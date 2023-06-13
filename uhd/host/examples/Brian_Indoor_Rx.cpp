//
// Copyright 2011-2012,2014 Ettus Research LLC
// Copyright 2018 Ettus Research, a National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
//
// Modifier: Yuning (Brian) Zhang
// Copyright: 2023
//



/**********************************************
This code will be used as the Rx 
(USRP N310) for the indoor experiment. 

USRP Configuration reference: https://files.ettus.com/manual/page_usrp_n3xx.html
RF Configuration reference: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html
N310 UHD usage: https://files.ettus.com/manual/page_usrp_n3xx.html#n3xx_usage
**********************************************/



/*=========================================
Items waited to be implemented:
    1. Integrate Python as a library into C++
         - https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
    2. Automation logic for indoor experiment
        - Create the automation structure with necessary loops, put the integration of Python as pseudo code or comment to take the place only
    3. RF configuration block - pack as a subfunction or whatever to make the main code as simple as possible
Question:
    1. What is the difference between ant/channels/subdev?
    2. How to make the send buffer size as equal to the txt file length?
        - I want to achieve an action that each receive will full the assigned buffer, which MIGHT be a full repetition of the sounding signal, or multiple repetitions. 
    3. What are the values of "rx_starting_tick" and "rx_starting_sec"?
=========================================*/



// #include "wavetable_Brian.hpp"
#include <uhd/exception.hpp>
#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/math/special_functions/round.hpp>
#include <chrono>
#include <complex>
#include <csignal>
#include <fstream>
#include <iostream>
#include <thread>  // to solve error: this_thread and std::chrono is not declared
#include <string>
namespace po = boost::program_options;





/***********************************************************************
 * recv_to_file function - one time action
 * @param usrp a created usrp object
 * @param rx_stream a created receiver streamer
 * @param write_file the name of the file that will store the data
 * @param samps_per_buff buffer size, should equals to "num_requested_samples"
 * @param num_requested_samples the total number of samples that will be captured
 * @param start_streaming_delay the delay that USRP will wait after it receives a 1 PPS trigger
 **********************************************************************/
template <typename samp_type>
void recv_to_file(uhd::usrp::multi_usrp::sptr usrp,         // a USRP object
    uhd::tx_streamer::sptr rx_stream                        // Tx streamer
    const std::string&  write_file,                         // file name to save data
    size_t              samps_per_buff,                     // buffer size to save data
    size_t              num_requested_samples,              // total number of samples to be received
    double              start_streaming_delay    = 3.0,    // how many seconds to start streaming after the Rx USRP receives its first 1 PPS
    )
{
    //// ====== Define Variables ======
        // system parameters
        bool continue_on_bad_packet     = false;
        bool stats                      = true;
        size_t num_received_samps       = 0;   // number of samples have received so far
        size_t num_rx_samps_tmp         = 0;
        const double timeout            = 10.0;   // in sec

        // Rx metadata
        uhd::rx_metadata_t rx_metadata;

        // define buffer
        std::vector<samp_type> buff(samps_per_buff);

        // Set up data writing
        std::ofstream data_file;
        char full_file_name[200];
        strcpy(full_file_name, write_file.c_str());
        strcat(full_file_name, ".dat");
        data_file.open(full_file_name, std::ofstream::binary);

        // Set up metadata writing
        std::ofstream metadata_file;
        char full_metafile_name[200];

    //// ====== Configurations ======
        // Setup streaming command - each receiving action will be achieved by issuing a streaming command
        uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);
                        
        // Number of samples to receive
        stream_cmd.num_samps  = size_t(num_requested_samples);

        // time to receive samples
        stream_cmd.stream_now = false;  // do NOT set it as true - otherwise the synchronization status will be lost!
        uhd::time_spec_t time_to_recv = uhd::time_spec_t(start_streaming_delay);
        stream_cmd.time_spec  = time_to_recv;
        /* USRP configured item:
            * streaming mode: continuous
            * number of samples to receive every time
            * when to stream (related to synchronization) - stream_now & time_spec
        */
        rx_stream->issue_stream_cmd(stream_cmd);    // configure the USRP accordingly

        // print starting info
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Rx: capturing will start in " << time_to_recv.get_real_secs() << " seconds..."
            << std::endl;

        // Mark the starting timestamp
        const auto start_time = std::chrono::steady_clock::now();

    //// ====== Receive and Write Data ======
        // Receive samples into the pre-assigned buffer
        num_rx_samps_tmp =
            rx_stream->recv(&buff.front(), buff.size(), rx_metadata, timeout);

        // Define error cases
            // - 1 - Time out
            if (rx_metadata.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
                std::cout << boost::format("Timeout while streaming") << std::endl;
                break;}
            // - 2 - Overflow
            if (rx_metadata.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
                std::cerr
                    << boost::format(
                        "Got an overflow indication. Please consider the following:\n"
                        "  Your write medium must sustain a rate of %fMB/s.\n"
                        "  Dropped samples will not be written to the file.\n"
                        "  Please modify this example for your purposes.\n")
                        % (usrp->get_rx_rate() * sizeof(samp_type) / 1e6);
                continue;}
            // - 3 - Other errors
            if (rx_metadata.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
                std::string error = str(boost::format("Receiver error: %s") % rx_metadata.strerror());
                if (continue_on_bad_packet) {
                    std::cerr << error << std::endl;
                    continue;
                } else
                    throw std::runtime_error(error);}

        // update Rx sample counter
        num_received_samps += num_rx_samps_tmp;

        // write data to file from buffer
        data_file.write((const char*)&buff.front(), num_rx_samps_tmp * sizeof(samp_type));       

        // Mark the starting timestamp
        const auto actual_stop_time = std::chrono::steady_clock::now();

    //// ====== Wrap up ======
        // close files
        data_file.close();

        // shut down receiver
        stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
        rx_stream->issue_stream_cmd(stream_cmd);       

        // print Rx finishes
        std::cout<<std::endl;
        std::cout<< "Rx Done!" <<std::endl;

    //// ====== Status check ======
        std::cout << std::endl;
        const double actual_duration_seconds =
            std::chrono::duration<float>(actual_stop_time - start_time).count();

        std::cout << boost::format("Received %d samples in %f seconds") % num_received_samps
                        % actual_duration_seconds
                << std::endl;
        const double rate_checked = (double)num_received_samps / actual_duration_seconds;
        std::cout << (rate_checked / 1e6) << " Msps" << std::endl;

    //// ====== Process Metadata ======
        long long rx_starting_tick = rx_metadata.time_spec.to_ticks(200e6);
        double rx_starting_sec = rx_metadata.time_spec.get_real_secs();
        std::cout << "Metadata Here... " << std::endl;
        std::cout << "  Streaming starting tick = " << rx_starting_tick << std::endl;
        std::cout << "  Streaming starting sec = " << rx_starting_sec 
                    << std::endl
                    << std::endl;
        
        strcpy(full_metafile_name, write_file.c_str());
        strcat(full_metafile_name, "_metadata.dat");
        metadata_file.open(full_metafile_name, std::ofstream::binary);
        metadata_file.write((char*)&rx_starting_tick, sizeof(long long));
        metadata_file.close();

        std::cout << "===============================" << std::endl;
        std::cout << boost::format("Data is saved in file: %s") % full_file_name
                << std::endl
                << std::endl;

        std::cout << boost::format("Metadata is saved in file: %s") % full_metafile_name
                << std::endl;
        std::cout << "===============================" << std::endl;
} // "recv_to_file()" ends




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




/***********************************************************************
 * Main function
 * @return None.
 **********************************************************************/
int UHD_SAFE_MAIN(int argc, char* argv[])
{
    //// ====== Setup Variables ======
        //constant variables
        /* --- Timing configuration ---
        Reference: 
            1 PPS: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a57a5580ba06d7d6a037c9ef64f1ea361
            Ref: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a73ed40009d0d3787c183d42423d25026
        */
        const std::string pps = "external";
        const std::string ref = "external";

        /* --- RF configuration --- */
        const double rx_rate = 200e6;  // Tx sampling rate, in Samples/sec
        const double rx_bw = 100e6;    // Transmission bandwidth, in Hz
        const double freq = 3e9;    // 1st-stage IF center frequency, in Hz, should be 3 GHz. Then PAAM will keep UPC from 3 GHz to 28 GHz.


    // variables to be set by po
    std::string rx_args, write_file, data_type, rx_ant, rx_subdev, wirefmt, rx_channels;
    size_t num_samps_to_recv, spb;
    double rx_gain, total_time, setup_time, rx_lo_offset, rx_start;


    // setup the program options
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        ("help", "help message")

        ("rx-ant", po::value<std::string>(&rx_ant)->default_value("AB"), "antenna selection")
        ("rx-args", po::value<std::string>(&rx_args)->default_value("addr=10.38.14.2"), "multi uhd device address args")
        // ("rx-bw", po::value<double>(&rx_bw), "analog frontend filter bandwidth in Hz")
        ("rx-channels", po::value<std::string>(&rx_channels)->default_value("0"), "which channels to use (specify \"0\", \"1\", \"0,1\", etc)")
        ("rx-continue", "don't abort on a bad packet")
        ("rx-duration", po::value<double>(&total_time)->default_value(0), "total number of seconds to receive")
        ("rx-file", po::value<std::string>(&write_file)->default_value("usrp_samples.dat"), "name of the file to write binary samples to")
        ("rx-gain", po::value<double>(&rx_gain)->default_value(6), "gain for the RF chain")
        ("rx-int-n", "tune USRP with integer-N tuning")
        ("rx-lo-offset", po::value<double>(&rx_lo_offset)->default_value(0.0),
            "Offset for frontend LO in Hz (optional)")
        ("rx-nsamps", po::value<size_t>(&num_samps_to_recv)->default_value(0), "total number of samples to receive (requested)")     
        // ("rx-null", "Determine if run the code and save data to file. Add 'null' when you don't want to save the data. ")
        ("rx-progress", "periodically display short-term bandwidth")
        // ("rx-rate", po::value<double>(&rx_rate)->default_value(200e6), "rate of incoming samples")
        ("rx-sizemap", "track packet size and display breakdown on exit")
        ("rx-skip-lo", "skip checking LO lock status")
        ("rx-start", po::value<double>(&rx_start)->default_value(15.0), "start streaming time")
        ("rx-stats", "show average bandwidth on exit")
        ("rx-subdev", po::value<std::string>(&rx_subdev)->default_value("B:AB"), "subdevice specification")
        ("rx-type", po::value<std::string>(&data_type)->default_value("double"), "sample type: double, float, or short")
                
        // ("freq", po::value<double>(&freq)->default_value(100e6), "IF center frequency in Hz")
        // ("pps", po::value<std::string>(&pps)->default_value("external"), "PPS source (internal, external, mimo, gpsdo)")
        // ("ref", po::value<std::string>(&ref)->default_value("external"), "reference source (internal, external, mimo)")
        ("setup", po::value<double>(&setup_time)->default_value(1.0), "seconds of setup time")
        ("spb", po::value<size_t>(&spb)->default_value(10000), "samples per buffer")
        ("wirefmt", po::value<std::string>(&wirefmt)->default_value("sc16"), "wire format (sc8, sc16 or s16)")
    ;


    //// ====== Clang-format on ======
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);



    //// ====== Print the help message ======
        if (vm.count("help")) {
            std::cout << boost::format("UHD Rx receiving by WiDeS %s") % desc << std::endl;
            std::cout << std::endl
                    << "This application streams data from a single channel of a USRP "
                        "device to a file.\n"
                    << std::endl;
            return ~0;
        }



    //// ====== Create Rx USRP Devices ======
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % rx_args
                << std::endl;
        uhd::usrp::multi_usrp::sptr rx_usrp = uhd::usrp::multi_usrp::make(rx_args);



    //// ====== Select Sub-device (always has default value) ======
        rx_usrp->set_rx_subdev_spec(rx_subdev);
    


    //// ====== Print Device Info ======
        // "get_pp_string" will return:
        //  1. USRP clock device;
        //  2. board amount, and their references;
        std::cout << std::endl;
        std::cout << boost::format("Using RX Device: %s") % rx_usrp->get_pp_string()
                << std::endl;



    //// ====== Detect which channels to use ======
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
        rx_usrp->set_clock_source(ref);

        std::cout << std::endl;
        std::cout<<boost::format("The reference clock for the Rx is: %s...") % ref
                    <<std::endl;



    //// ====== Reset timestamp and pps (always has default value) ======
        std::cout << boost::format("Setting device timestamp to 0 for the next unknown PPS edge...") << std::endl;

        rx_usrp->set_time_source(pps);

        rx_usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));  // set the next coming pps as t = 0;
        std::this_thread::sleep_for(
            std::chrono::milliseconds(200)); // wait for pps sync pulse
        std::cout << "Current Rx time is: " << rx_usrp->get_time_now(0).get_real_secs() << std::endl;
        
        std::cout<<std::endl;
        std::cout<<"t=0 timestamp set."
            <<std::endl;
        


    //// ====== Set the sample rate (always has default value) ======
        // set the Rx sample rate
        std::cout << std::endl;
        std::cout << boost::format("Setting Rx Rate: %f Msps...") % (rx_rate / 1e6) << std::endl;
        rx_usrp->set_rx_rate(rx_rate);  // remove the channels parameters or not?
        std::cout << boost::format("Actual Rx Rate: %f Msps...")
                        % (rx_usrp->get_rx_rate() / 1e6)
                << std::endl;
              


    //// ====== Configure each channel ======
        for (size_t ch_idx = 0; ch_idx < rx_channel_nums.size(); ch_idx++) {

            size_t channel = rx_channel_nums[ch_idx];
                
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << boost::format("Timed command: Setting Rx Freq: %f MHz...") 
                    % (freq / 1e6) << std::endl;
            std::cout << boost::format("Timed command: Setting Rx LO Offset: %f MHz...") 
                    % (rx_lo_offset / 1e6) << std::endl;


            // start timed command with tune: 
            rx_usrp->clear_command_time();
            rx_usrp->set_command_time(uhd::time_spec_t(4.0));  //operate any command after "set_command_time" at t sec;
            
                // timed command content:
                    uhd::tune_request_t rx_tune_request(freq, rx_lo_offset);
                    if (vm.count("rx-int-n"))
                        rx_tune_request.args = uhd::device_addr_t("mode_n=integer");
                    rx_usrp->set_rx_freq(rx_tune_request, channel);
                    std::this_thread::sleep_for(std::chrono::milliseconds(110)); //sleep 110ms (~10ms after retune occurs) to allow LO to lock

            rx_usrp->clear_command_time();


            // print setting results
            std::cout<<std::endl;
            std::cout << boost::format("Actual Rx Freq: %f MHz...")
                            % (rx_usrp->get_rx_freq(channel) / 1e6)
                    << std::endl;


            // set the rf gain (always has default value)
            std::cout << std::endl;
            std::cout << boost::format("Setting Rx Gain: %f dB...") % rx_gain << std::endl;
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
        std::this_thread::sleep_for(std::chrono::seconds(int64_t(1 * setup_time))); // allow for some setup time



    //// ====== Check Ref and LO Lock detect ======
        // LO locking check
        std::vector<std::string> rx_sensor_names;
        const size_t rx_sensor_chan = rx_channel_nums.empty() ? 0 : rx_channel_nums[0];   // in this case, the value is still 0
        rx_sensor_names = rx_usrp->get_rx_sensor_names(rx_sensor_chan);

        if (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "lo_locked")
            != rx_sensor_names.end()) {
            uhd::sensor_value_t lo_locked = rx_usrp->get_rx_sensor("lo_locked", rx_sensor_chan);
            std::cout << std::endl;
            std::cout << boost::format("Checking Rx: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());
        }

        rx_sensor_names = rx_usrp->get_mboard_sensor_names(0);
        if ((ref == "external")
            and (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "ref_locked")
                    != rx_sensor_names.end())) {
            uhd::sensor_value_t ref_locked = rx_usrp->get_mboard_sensor("ref_locked", 0);
            std::cout << std::endl;
            std::cout << boost::format("Checking Rx: %s ...") % ref_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());
        }



    //// ====== Create a receive streamer ======
        // refer to: https://files.ettus.com/manual/page_configuration.html#config_stream_args_cpu_format
        std::string cpu_format = "f32"; // Single-precision 32-bit data
        std::string wirefmt = "s16"; // Signed 16-bit integer data
        uhd::stream_args_t stream_args(cpu_format, wire_format);
        rx_channel_nums.push_back(boost::lexical_cast<size_t>(rx_channels)); // copied from Brian_Indoor_Tx.cpp
        stream_args.channels = rx_channel_nums;
        uhd::rx_streamer::sptr rx_stream = usrp->get_rx_stream(stream_args);

 
    
    //// ====== Start Rx ======
        // figure out a way to set spb = rep * signal_length
        recv_to_file<std::complex<double>>(
            rx_usrp, rx_stream, write_file, spb, num_samps_to_recv, rx_start);



    
    return EXIT_SUCCESS;
}
