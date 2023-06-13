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
This code will be used as the Tx 
(USRP 2974) for the indoor experiment. 

USRP-2974 is the equivalent to a USRP X310 with two UBX-160 boards, a GPSDO and an onboard Intel i7 computer.

USRP Configuration reference: https://files.ettus.com/manual/page_usrp_x3x0.html
RF Configuration reference: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html
**********************************************/


/*------------------------------------
Notes:
    1. USRP Interface should be set to 10 Gigabit Ethernet - makes max sampling rate as 200MS/s (https://kb.ettus.com/About_USRP_Bandwidths_and_Sampling_Rates)
------------------------------------*/



/*=========================================
Items waited to be implemented:
    1. Integrate Python as a library into C++
         - https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
    2. RF configuration block - pack as a subfunction or whatever to make the main code as simple as possible
    3. Double check the continuouty of this code: need to verify if it is actually continuously transmission. The verification can be checked via received data with multiple repetion of data. 
         - check if there is a pause or gap between every two consecutive repetition of sounding signal from data. 
         - We may even have to use the stream_cmd_t to set the Tx streaming mode as continuous. 
Question:
    1. What is the difference between ant/channels/subdev?
    2. How to make the send buffer size as equal to the txt file length?
        - I want to achieve an action that each send will empty the assigned buffer, whose size is a full repetition of the sounding signal. 
        So: buffer size = sounding signal size = txt file sample amount
=========================================*/



#include <uhd/types/tune_request.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/thread.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <complex>
#include <csignal>
#include <fstream>
#include <iostream>
#include <thread>
#include <string>
namespace po = boost::program_options;


/***********************************************************************
 * Signal handlers
 **********************************************************************/
static bool stop_signal_called = false;
void sig_int_handler(int)
{
    stop_signal_called = true;
} // sig_int_handler ends



/***********************************************************************
 * send_from_file function - one time action
 **********************************************************************/
template <typename samp_type>
void send_from_file(
    uhd::tx_streamer::sptr tx_stream, const std::string& read_file, size_t samps_per_buff)
{
    // Tx metadata
    uhd::tx_metadata_t tx_metadata;
    tx_metadata.start_of_burst = false;
    tx_metadata.end_of_burst   = false;
    
    // define buffer
    std::vector<samp_type>  buff(samps_per_buff);
    
    // Setup data reading
    std::ifstream signal_file(read_file.c_str(), std::ifstream::binary);


    /********************
     * Perhaps there is a need to use stream command to control the bahavior of the Tx streamer
    ********************/



    // loop until the entire file has been read
    while (not tx_metadata.end_of_burst and not stop_signal_called) {
        // read sample data from txt file to pre-assigned buffer
        signal_file.read((char*)&buff.front(), buff.size() * sizeof(samp_type));
        size_t num_tx_samps = size_t(signal_file.gcount() / sizeof(samp_type));

        tx_metadata.end_of_burst = signal_file.eof();

        tx_stream->send(&buff.front(), num_tx_samps, tx_metadata);
    }

    signal_file.close();
} // send_from_file ends







///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////



/***********************************************************************
 * Main function
 * @param 
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
        const double rate = 200e6;  // Tx sampling rate, in Samples/sec
        const double bw = 100e6;    // Transmission bandwidth, in Hz
        const double freq = 3e9;    // 1st-stage IF center frequency, in Hz, should be 3 GHz. Then PAAM will keep UPC from 3 GHz to 28 GHz. 
    

        // variables to be set by po
        std::string args, read_file, ant, subdev, tx_channels;
        size_t spb;
        double gain;
        
        po::options_description desc("Allowed options");    // setup the program options
        desc.add_options()
            ("help", "help message")

            /*
            For USRP 2974, RF0 - Tx(H)+Rx(H); RF1 - Tx(V)+Rx(V).
            Most likely, the subdev should be: B:0
            Refer to: https://files.ettus.com/manual/page_dboards.html#dboards_ubx

            set "args" as USRP's address
            Refer to: https://files.ettus.com/manual/page_usrp_x3x0.html#x3x0_usage_device_args
            */
            ("ant", po::value<std::string>(&ant)->default_value("AB"), "antenna selection")
            ("channels", po::value<std::string>(&tx_channels)->default_value("0"), "which channels to use (specify \"0\", \"1\", \"0,1\", etc)")
            ("subdev", po::value<std::string>(&subdev)->default_value("A:AB"), "subdevice specification")
            ("args", po::value<std::string>(&args)->default_value("addr=10.37.21.1"), "USRP addresses, default is for the portable node mob4")

            // RF parameters
            ("gain", po::value<double>(&gain)->default_value(0), "gain for the Tx USRP")
            ("int-n", "tune USRP with integer-n tuning")

            // sounding signal/transmission
            ("file", po::value<std::string>(&read_file)->default_value(""), "name of the txt file to read samples - will be a known file name")
            ("spb", po::value<size_t>(&spb)->default_value(10000), "samples per buffer")  
        ;



    //// ====== Clang-format on ======
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);



    //// ====== Print the help message ======
        if (vm.count("help")) {
            std::cout << boost::format("UHD TX samples from file %s") % desc << std::endl;
            return ~0;
        }



    //// ====== Create a usrp device ======
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % args
                << std::endl;
        // uhd is defined at "<uhd/usrp/multi_usrp.hpp>"   
        uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);



    //// ====== Select Sub-device (always use default value) ======
        if (vm.count("subdev"))
            usrp->set_tx_subdev_spec(subdev);  // A:AB for Tx, and B:AB for Rx, check the "X310 probe" note in Samsung Notes
    
    

    //// ====== Detect which channels to use ======
        std::vector<std::string> tx_channel_strings;
        std::vector<size_t> tx_channel_nums;
        boost::split(tx_channel_strings, tx_channels, boost::is_any_of("\"',"));
        for (size_t ch_idx = 0; ch_idx < tx_channel_strings.size(); ch_idx++) {
            size_t chan = std::stoi(tx_channel_strings[ch_idx]);
            if (chan >= usrp->get_tx_num_channels())
                throw std::runtime_error("Invalid channel(s) specified.");
            else
                tx_channel_nums.push_back(std::stoi(tx_channel_strings[ch_idx]));
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
        for (size_t ch_idx = 0; ch_idx < tx_channel_nums.size(); ch_idx++) {
            std::cout << boost::format("Setting TX Freq: %f MHz...") % (freq / 1e6) 
                    << std::endl;
            uhd::tune_request_t tune_request(freq);
            if (vm.count("int-n"))
                tune_request.args = uhd::device_addr_t("mode_n=integer");
            usrp->set_tx_freq(tune_request, tx_channel_nums[ch_idx]);
            std::cout << boost::format("Actual TX Freq: %f MHz...") 
                            % (usrp->get_tx_freq(tx_channel_nums[ch_idx]) / 1e6)
                    << std::endl
                    << std::endl;

            // set the rf gain (always has default value)
                std::cout << boost::format("Setting TX Gain: %f dB...") % gain << std::endl;
                usrp->set_tx_gain(gain, tx_channel_nums[ch_idx]);
                std::cout << boost::format("Actual TX Gain: %f dB...") 
                                % usrp->get_tx_gain(tx_channel_nums[ch_idx])
                        << std::endl
                        << std::endl;
            

            // set the analog frontend filter bandwidth
            if (vm.count("bw")) {
                std::cout << boost::format("Setting TX Bandwidth: %f MHz...") % (bw / 1e6)
                        << std::endl;
                usrp->set_tx_bandwidth(bw, tx_channel_nums[ch_idx]);
                std::cout << boost::format("Actual TX Bandwidth: %f MHz...")
                                % usrp->get_tx_bandwidth(tx_channel_nums[ch_idx] / 1e6)
                        << std::endl
                        << std::endl;
            }


            // set the antenna
            if (vm.count("ant"))
                usrp->set_tx_antenna(ant, tx_channel_nums[ch_idx]);
        }





    std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time




    //// ====== Set timestamp and pps ======
        std::cout << boost::format("Setting device timestamp to 0...") << std::endl;
        std::cout << "channel num = " << tx_channel_nums.size()<< std::endl;
        if (tx_channel_nums.size() >= 1) {
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
        const size_t tx_sensor_chan = tx_channel_nums.empty() ? 0 : tx_channel_nums[0];
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


    //// ************ copied from test_pps_input *********************
        // set the time at an unknown pps (will throw if no pps)
        std::cout << std::endl
                << "Attempt to detect the PPS and set the time..." << std::endl
                << std::endl;
        usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));
        std::cout << std::endl << "Success!" << std::endl << std::endl;

        if (product_requires_reflock(usrp->get_mboard_name())) {
            std::cout << "Product requires verification of ref_locked sensor!" << std::endl;
            std::cout << "Checking ref_locked sensor..." << std::flush;
            if (!usrp->get_mboard_sensor("ref_locked").to_bool()) {
                std::cout << "FAIL!" << std::endl;
                return EXIT_FAILURE;
            }
            std::cout << "PASS!" << std::endl;
        }



    //// ====== Set sigint if user wants to stop ======
        std::signal(SIGINT, &sig_int_handler);
        std::cout << "Press Ctrl + C to stop transmitting..." << std::endl;



    //// ====== Create a transmit streamer ======
        // refer to: https://files.ettus.com/manual/page_configuration.html#config_stream_args_cpu_format
        std::string cpu_format = "f32"; // Single-precision 32-bit data
        std::string wirefmt = "s16"; // Signed 16-bit integer data
        uhd::stream_args_t stream_args(cpu_format, wirefmt);
        tx_channel_nums.push_back(boost::lexical_cast<size_t>(tx_channels));
        stream_args.channels = tx_channel_nums;
        uhd::tx_streamer::sptr tx_stream = usrp->get_tx_stream(stream_args);



    //// ====== Continuosly Send data ======
        // Not 100% sure if there will be software/systmetic processing time between two calls of the send_from_file() function. 
        // If there is, then we need to modify the while-loop structure or logic in the send_from_file() and make the continuouty there
        // so that it can be a continuous action instead of a one-time action.  
        do {
            send_from_file<float>(tx_stream, read_file, spb);
        } while (not stop_signal_called);



    //// finished
        std::cout << std::endl << "Done!" << std::endl << std::endl;
        return EXIT_SUCCESS;
}
