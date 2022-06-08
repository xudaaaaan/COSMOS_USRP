//
// Copyright 2010-2012,2014-2015 Ettus Research LLC
// Copyright 2018 Ettus Research, a National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include "wavetable_Brian.hpp"
// #include "wavetable.hpp"
#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/static.hpp>
#include <uhd/utils/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <csignal>
#include <fstream>
#include <iostream>

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
 * Utilities
 **********************************************************************/
//! Change to filename, e.g. from usrp_samples.dat to usrp_samples.00.dat,
//  but only if multiple names are to be generated.
std::string generate_out_filename(
    const std::string& base_fn, size_t n_names, size_t this_name)
{
    if (n_names == 1) {
        return base_fn;
    }

    boost::filesystem::path base_fn_fp(base_fn);
    base_fn_fp.replace_extension(boost::filesystem::path(
        str(boost::format("%02d%s") % this_name % base_fn_fp.extension().string())));
    return base_fn_fp.string();
}


/***********************************************************************
 * transmit_worker function
 * A function to be used as a boost::thread_group thread for transmitting
 **********************************************************************/
void transmit_worker(std::vector<std::complex<float>> buff,
    wave_table_class wave_table,
    uhd::tx_streamer::sptr tx_streamer,
    uhd::tx_metadata_t md,  // metadata
    size_t step,
    size_t index,
    int size_channels)
{
    std::vector<std::complex<float>*> buffs(size_channels, &buff.front());

    // send data until the signal handler gets called
    while (not stop_signal_called) {
        // fill the buffer with the waveform
        for (size_t n = 0; n < buff.size(); n++) {
            buff[n] = wave_table(index += step);
        }

        // send the entire contents of the buffer
        tx_streamer->send(buffs, buff.size(), md);

        md.start_of_burst = false;
        md.has_time_spec  = false;
    }

    // send a mini EOB packet
    md.end_of_burst = true;
    tx_streamer->send("", 0, md);
}


/***********************************************************************
 * recv_to_file function
 **********************************************************************/
template <typename samp_type>
void recv_to_file(uhd::usrp::multi_usrp::sptr usrp,   // a USRP object/(virtual) device
    const std::string& cpu_format,
    const std::string& wire_format,
    // const std::string& channel,
    const std::string& data_file,
    size_t samps_per_buff,
    unsigned long long  num_requested_samples,
    double time_requested       = 0.0,
    double start_streaming_time,
    bool bw_summary             = false,
    bool stats                  = false,
    bool null                   = false,
    bool enable_size_map        = false,
    bool continue_on_bad_packet = false,
    std::vector<size_t> rx_channel_nums)
{
    unsigned long long  num_total_samps = 0;   // number of samples have received so far

    //// ====== Create a receive streamer ======
        uhd::stream_args_t stream_args(cpu_format, wire_format);
        stream_args.channels = rx_channel_nums;
        uhd::rx_streamer::sptr rx_stream = usrp->get_rx_stream(stream_args);

        uhd::rx_metadata_t rx_md;
        std::vector<std::vector<samp_type>> buffs(
            rx_channel_nums.size(), std::vector<samp_type>(samps_per_buff));

        std::ofstream datafile;
        std::ofstream metadatafile;

        size_t num_rx_samps = 0;

        char full_file_name[200];
        char full_metafile_name[200];
        strcpy(full_file_name, data_file.c_str());
        strcat(full_file_name, ".dat");
        if (not null)
            datafile.open(full_file_name, std::ofstream::binary);
        bool overflow_message = true;


    //// ====== Configurations ======
        // Setup streaming
            uhd::stream_cmd_t stream_cmd((num_requested_samples == 0)
                        ? uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS
                        : uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
        
        // Number of samples to receive
            stream_cmd.num_samps  = size_t(num_requested_samples);

        // time to receive samples
            stream_cmd.stream_now = false;
            uhd::time_spec_t time_to_recv = uhd::time_spec_t(start_streaming_time);
            stream_cmd.time_spec  = time_to_recv;
            rx_stream->issue_stream_cmd(stream_cmd);

        // Define starting and stop time when request a duration
            const auto start_time = std::chrono::steady_clock::now();
            const auto stop_time =
                start_time + std::chrono::milliseconds(int64_t(1000 * time_requested));

        // Define sizemap
            typedef std::map<size_t, size_t> SizeMap;
            SizeMap mapSizes;

        // Track time and samps between updating the BW summary
            auto last_update = start_time;
            unsigned long long last_update_samps = 0; 


        // --- prints ---
            std::cout<<std::endl;
            std::cout << "  Wait for less than " << time_to_recv.get_real_secs() << " seconds to start streaming..."
                << std::endl;
        // --------------


    //// ====== Keep running until... ======
    // Until either time expired (if a duration was given), until
    // the requested number of samples were collected (if such a number was
    // given), or until Ctrl-C was pressed.

    while (not stop_signal_called
        and (num_requested_samples != num_total_samps or num_requested_samples == 0)
        and (time_requested == 0.0 or std::chrono::steady_clock::now() <= stop_time))  {
            
            const auto now = std::chrono::steady_clock::now();

            num_rx_samps = 
                rx_stream->recv(&buff.front(), buff.size(), md, 30.0);

            // Define error cases
                // - 1 - 
                if (rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
                    std::cout<<std::endl;
                    std::cout << boost::format("Timeout while streaming") << std::endl;
                    break;
                }

                // - 2 - 
                if (rx_md.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
                    if (overflow_message) {
                        overflow_message = false;
                        std::cerr
                            << boost::format(
                                "Got an overflow indication. Please consider the following:\n"
                                "  Your write medium must sustain a rate of %fMB/s.\n"
                                "  Dropped samples will not be written to the file.\n"
                                "  Please modify this example for your purposes.\n"
                                "  This message will not appear again.\n")
                                % (usrp->get_rx_rate() * sizeof(samp_type) / 1e6);
                    }
                    continue;
                }

                // - 3 - 
                if (rx_md.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
                    std::string error = str(boost::format("Receiver error: %s") % rx_md.strerror());
                    if (continue_on_bad_packet) {
                        std::cerr << error << std::endl;
                        continue;
                    } else
                        throw std::runtime_error(error);
                }


            if (enable_size_map) {
                SizeMap::iterator it = mapSizes.find(num_rx_samps);
                if (it == mapSizes.end())
                    mapSizes[num_rx_samps] = 0;
                mapSizes[num_rx_samps] += 1;
            }

            num_total_samps += num_rx_samps;

            if (datafile.is_open()) {
                datafile.write((const char*)&buff.front(), num_rx_samps * sizeof(samp_type));
            }

            if (bw_summary) {
                last_update_samps += num_rx_samps;
                const auto time_since_last_update = now - last_update;
                if (time_since_last_update > std::chrono::seconds(1)) {
                    const double time_since_last_update_s =
                        std::chrono::duration<double>(time_since_last_update).count();
                    const double rate = double(last_update_samps) / time_since_last_update_s;
                    std::cout << "\t" << (rate / 1e6) << " Msps" << std::endl;
                    last_update_samps = 0;
                    last_update       = now;
                }
            }
    } //while ends
    const auto actual_stop_time = std::chrono::steady_clock::now();

    // Shut down receiver
    stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    rx_stream->issue_stream_cmd(stream_cmd);

    // Close files
    if (datafile.is_open()) {
        datafile.close();
    }

    if (stats) {
        std::cout << std::endl;
        const double actual_duration_seconds =
            std::chrono::duration<float>(actual_stop_time - start_time).count();

        std::cout << boost::format("Received %d samples in %f seconds") % num_total_samps
                         % actual_duration_seconds
                  << std::endl;
        const double rate = (double)num_total_samps / actual_duration_seconds;
        std::cout << (rate / 1e6) << " Msps" << std::endl;

        if (enable_size_map) {
            std::cout << std::endl;
            std::cout << "Packet size map (bytes: count)" << std::endl;
            for (SizeMap::iterator it = mapSizes.begin(); it != mapSizes.end(); it++)
                std::cout << it->first << ":\t" << it->second << std::endl;
        }
    }


    //// ====== Process Metadata ======
        long long rx_starting_tick = rx_md.time_spec.to_ticks(200e6);
        double rx_starting_sec = rx_md.time_spec.get_real_secs();
        std::cout<<std::endl;
        std::cout << "Metadata Here... " << std::endl;
        std::cout << "  Streaming starting tick = " << rx_starting_tick << std::endl;
        std::cout << "  Streaming starting sec = " << rx_starting_sec 
                    << std::endl;
        
        if (not null){
            strcpy(full_metafile_name, data_file.c_str());
            strcat(full_metafile_name, "_metadata.dat");
            metadatafile.open(full_metafile_name, std::ofstream::binary);
            metadatafile.write((char*)&rx_starting_tick, sizeof(long long));
            metadatafile.close();

            std::cout<<std::endl;
            std::cout << "===============================" << std::endl;
            std::cout << boost::format("Data is saved in file: %s") % full_file_name
                    << std::endl
                    << std::endl;


            std::cout << boost::format("Metadata is saved in file: %s") % full_metafile_name
                    << std::endl;
            std::cout << "===============================" << std::endl;
            std::cout<<std::endl;
            std::cout<< "Rx done!" <<std::endl;

        }
} // recv_to_file ends





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




/***********************************************************************
 * Main function
 **********************************************************************/
int UHD_SAFE_MAIN(int argc, char* argv[])
{
    // transmit variables to be set by po
    std::string tx_args, wave_type, tx_ant, tx_subdev, ref, wirefmt, tx_channels, signal_file;
    double tx_rate, tx_gain, tx_bw, tx_lo_offset, tx_start;
    float ampl;

    // receive variables to be set by po
    std::string rx_args, data_file, data_type, rx_ant, rx_subdev, rx_channels;
    size_t total_num_samps;
    double rx_rate, rx_gain, rx_bw, rx_lo_offset, rx_start, total_time;
    
    //general variables
    std::string pps, ref, wirefmt;
    double freq, setup_time;
    size_t spb;
    

    // setup the program options
    po::options_description desc("Allowed options");

    // clang-format off
    desc.add_options()
        ("help", "help message")

        // Tx parameters
        ("ampl", po::value<float>(&ampl)->default_value(float(0.7)), "amplitude of the waveform [0 to 0.7]")
        ("tx-ant", po::value<std::string>(&tx_ant)->default_value("AB"), "transmit antenna selection")
        ("tx-args", po::value<std::string>(&tx_args)->default_value("addr=10.38.14.1"), "uhd transmit device address args")
        ("tx-bw", po::value<double>(&tx_bw), "analog transmit filter bandwidth in Hz")
        ("tx-channels", po::value<std::string>(&tx_channels)->default_value("0"), "which TX channel(s) to use (specify \"0\", \"1\", \"0,1\", etc)")
        // ("tx-freq", po::value<double>(&tx_freq)->default_value(100e6), "transmit RF center frequency in Hz")
        ("tx-gain", po::value<double>(&tx_gain)->default_value(0), "gain for the transmit RF chain")
        ("tx-int-n", "tune USRP TX with integer-N tuning")
        ("tx-lo-offset", po::value<double>(&tx_lo_offset)->default_value(0.0),
            "Offset for frontend LO in Hz (optional)")   
        ("tx-rate", po::value<double>(&tx_rate)->default_value(200e6), "rate of transmit outgoing samples")
        ("tx-signal", po::value<std::string>(&signal_file)->default_value("cosmos_-100MHz_to_100MHz_SR_200MS"), "signal txt file name")
        ("tx-start", po::value<double>(&tx_start)->default_value(10.0), "Tx starts streaming time")
        ("tx-subdev", po::value<std::string>(&tx_subdev)->default_value("A:AB"), "transmit subdevice specification")
        ("wave-type", po::value<std::string>(&wave_type)->default_value("OFDM"), "waveform type (CONST, SQUARE, RAMP, SINE)")
        
        // Rx parameters
        ("rx-ant", po::value<std::string>(&rx_ant)->default_value("AB"), "receive antenna selection")
        ("rx-args", po::value<std::string>(&rx_args)->default_value("addr=10.38.14.2"), "uhd receive device address args")
        ("rx-bw", po::value<double>(&rx_bw), "analog receive filter bandwidth in Hz")
        ("rx-channels", po::value<std::string>(&rx_channels)->default_value("0"), "which RX channel(s) to use (specify \"0\", \"1\", \"0,1\", etc)")
        ("rx-continue", "don't abort on a bad packet")
        ("rx-duration", po::value<double>(&total_time)->default_value(0), "total number of seconds to receive")
        ("rx-file", po::value<std::string>(&data_file)->default_value("usrp_samples.dat"), "name of the file to write binary samples to")
        // ("rx-freq", po::value<double>(&rx_freq)->default_value(100e6), "receive RF center frequency in Hz")
        ("rx-gain", po::value<double>(&rx_gain)->default_value(6), "gain for the receive RF chain")
        ("rx-int-n", "tune USRP RX with integer-N tuning")
        ("rx-lo-offset", po::value<double>(&rx_lo_offset)->default_value(0.0),
            "Offset for frontend LO in Hz (optional)")   
        ("rx-nsamps", po::value<size_t>(&total_num_samps)->default_value(0), "total number of samples to receive")
        ("rx-null", "Determine if run the code and save data to file. Add 'rx-null' when you don't want to save the data. ")
        ("rx-progress", "periodically display short-term bandwidth")
        ("rx-rate", po::value<double>(&rx_rate)->default_value(200e6), "rate of receive incoming samples")
        // ("rx-settling", po::value<double>(&settling)->default_value(double(15.0)), "settling time (seconds) before receiving")
        ("rx-sizemap", "track packet size and display breakdown on exit")
        ("rx-start", po::value<double>(&rx_start)->default_value(15.0), "Tx starts streaming time")
        ("rx-stats", "show average bandwidth on exit")
        ("rx-subdev", po::value<std::string>(&rx_subdev)->default_value("B:AB"), "receive subdevice specification")  
        ("rx-type", po::value<std::string>(&data_type)->default_value("double"), "sample type in file: double, float, or short")
                
        //General
        ("freq", po::value<double>(&freq)->default_value(100e6), "receive RF center frequency in Hz")
        ("pps", po::value<std::string>(&pps)->default_value("external"), "PPS source (internal, external, mimo, gpsdo)")
        ("ref", po::value<std::string>(&ref)->default_value("external"), "clock reference (internal, external, mimo, gpsdo)")
        ("setup", po::value<double>(&setup_time)->default_value(1.0), "seconds of setup time")
        ("spb", po::value<size_t>(&spb)->default_value(0), "samples per buffer, 0 for default")
        ("wirefmt", po::value<std::string>(&wirefmt)->default_value("sc16"), "specify the over-the-wire sample mode")
    ;


    //// ====== Clang-format on ======
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);



    //// ====== Print the help message ======
        if (vm.count("help")) {
            std::cout << boost::format("UHD single node controlled TxRx %s") % desc << std::endl;
            std::cout << std::endl
                  << "This application streams data from a single channel of a USRP "
                     "device to a file.\n"
                  << std::endl;
            return ~0;
        }



    /// ====== Set the Rx info parameters ======
        // vm.count("x") > 0 means there is an option named "x" is found. 
        bool bw_summary             = vm.count("rx-progress") > 0;  // initial value = 1
        bool stats                  = vm.count("rx-stats") > 0;     // initial value = 1
        bool null                   = vm.count("rx-null") > 0;      // initial value = 1
        bool enable_size_map        = vm.count("rx-sizemap") > 0;   // initial value = 1
        bool continue_on_bad_packet = vm.count("rx-continue") > 0;  // initial value = 1

        if (enable_size_map)
        std::cout << "Packet size tracking enabled - will only recv one packet at a time!"
                  << std::endl;



    //// ====== Create Tx and Rx USRP Devices ======
        // Tx USRP
        std::cout << std::endl;
        std::cout << boost::format("Creating the Tx USRP device with: %s...") % tx_args
                << std::endl;
        uhd::usrp::multi_usrp::sptr tx_usrp = uhd::usrp::multi_usrp::make(tx_args);

        // Rx USRP
        std::cout << std::endl;
        std::cout << boost::format("Creating the Rx USRP device with: %s...") % rx_args
                << std::endl;
        uhd::usrp::multi_usrp::sptr rx_usrp = uhd::usrp::multi_usrp::make(rx_args);



    //// ====== Select Sub-device (always has default value) ======
        tx_usrp->set_tx_subdev_spec(tx_subdev);
        rx_usrp->set_rx_subdev_spec(rx_subdev);


    
    //// ====== Print Device Info ======
        // "get_pp_string" will return:
        //  1. USRP clock device;
        //  2. board amount, and their references;
        std::cout << std::endl;
        std::cout << boost::format("Using TX Device: %s") % tx_usrp->get_pp_string()
                << std::endl;
        
        std::cout << std::endl;
        std::cout << boost::format("Using RX Device: %s") % rx_usrp->get_pp_string()
                << std::endl;



    //// ====== Detect which channels to use ======
        // Tx channel
        std::vector<std::string> tx_channel_strings;
        std::vector<size_t> tx_channel_nums;
        boost::split(tx_channel_strings, tx_channels, boost::is_any_of("\"',"));
        for (size_t ch_idx = 0; ch_idx < tx_channel_strings.size(); ch_idx++) {
            size_t chan = std::stoi(tx_channel_strings[ch_idx]);
            if (chan >= tx_usrp->get_tx_num_channels())
                throw std::runtime_error("Invalid Tx channel(s) specified.");
            else
                tx_channel_nums.push_back(std::stoi(tx_channel_strings[ch_idx]));
        }

        // Rx channel
        std::vector<std::string> rx_channel_strings;
        std::vector<size_t> rx_channel_nums;
        boost::split(rx_channel_strings, rx_channels, boost::is_any_of("\"',"));
        for (size_t ch_idx = 0; ch_idx < rx_channel_strings.size(); ch_idx++) {
            size_t chan = std::stoi(rx_channel_strings[ch_idx]);
            if (chan >= rx_usrp->get_rx_num_channels())
                throw std::runtime_error("Invalid Rx channel(s) specified.");
            else
                rx_channel_nums.push_back(std::stoi(rx_channel_strings[ch_idx]));
        }



    //// ====== Set mboard reference clock source (always has default value) ======
        tx_usrp->set_clock_source(ref);
        rx_usrp->set_clock_source(ref);

        std::cout << std::endl;
        std::cout<<boost::format("The reference clock for both Tx/Rx is: %s...") % ref
                    <<std::endl;



    //// ====== Reset timestamp and pps (always has default value) ======
        std::cout << boost::format("Setting device timestamp to 0 for the next unknown PPS edge...") << std::endl;

        tx_usrp->set_time_source(pps);
        rx_usrp->set_time_source(pps);
        
        tx_usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));  // set the next coming pps as t = 0;
        rx_usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));  // set the next coming pps as t = 0;
        // usrp->set_time_next_pps(uhd::time_spec_t(0.0));
        std::this_thread::sleep_for(
            std::chrono::seconds(1)); // wait for pps sync pulse
        
        std::cout<<std::endl;
        std::cout<<"t=0 timestamp set."
            <<std::endl;


    
    //// ====== Set the sample rate (always has default value) ======
        // set the Tx sample rate
        std::cout << boost::format("Setting Tx Rate: %f Msps...") % (tx_rate / 1e6) << std::endl;
        tx_usrp->set_tx_rate(tx_rate, tx_channels);  // remove the channels parameters or not?
        std::cout << boost::format("Actual Tx Rate: %f Msps...")
                        % (tx_usrp->get_tx_rate(tx_channels) / 1e6)
                << std::endl;

        // set the Rx sample rate
        std::cout << boost::format("Setting Rx Rate: %f Msps...") % (rx_rate / 1e6) << std::endl;
        rx_usrp->set_rx_rate(rx_rate, rx_channels);  // remove the channels parameters or not?
        std::cout << boost::format("Actual Rx Rate: %f Msps...")
                        % (rx_usrp->get_rx_rate(rx_channels) / 1e6)
                << std::endl;



    //// ====== Configure each channel ======
        // --- Tx channels ---
        for (size_t ch_idx = 0; ch_idx < tx_channel_nums.size(); ch_idx++) {

            size_t channel = tx_channel_nums[ch_idx];
                
            std::cout<<std::endl;
            std::cout << boost::format("Timed command: Setting Tx Freq: %f MHz...") 
                    % (freq / 1e6) << std::endl;
            std::cout << boost::format("Timed command: Setting Tx LO Offset: %f MHz...") 
                    % (tx_lo_offset / 1e6) << std::endl;            

            // start timed command with tune: 
            tx_usrp->clear_command_time();
            tx_usrp->set_command_time(uhd::time_spec_t(4.0));  //operate any command after "set_command_time" at t sec;           
            
                // timed command content:
                    uhd::tune_request_t tx_tune_request(freq, tx_lo_offset);
                    if (vm.count("tx-int-n"))
                        tx_tune_request.args = uhd::device_addr_t("mode_n=integer");
                    usrp->set_tx_freq(tx_tune_request, channel);
                    std::this_thread::sleep_for(std::chrono::milliseconds(110)); //sleep 110ms (~10ms after retune occurs) to allow LO to lock

            tx_usrp->clear_command_time();


            // print setting results
            std::cout<<std::endl;
            std::cout << boost::format("Actual Tx Freq: %f MHz...")
                            % (tx_usrp->get_tx_freq(channel) / 1e6)
                    << std::endl;


            // set the rf gain (always has default value)
            std::cout<<std::endl;
            std::cout << boost::format("Setting Tx Gain: %f dB...") % gain << std::endl;
            tx_usrp->set_tx_gain(tx_gain, channel);
            std::cout << boost::format("Actual Tx Gain: %f dB...")
                            % tx_usrp->get_tx_gain(channel)
                    << std::endl;


            // set the analog frontend filter bandwidth
            if (vm.count("tx-bw")) {
                std::cout<<std::endl;
                std::cout << boost::format("Setting Tx Bandwidth: %f MHz...") % (tx_bw / 1e6)
                        << std::endl;
                tx_usrp->set_tx_bandwidth(tx_bw, channel);
                std::cout << boost::format("Actual Tx Bandwidth: %f MHz...")
                                % tx_usrp->get_tx_bandwidth(channel / 1e6)
                        << std::endl;
            }

            // set the antenna (always has default value)
            tx_usrp->set_tx_antenna(tx_ant, channel);
        }


        // --- Rx channels ---
        for (size_t ch_idx = 0; ch_idx < rx_channel_nums.size(); ch_idx++) {

            size_t channel = rx_channel_nums[ch_idx];
                
            std::cout<<std::endl;
            std::cout << boost::format("Timed command: Setting Rx Freq: %f MHz...") 
                    % (freq / 1e6) << std::endl;
            std::cout << boost::format("Timed command: Setting Rx LO Offset: %f MHz...") 
                    % (lo_offset / 1e6) << std::endl;


            // start timed command with tune: 
            rx_usrp->clear_command_time();
            rx_usrp->set_command_time(uhd::time_spec_t(4.0));  //operate any command after "set_command_time" at t sec;
            
                // timed command content:
                    uhd::tune_request_t rx_tune_request(freq, rx_lo_offset);
                    if (vm.count("rx-int-n"))
                        rx_tune_request.args = uhd::device_addr_t("mode_n=integer");
                    usrp->set_tx_freq(rx_tune_request, channel);
                    std::this_thread::sleep_for(std::chrono::milliseconds(110)); //sleep 110ms (~10ms after retune occurs) to allow LO to lock

            rx_usrp->clear_command_time();


            // print setting results
            std::cout<<std::endl;
            std::cout << boost::format("Actual Rx Freq: %f MHz...")
                            % (rx_usrp->get_rx_freq(channel) / 1e6)
                    << std::endl;


            // set the rf gain (always has default value)
            std::cout<<std::endl;
            std::cout << boost::format("Setting Rx Gain: %f dB...") % gain << std::endl;
            rx_usrp->set_rx_gain(rx_gain, channel);
            std::cout << boost::format("Actual Rx Gain: %f dB...")
                            % rx_usrp->get_rx_gain(channel)
                    << std::endl;


            // set the analog frontend filter bandwidth
            if (vm.count("rx-bw")) {
                std::cout<<std::endl;
                std::cout << boost::format("Setting Rx Bandwidth: %f MHz...") % (rx_bw / 1e6)
                        << std::endl;
                rx_usrp->set_rx_bandwidth(rx_bw, channel);
                std::cout << boost::format("Actual Rx Bandwidth: %f MHz...")
                                % rx_usrp->get_rx_bandwidth(channel / 1e6)
                        << std::endl;
            }

            // set the antenna (always has default value)
            rx_usrp->set_rx_antenna(rx_ant, channel);
        }



    //// ====== Wait for Setup ======
        std::this_thread::sleep_for(std::chrono::seconds(1 * setup_time)); // allow for some setup time



    //// ====== Pre-compute wavetable ======
        signal_file = signal_file + ".txt";
        const wave_table_class wave_table(wave_type, ampl, signal_file);
        const size_t step = 1;
        size_t index = 0;



    //// ====== Create a transmit streamer ======
        // linearly map channels (index0 = channel0, index1 = channel1, ...)
        uhd::stream_args_t tx_stream_args("fc32", wirefmt);
        tx_stream_args.channels             = tx_channel_nums;
        uhd::tx_streamer::sptr tx_stream = tx_usrp->get_tx_stream(tx_stream_args);



    //// ====== Allocate a buffer which we re-use for each channel ======
        if (spb == 0) 
            spb = tx_stream->get_max_num_samps() * 10;
        std::vector<std::complex<float>> tx_buff(spb);
        int tx_size_channels = tx_channel_nums.size();  // not sure what it is

                        std::cout << std::endl;
                        std::cout << "Test: tx_size_channels =  " << tx_size_channels
                                << std::endl;

        std::vector<std::complex<float>*> buffs(tx_size_channels, &tx_buff.front());
    


    // //// ====== Pre-fill the buffer ======
    //     std::cout<<"size of Tx buffer is: "<<tx_buff.size()<<" and step is: " << step << std::endl;
    //     for (size_t n = 0; n < tx_buff.size(); n++) 
    //         tx_buff[n] = wave_table(index += step);


    
    //// ====== Set up metadata ======
        uhd::tx_metadata_t tx_md;
        tx_md.start_of_burst = true;
        tx_md.end_of_burst   = false;
        tx_md.has_time_spec  = true;
        tx_md.time_spec      = uhd::time_spec_t(tx_start); // test if the Tx will not send until t = 10. 

        std::cout<<std::endl;
        std::cout << "Wait for less than " << tx_md.time_spec.get_real_secs() << " seconds to start streaming..."
                << std::endl;
        std::cout<< "The meta data will not display untill the transmission is done. "
                << std::endl;



    //// ====== Check Ref and LO Lock detect ======
        // LO locking check
        std::vector<std::string> tx_sensor_names, rx_sensor_names;
        const size_t tx_sensor_chan = tx_channel_nums.empty() ? 0 : tx_channel_nums[0];   // in this case, the value is still 0
        tx_sensor_names = tx_usrp->get_tx_sensor_names(tx_sensor_chan);

                    std::cout << std::endl;
                    std::cout << boost::format("Test: Tx sensor name: %s") % tx_sensor_names
                            << std::endl;

        if (std::find(tx_sensor_names.begin(), tx_sensor_names.end(), "lo_locked")
            != tx_sensor_names.end()) {
            uhd::sensor_value_t lo_locked = tx_usrp->get_tx_sensor("lo_locked", tx_sensor_chan);
            std::cout << boost::format("Checking Tx: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }

        const size_t rx_sensor_chan = rx_channel_nums.empty() ? 0 : rx_channel_nums[0];   // in this case, the value is still 0
        rx_sensor_names = rx_usrp->get_rx_sensor_names(rx_sensor_chan);

                    std::cout << std::endl;
                    std::cout << boost::format("Test: Rx sensor name: %s") % rx_sensor_names
                            << std::endl;

        if (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "lo_locked")
            != rx_sensor_names.end()) {
            uhd::sensor_value_t lo_locked = rx_usrp->get_rx_sensor("lo_locked", rx_sensor_chan);
            std::cout << boost::format("Checking Rx: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }


        // Reference Clock
        tx_sensor_names = tx_usrp->get_mboard_sensor_names(0);
        if ((ref == "external")
            and (std::find(tx_sensor_names.begin(), tx_sensor_names.end(), "ref_locked")
                    != tx_sensor_names.end())) {
            uhd::sensor_value_t ref_locked = tx_usrp->get_mboard_sensor("ref_locked", 0);

                        std::cout << std::endl;
                        std::cout << boost::format("Test: Tx sensor name: %s") % tx_sensor_names
                                << std::endl;

            std::cout << boost::format("Checking Tx: %s ...") % ref_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }

        rx_sensor_names = rx_usrp->get_mboard_sensor_names(0);
        if ((ref == "external")
            and (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "ref_locked")
                    != rx_sensor_names.end())) {
            uhd::sensor_value_t ref_locked = rx_usrp->get_mboard_sensor("ref_locked", 0);

                        std::cout << std::endl;
                        std::cout << boost::format("Test: Rx sensor name: %s") % tx_sensor_names
                                << std::endl;

            std::cout << boost::format("Checking Rx: %s ...") % ref_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }



    //// ====== Rx streaming prints ======
        if (total_num_samps == 0) {
            std::signal(SIGINT, &sig_int_handler);
            std::cout << "Press Ctrl + C to stop streaming..." << std::endl;
        }



    //// ====== Start Tx ======
    boost::thread_group transmit_thread;
    transmit_thread.create_thread(boost::bind(
        &transmit_worker, tx_buff, wave_table, tx_stream, tx_md, step, index, tx_size_channels));



    //// ====== Start Rx ======
        #define recv_to_file_args(cpufmt)
            (rx_usrp,                   \
                cpufmt,                 \
                wirefmt,                \
                rx_channels,            \
                data_file,              \
                spb,                    \
                total_num_samps,        \
                total_time,             \
                rx_start,               \
                bw_summary,             \
                stats,                  \
                null,                   \
                enable_size_map,        \
                continue_on_bad_packet, \
                rx_channel_nums)



    if (data_type == "double")
        recv_to_file<std::complex<double>> recv_to_file_args("f64");
    else if (data_type == "float")
        recv_to_file<std::complex<float>> recv_to_file_args("f32");
    else if (data_type == "short")
        recv_to_file<std::complex<short>> recv_to_file_args("s16");
    else {
        // clean up transmit worker
        stop_signal_called = true;
        transmit_thread.join_all();
        throw std::runtime_error("Unknown type " + data_type);
    }

    // clean up transmit worker
    stop_signal_called = true;
    transmit_thread.join_all();

    // finished
    std::cout << std::endl << "Tx Done!" << std::endl << std::endl;
    return EXIT_SUCCESS;
}
