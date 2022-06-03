//
// Copyright 2010-2012,2014 Ettus Research LLC
// Copyright 2018 Ettus Research, a National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include "wavetable_Brian.hpp"
// #include "wavetable.hpp"
#include <uhd/exception.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/static.hpp>
#include <uhd/utils/thread.hpp>
#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>

namespace po = boost::program_options;

/***********************************************************************
 * Signal handlers
 **********************************************************************/
static bool stop_signal_called = false;
void sig_int_handler(int)
{
    stop_signal_called = true;
}

/***********************************************************************
 * Main function
 **********************************************************************/
int UHD_SAFE_MAIN(int argc, char* argv[])
{
    // variables to be set by po
    std::string args, wave_type, ant, subdev, ref, pps, wirefmt, channel_list, file;
    uint64_t total_num_samps;
    size_t spb;
    double rate, freq, gain, wave_freq, bw, lo_offset, max_freq;
    float ampl;
    // float T0 = 1e-6;
    

    // setup the program options
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        // ("help", "help message")
        // ("args", po::value<std::string>(&args)->default_value(""), "single uhd device address args")
        // ("spb", po::value<size_t>(&spb)->default_value(0), "samples per buffer, 0 for default")
        // ("nsamps", po::value<uint64_t>(&total_num_samps)->default_value(0), "total number of samples to transmit")
        // ("rate", po::value<double>(&rate), "rate of outgoing samples")
        // ("freq", po::value<double>(&freq), "RF center frequency in Hz")
        // ("lo-offset", po::value<double>(&lo_offset)->default_value(0.0),
        //     "Offset for frontend LO in Hz (optional)")
        // ("ampl", po::value<float>(&ampl)->default_value(float(0.3)), "amplitude of the waveform [0 to 0.7]")
        // ("gain", po::value<double>(&gain), "gain for the RF chain")
        // ("ant", po::value<std::string>(&ant), "antenna selection")
        // ("subdev", po::value<std::string>(&subdev), "subdevice specification")
        // ("bw", po::value<double>(&bw), "analog frontend filter bandwidth in Hz")
        // ("wave-type", po::value<std::string>(&wave_type)->default_value("CONST"), "waveform type (CONST, SQUARE, RAMP, SINE)")
        // ("wave-freq", po::value<double>(&wave_freq)->default_value(0), "waveform frequency in Hz")
        // ("ref", po::value<std::string>(&ref)->default_value("internal"), "clock reference (internal, external, mimo, gpsdo)")
        // ("pps", po::value<std::string>(&pps), "PPS source (internal, external, mimo, gpsdo)")
        // ("otw", po::value<std::string>(&otw)->default_value("sc16"), "specify the over-the-wire sample mode")
        // ("channels", po::value<std::string>(&channel_list)->default_value("0"), "which channels to use (specify \"0\", \"1\", \"0,1\", etc)")
        // ("int-n", "tune USRP with integer-N tuning")

        ("help", "help message")

        ("ampl", po::value<float>(&ampl)->default_value(float(0.7)), "amplitude of the waveform [0 to 0.7]")
        ("ant", po::value<std::string>(&ant)->default_value("AB"), "antenna selection")
        ("args", po::value<std::string>(&args)->default_value("addr=10.38.14.1"), 
            "single uhd device address args, and it can be IP address. Default value is the Tx USRP. ")
        ("bw", po::value<double>(&bw), "analog frontend filter bandwidth in Hz")
        ("channels", po::value<std::string>(&channel_list)->default_value("0"), "which channels to use (specify \"0\", \"1\", \"0,1\", etc)")
        ("file", po::value<std::string>(&file)->default_value(""), "signal txt file name")
        ("freq", po::value<double>(&freq)->default_value(80e6), "IF center frequency in Hz")
        ("gain", po::value<double>(&gain)->default_value(0), "gain for the RF chain")
        ("int-n", "tune USRP with integer-N tuning")
        ("lo-offset", po::value<double>(&lo_offset)->default_value(0.0),
            "Offset for frontend LO in Hz (optional)")    
        ("max-freq", po::value<double>(&max_freq)->default_value(20e6), "maximum waveform frequency in Hz for OFDM")
        ("nsamps", po::value<uint64_t>(&total_num_samps)->default_value(0), "total number of samples to transmit")
        ("pps", po::value<std::string>(&pps)->default_value("external"), "PPS source (internal, external, mimo, gpsdo)")
        ("rate", po::value<double>(&rate)->default_value(10e6), "rate of outgoing samples")
        ("ref", po::value<std::string>(&ref)->default_value("external"), "clock reference (internal, external, mimo, gpsdo)")
        ("spb", po::value<size_t>(&spb)->default_value(0), "samples per buffer, 0 for default")
        ("subdev", po::value<std::string>(&subdev)->default_value("A:AB"), "subdevice specification, use A:AB for Tx")
        ("wave-type", po::value<std::string>(&wave_type)->default_value("OFDM"), "waveform type (SINE)")
        ("wave-freq", po::value<double>(&wave_freq)->default_value(1e6), "waveform frequency in Hz")
        ("wirefmt", po::value<std::string>(&wirefmt)->default_value("sc16"), "specify the over-the-wire sample mode")

    ;
    
    //// ====== Clang-format on ======
        // An object of class "variables_map" is declared. That class is intended to store values 
        // of options, and can store values of arbitrary types. Next, the calls to "store", 
        // "parse_command_line" and "notify" functions cause "vm" to contain all the options found 
        // on the command line.
        //
        // If an option "arg" exists, then "vm.count(arg)" returns a bool value to represent True. 
        // 
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

    
    
    //// ====== Print the help message ======
        if (vm.count("help")) {
            std::cout << boost::format("UHD TX Waveforms %s") % desc << std::endl;
            return ~0;
        }



    //// ====== Create a usrp device ======
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % args
                << std::endl;
        // uhd is defined at "<uhd/usrp/multi_usrp.hpp>" and implemented in "uhd/lib/.cpp"   
        uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);



    //// ====== Select Sub-device (always has default value) ======
        if (vm.count("subdev"))
            usrp->set_tx_subdev_spec(subdev);   // A:AB for Tx, and B:AB for Rx, check the "X310 probe" note in Samsung Notes


    //// ====== Detect which channels to use ======
        std::vector<std::string> channel_strings;
        std::vector<size_t> channel_nums;
        boost::split(channel_strings, channel_list, boost::is_any_of("\"',"));
        for (size_t ch_idx = 0; ch_idx < channel_strings.size(); ch_idx++) {
            size_t chan = std::stoi(channel_strings[ch_idx]);
            if (chan >= usrp->get_tx_num_channels())
                throw std::runtime_error("Invalid channel(s) specified.");
            else
                channel_nums.push_back(std::stoi(channel_strings[ch_idx]));
        }



    //// ====== Lock mboard reference clock source (always has default value) ======
        usrp->set_clock_source(ref);
        std::cout<<boost::format("The reference clock for motherboard is: %s...") % ref
                    <<std::endl;


    //// ====== Print Device Info ======
        // "get_pp_string" will return:
        //  1. USRP clock device;
        //  2. board amount, and their references;
        std::cout << boost::format("Using Device: %s") % usrp->get_pp_string() << std::endl;



    //// ====== Set the sample rate ======
        if (not vm.count("rate")) {
            std::cerr << "Please specify the sample rate with --rate" << std::endl;
            return ~0;
        }
        std::cout << boost::format("Setting TX Rate: %f Msps...") % (rate / 1e6) << std::endl;
        usrp->set_tx_rate(rate);
        std::cout << boost::format("Actual TX Rate: %f Msps...") % (usrp->get_tx_rate() / 1e6)
                << std::endl;



    //// ====== Set the center frequency (always has default value) ======
            // std::cerr << "Please specify the center frequency with --freq" << std::endl;
            // return ~0;


    //// ====== Configure each channel ======
        for (size_t ch_idx = 0; ch_idx < channel_nums.size(); ch_idx++) {
            std::cout << boost::format("Setting TX Freq: %f MHz...") % (freq / 1e6)
                    << std::endl;
            std::cout << boost::format("Setting TX LO Offset: %f MHz...") % (lo_offset / 1e6)
                    << std::endl;
            uhd::tune_request_t tune_request(freq, lo_offset);
            if (vm.count("int-n"))
                tune_request.args = uhd::device_addr_t("mode_n=integer");
            usrp->set_tx_freq(tune_request, channel_nums[ch_idx]);
            std::cout << boost::format("Actual TX Freq: %f MHz...")
                            % (usrp->get_tx_freq(channel_nums[ch_idx]) / 1e6)
                    << std::endl
                    << std::endl;


            // set the rf gain (always has default value)
                std::cout << boost::format("Setting TX Gain: %f dB...") % gain << std::endl;
                usrp->set_tx_gain(gain, channel_nums[ch_idx]);
                std::cout << boost::format("Actual TX Gain: %f dB...")
                                % usrp->get_tx_gain(channel_nums[ch_idx])
                        << std::endl
                        << std::endl;


            // set the analog frontend filter bandwidth
            if (vm.count("bw")) {
                std::cout << boost::format("Setting TX Bandwidth: %f MHz...") % (bw / 1e6)
                        << std::endl;
                usrp->set_tx_bandwidth(bw, channel_nums[ch_idx]);
                std::cout << boost::format("Actual TX Bandwidth: %f MHz...")
                                % usrp->get_tx_bandwidth(channel_nums[ch_idx] / 1e6)
                        << std::endl
                        << std::endl;
            }


            // set the antenna (always has default value)
            if (vm.count("ant"))
                usrp->set_tx_antenna(ant, channel_nums[ch_idx]);
        }



    std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time



    // // for the const wave, set the wave freq for small samples per period
    // if (wave_freq == 0) {
    //     if (wave_type == "CONST") {
    //         wave_freq = usrp->get_tx_rate() / 2;
    //     } else {
    //         throw std::runtime_error(
    //             "wave freq cannot be 0 with wave type other than CONST");
    //     }
    // }



    //// ====== Error when the waveform is not possible to generate ======
        // when the waveform frequency*2 > Tx sampling rate, can't generate wfm. 
        if (wave_type == "OFDM")
            wave_freq = max_freq;
        
        if (std::abs(wave_freq) > usrp->get_tx_rate() / 2) {
            throw std::runtime_error("wave freq out of Nyquist zone");
        }

        // This step is to make sure there are more than half of the signal
        // points have been sampled within each signal duration (which is 
        // determined by the waveform frequency accordingly). --> still Nyquist Sampling Law
        if (usrp->get_tx_rate() / std::abs(wave_freq) > wave_table_len / 2) {
            throw std::runtime_error("wave freq too small for table");
        }



    //// ====== Create a transmit streamer ======
        // linearly map channels (index0 = channel0, index1 = channel1, ...)
        uhd::stream_args_t stream_args("fc32", wirefmt);
        stream_args.channels             = channel_nums;
        uhd::tx_streamer::sptr tx_stream = usrp->get_tx_stream(stream_args);



    //// ====== Allocate a buffer which we re-use for each channel ======
        if (spb == 0) {
            spb = tx_stream->get_max_num_samps() * 10;
        }
        std::vector<std::complex<float>> buff(spb);
        std::vector<std::complex<float>*> buffs(channel_nums.size(), &buff.front());


        // pre-fill the buffer with the waveform
        file = file + ".txt";
        const wave_table_class wave_table(wave_type, ampl, file);
        // const size_t step = 
        //     std::lround(wave_freq / usrp->get_tx_rate() * wave_table_len);
        // const size_t step = wave_table_len / (usrp->get_tx_rate() * T0);
        const size_t step = 1;
        size_t index = 0;

        std::cout<<"size of buffer is: "<<buff.size()<<" and step is: " << step << std::endl;
        for (size_t n = 0; n < buff.size(); n++) {
            buff[n] = wave_table(index += step);
        }

        // size_t step_tmp = 5;
        // index = 0;
        // for (size_t n = 0; n < 10; n++) {
        //     std::cout<< wave_table(index += step_tmp)<<std::endl;
        // }


    //// ====== Set timestamp and pps ======
        std::cout << boost::format("Setting device timestamp to 0...") << std::endl;
        if (channel_nums.size() >= 1) {
            // Sync times
            if (pps == "mimo") {
                UHD_ASSERT_THROW(usrp->get_num_mboards() == 2);

                // make mboard 1 a slave over the MIMO Cable
                usrp->set_time_source("mimo", 1);

                // set time on the master (mboard 0)
                usrp->set_time_now(uhd::time_spec_t(0.0), 0);

                // sleep a bit while the slave locks its time to the master
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                if (pps == "internal" or pps == "external" or pps == "gpsdo"){
                    usrp->set_time_source(pps);
                    std::cout<<"pps set success"<<std::endl;
                }
                usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));
                std::this_thread::sleep_for(
                    std::chrono::seconds(1)); // wait for pps sync pulse
            }
        } else {
            usrp->set_time_now(0.0);
        }

    //// ====== Check Ref and LO Lock detect ======
        std::vector<std::string> sensor_names;
        const size_t tx_sensor_chan = channel_nums.empty() ? 0 : channel_nums[0];
        sensor_names                = usrp->get_tx_sensor_names(tx_sensor_chan);
        if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")
            != sensor_names.end()) {
            uhd::sensor_value_t lo_locked = usrp->get_tx_sensor("lo_locked", tx_sensor_chan);
            std::cout << boost::format("Checking TX: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }
        const size_t mboard_sensor_idx = 0;
        sensor_names = usrp->get_mboard_sensor_names(mboard_sensor_idx);
        if ((ref == "mimo")
            and (std::find(sensor_names.begin(), sensor_names.end(), "mimo_locked")
                    != sensor_names.end())) {
            uhd::sensor_value_t mimo_locked =
                usrp->get_mboard_sensor("mimo_locked", mboard_sensor_idx);
            std::cout << boost::format("Checking TX: %s ...") % mimo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(mimo_locked.to_bool());
        }
        if ((ref == "external")
            and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")
                    != sensor_names.end())) {
            uhd::sensor_value_t ref_locked =
                usrp->get_mboard_sensor("ref_locked", mboard_sensor_idx);
            std::cout << boost::format("Checking TX: %s ...") % ref_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }



    std::signal(SIGINT, &sig_int_handler);
    std::cout << "Press Ctrl + C to stop streaming..." << std::endl;



    //// ====== Set up metadata ======
        // We start streaming a bit in the future to allow MIMO operation:
        uhd::tx_metadata_t md;
        md.start_of_burst = true;
        md.end_of_burst   = false;
        md.has_time_spec  = true;

        uhd::time_spec_t Ettus_const_value = uhd::time_spec_t(0.1);
        // md.time_spec      = usrp->get_time_now() + uhd::time_spec_t(0.1);
        md.time_spec = usrp->get_time_now() + Ettus_const_value;

        
        
        std::cout << "starting timetamp = " << md.time_spec << std::endl;



    //// ====== Send data ======
    // Until the signal handler gets called or if we accumulate the number 
    // of samples that been specified (unless it's 0).
    uint64_t num_acc_samps = 0;
    while (true) {
        // Break on the end of duration or CTRL-C
        if (stop_signal_called) {
            break;
        }
        // Break when we've received nsamps
        if (total_num_samps > 0 and num_acc_samps >= total_num_samps) {
            break;
        }

        // send the entire contents of the buffer
        num_acc_samps += tx_stream->send(buffs, buff.size(), md);

        // fill the buffer with the waveform
        for (size_t n = 0; n < buff.size(); n++) {
            buff[n] = wave_table(index += step);
        }

        md.start_of_burst = false;
        md.has_time_spec  = false;
    }

    // send a mini EOB packet
    md.end_of_burst = true;
    tx_stream->send("", 0, md);



    //// finished
        // "EXIT_SUCCESS" and "0" both mean the program has executed successfully, 
        // but "EXIT_SUCCESS" is not requried to be equal to 0.
        std::cout << std::endl << "Done!" << std::endl << std::endl;
        return EXIT_SUCCESS;
}

