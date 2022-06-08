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
    std::string args, wave_type, ant, subdev, ref, pps, wirefmt, channels, signal_file;
    // uint64_t total_num_samps;
    size_t spb;
    double rate, freq, gain, bw, lo_offset, start, setup_time;
    float ampl;
    // float T0 = 1e-6;
    // double wave_freq, max_freq;
    

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
        ("channels", po::value<std::string>(&channels)->default_value("0"), "which channels to use (specify \"0\", \"1\", \"0,1\", etc)")
        ("freq", po::value<double>(&freq)->default_value(100e6), "IF center frequency in Hz")
        ("gain", po::value<double>(&gain)->default_value(0), "gain for the RF chain")
        ("int-n", "tune USRP with integer-N tuning")
        ("lo-offset", po::value<double>(&lo_offset)->default_value(0.0),
            "Offset for frontend LO in Hz (optional)")    
        // ("max-freq", po::value<double>(&max_freq)->default_value(20e6), "maximum waveform frequency in Hz for OFDM")
        // ("nsamps", po::value<uint64_t>(&total_num_samps)->default_value(0), "total number of samples to transmit")
        ("pps", po::value<std::string>(&pps)->default_value("external"), "PPS source (internal, external, mimo, gpsdo)")
        ("rate", po::value<double>(&rate)->default_value(200e6), "rate of outgoing samples")
        ("ref", po::value<std::string>(&ref)->default_value("external"), "clock reference (internal, external, mimo, gpsdo)")
        ("setup", po::value<double>(&setup_time)->default_value(1.0), "seconds of setup time")
        ("signal", po::value<std::string>(&signal_file)->default_value("cosmos_-100MHz_to_100MHz_SR_200MS"), "signal txt file name")
        ("start", po::value<double>(&start)->default_value(5.0), "start streaming time")
        ("spb", po::value<size_t>(&spb)->default_value(0), "samples per buffer, 0 for default")
        ("subdev", po::value<std::string>(&subdev)->default_value("A:AB"), "subdevice specification, use A:AB for Tx")
        ("wave-type", po::value<std::string>(&wave_type)->default_value("OFDM"), "waveform type (SINE)")
        // ("wave-freq", po::value<double>(&wave_freq)->default_value(1e6), "waveform frequency in Hz")
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
            std::cout << boost::format("UHD Tx sending OFDM by WiDeS %s") % desc << std::endl;
            return ~0;
        }



    //// ====== Create a usrp device ======
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % args
                << std::endl;
        // uhd is defined at "<uhd/usrp/multi_usrp.hpp>" and implemented in "uhd/lib/.cpp"   
        uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);



    //// ====== Select Sub-device (always has default value) ======
        usrp->set_tx_subdev_spec(subdev);   // A:AB for Tx, and B:AB for Rx, check the "X310 probe" note in Samsung Notes



    //// ====== Print Device Info ======
        // "get_pp_string" will return:
        //  1. USRP clock device;
        //  2. board amount, and their references;
        std::cout << std::endl;
        std::cout << boost::format("Using TX Device: %s") % usrp->get_pp_string()
                << std::endl;
        


    //// ====== Detect which channels to use ======
        // if build error: split is not member of boost, then add library:
        // #include <boost/algorithm/string.hpp>
        std::vector<std::string> channel_strings;
        std::vector<size_t> channel_nums;
        boost::split(channel_strings, channels, boost::is_any_of("\"',"));
        for (size_t ch_idx = 0; ch_idx < channel_strings.size(); ch_idx++) {
            size_t chan = std::stoi(channel_strings[ch_idx]);
            if (chan >= usrp->get_tx_num_channels())
                throw std::runtime_error("Invalid Tx channel(s) specified.");
            else
                channel_nums.push_back(std::stoi(channel_strings[ch_idx]));
        }



    //// ====== Set mboard reference clock source (always has default value) ======
        usrp->set_clock_source(ref);

        std::cout << std::endl;
        std::cout<<boost::format("The reference clock for the Tx is: %s...") % ref
                    <<std::endl;



    //// ====== Reset timestamp and pps (always has default value) ======
        std::cout << boost::format("Setting device timestamp to 0 for the next unknown PPS edge...") << std::endl;

        usrp->set_time_source(pps);
        usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));  // set the next coming pps as t = 0;
        // usrp->set_time_next_pps(uhd::time_spec_t(0.0));
        std::this_thread::sleep_for(
            std::chrono::seconds(1)); // wait for pps sync pulse
        
        std::cout<<std::endl;
        std::cout<<"t=0 timestamp set."
            <<std::endl;   



    //// ====== Set the sample rate (always has default value) ======
        // set the Tx sample rate
        std::cout << boost::format("Setting Tx Rate: %f Msps...") % (rate / 1e6) << std::endl;
        usrp->set_tx_rate(rate);  // remove the channels parameters or not?
        std::cout << boost::format("Actual Tx Rate: %f Msps...")
                        % (usrp->get_tx_rate() / 1e6)
                << std::endl;
                


    //// ====== Configure each channel ======
        for (size_t ch_idx = 0; ch_idx < channel_nums.size(); ch_idx++) {

            size_t channel = channel_nums[ch_idx];

            std::cout<<std::endl;
            std::cout << boost::format("Timed command: Setting Tx Freq: %f MHz...") 
                    % (freq / 1e6) << std::endl;
            std::cout << boost::format("Timed command: Setting Tx LO Offset: %f MHz...") 
                    % (lo_offset / 1e6) << std::endl;

            // start timed command with tune: 
            usrp->clear_command_time();
            usrp->set_command_time(uhd::time_spec_t(4.0));  //operate any command after "set_command_time" at t sec;
            
            // timed command content:
                uhd::tune_request_t tune_request(freq, lo_offset);
                if (vm.count("int-n"))
                    tune_request.args = uhd::device_addr_t("mode_n=integer");
                usrp->set_tx_freq(tune_request, channel);
                std::this_thread::sleep_for(std::chrono::milliseconds(110)); //sleep 110ms (~10ms after retune occurs) to allow LO to lock

            usrp->clear_command_time();


            // print setting results
            std::cout<<std::endl;
            std::cout << boost::format("Actual Tx Freq: %f MHz...")
                            % (usrp->get_tx_freq(channel) / 1e6)
                    << std::endl;
                    


            // set the rf gain (always has default value)
            std::cout<<std::endl;
            std::cout << boost::format("Setting Tx Gain: %f dB...") % gain << std::endl;
            usrp->set_tx_gain(gain, channel);
            std::cout << boost::format("Actual Tx Gain: %f dB...")
                            % usrp->get_tx_gain(channel)
                    << std::endl;
                    


            // set the analog frontend filter bandwidth
            if (vm.count("bw")) {
                std::cout<<std::endl;
                std::cout << boost::format("Setting Tx Bandwidth: %f MHz...") % (bw / 1e6)
                        << std::endl;
                usrp->set_tx_bandwidth(bw, channel);
                std::cout << boost::format("Actual Tx Bandwidth: %f MHz...")
                                % usrp->get_tx_bandwidth(channel / 1e6)
                        << std::endl;
            }


            // set the antenna (always has default value)
            usrp->set_tx_antenna(ant, channel);
        }



    //// ====== Wait for Setup ======
        std::this_thread::sleep_for(std::chrono::seconds(int64_t(1 * setup_time))); // allow for some setup time



    //// ====== Pre-compute wavetable ======
        signal_file = signal_file + ".txt";
        const wave_table_class wave_table(wave_type, ampl, signal_file);
        const size_t step = 1;
        size_t index = 0;



    //// ====== Create a transmit streamer ======
        // linearly map channels (index0 = channel0, index1 = channel1, ...)
        uhd::stream_args_t stream_args("fc32", wirefmt);
        stream_args.channels             = channel_nums;
        uhd::tx_streamer::sptr tx_stream = usrp->get_tx_stream(stream_args);



    //// ====== Allocate a buffer which we re-use for each channel ======
        if (spb == 0) 
            spb = tx_stream->get_max_num_samps() * 10;
        std::vector<std::complex<float>> buff(spb);
        std::vector<std::complex<float>*> buffs(channel_nums.size(), &buff.front());


        
    //// ====== Pre-fill the buffer ======
        std::cout<<"size of buffer is: "<<buff.size()<<" and step is: " << step << std::endl;
        for (size_t n = 0; n < buff.size(); n++) 
            buff[n] = wave_table(index += step);




    //// ====== Set up metadata ======
        uhd::tx_metadata_t md;
        md.start_of_burst = true;
        md.end_of_burst   = false;
        md.has_time_spec  = true;
        md.time_spec      = uhd::time_spec_t(start); // test if the Tx will not send until t = 10. 

        std::cout<<std::endl;
        std::cout << "Wait for less than " << md.time_spec.get_real_secs() << " seconds to start streaming..."
                << std::endl;
        std::cout<< "The meta data will not display untill the transmission is done. "
                << std::endl;


    

    //// ====== Check Ref and LO Lock detect ======
        // LO locking check
        std::vector<std::string> sensor_names;
        const size_t tx_sensor_chan = channel_nums.empty() ? 0 : channel_nums[0];   // in this case, the value is still 0
        sensor_names                = usrp->get_tx_sensor_names(tx_sensor_chan);
        if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")
            != sensor_names.end()) {
            uhd::sensor_value_t lo_locked = usrp->get_tx_sensor("lo_locked", tx_sensor_chan);
            std::cout << boost::format("Checking Tx: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }

        // Reference Clock
        const size_t mboard_sensor_idx = 0;
        sensor_names = usrp->get_mboard_sensor_names(mboard_sensor_idx);
        if ((ref == "external")
            and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")
                    != sensor_names.end())) {
            uhd::sensor_value_t ref_locked =
                usrp->get_mboard_sensor("ref_locked", mboard_sensor_idx);
            std::cout << boost::format("Checking Tx: %s ...") % ref_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }



    //// ====== Tx streaming mode ======
        std::signal(SIGINT, &sig_int_handler);
        std::cout << "Press Ctrl + C to stop streaming..." << std::endl << std::endl;
    








    
     


    //// ====== Send data ======
    // Until the signal handler gets called or if we accumulate the number 
    // of samples that been specified (unless it's 0).
    uint64_t num_acc_samps = 0;
    uhd::set_thread_priority(); //Added as suggested by Neel
    while (true) {
        // Break on the end of duration or CTRL-C
        if (stop_signal_called) {
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
        std::cout << "Metadata Here... " << std::endl;
        std::cout << "  Streaming starting tick = " << md.time_spec.to_ticks(200e6) << std::endl;
        std::cout << "  Streaming starting sec = " << md.time_spec.get_real_secs() 
                    << std::endl
                    << std::endl;
        return EXIT_SUCCESS;
}

