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
    2. Tuning: https://files.ettus.com/manual/page_general.html#general_tuning
    3. Data format for CPU and in-wire: https://files.ettus.com/manual/page_configuration.html#config_stream_args_cpu_format
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
        - A: refer to the Section Q&A in overleaf. 
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




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////




/***********************************************************************
 * Main function
 * @param gain
 * @param file
 * @param spb
 * @return None.
 **********************************************************************/
int UHD_SAFE_MAIN(int argc, char* argv[])
{
    //// ====== Setup Variables ======
        // USRP Config - USRP 2974 (mob4-1)
            // RF0 - Tx(H)+Rx(H); RF1 - Tx(V)+Rx(V). We are using the Tx port on RF1 (assuming it's the second daughterboard)
        const std::string tx_ant = "TX/RX"; // antenna port selection: https://files.ettus.com/manual/page_dboards.html#dboards_ubx
        const size_t tx_channel = 0;    // the concept of "channel" is logic one, it doesn't mean a physical connection..? 
        const std::string tx_subdev = "B:0";    // for now keep it as B:channel
        const std::string tx_args = "addr=10.37.21.1"; // mob4-1 address: https://files.ettus.com/manual/page_usrp_x3x0.html#x3x0_usage_device_args

        // Timing
        const std::string pps = "external"; // https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a57a5580ba06d7d6a037c9ef64f1ea361
        const std::string ref = "external"; // https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a73ed40009d0d3787c183d42423d25026
        
        // RF configuration
        const double tx_rate = 200e6;  // Tx sampling rate, in Samples/sec
        const double IF_freq = 3e9;    // 1st-stage IF center frequency, in Hz, should be 3 GHz. Then PAAM will keep UPC from 3 GHz to 28 GHz. 
    

        // variables to be set by po
        std::string filename_read;
        size_t spb;
        double tx_gain;
        
        po::options_description desc("Allowed options");    // setup the program options
        desc.add_options()
            ("help", "help message")

            // RF parameters
            ("gain", po::value<double>(&tx_gain)->default_value(0), "gain for the Tx USRP, 0~31.5dB")

            // sounding signal/transmission
            ("file", po::value<std::string>(&filename_read)->default_value(""), "name of the txt file to read samples - will be a known file name")
            ("spb", po::value<size_t>(&spb)->default_value(10000), "samples per buffer")
        ;



    //// ====== Preparation ======
        // clang-format on
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // print the help message
        if (vm.count("help")) {
            std::cout << boost::format("UHD TX samples from file %s") % desc << std::endl;
            return ~0;}

        // input check
        if (not vm.count("tx_gain")) {
            std::cerr << "Please specify the RF gain with --tx_gain" << std::endl;
            return ~0;}
        if (not vm.count("filename_read")) {
            std::cerr << "Please specify the sounding signal source file name with --file" << std::endl;
            return ~0;}
        if (not vm.count("spb")) {
            std::cerr << "Please specify the buffer size with --spb" << std::endl;
            return ~0;}



    //// ====== Configure USRP ======
        // --- create a usrp device ---
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % tx_args
                << std::endl;
        uhd::usrp::multi_usrp::sptr tx_usrp = uhd::usrp::multi_usrp::make(tx_args);

        // --- select subdevice (always use default value) ---
        tx_usrp->set_tx_subdev_spec(tx_subdev);

        // --- set timing ---
        tx_usrp->set_clock_source(ref); // ref as external
        tx_usrp->set_time_source(pps);  // pps as external
        std::cout<<boost::format("The reference clock source is: %s...") % ref
            <<std::endl;
        std::cout<<boost::format("The PPS signal source is: %s...") % pps
            <<std::endl;
        tx_usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));   // set timestamp: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a413014bf3aea4a8ea2d268b4a3b390e9
        std::cout << boost::format("Device timestamp has been set to 0.")
            << std::endl;

        // --- set sampling rate ---
        tx_usrp->set_tx_rate(tx_rate);        
        std::cout << boost::format("TX sampling rate has been set to: %f Msps...") % (tx_usrp->get_tx_rate() / 1e6)
            << std::endl;

        // --- set IF tuning ---
        uhd::tune_request_t tune_request(IF_freq);  // specify the frequency
        tune_request.args = uhd::device_addr_t("mode_n=integer");   // tune the USRP with integer-N mode
        tx_usrp->set_tx_freq(tune_request, tx_channel);
        std::cout << boost::format("TX IF frequency has been set to: %f MHz...") % (tx_usrp->get_tx_freq(tx_channel) / 1e6)
            << std::endl;

        // --- set RF gain ---
        tx_usrp->set_tx_gain(tx_gain, tx_channel);
        std::cout << boost::format("TX gain has been set to: %f dB...") % tx_usrp->get_tx_gain(tx_channel)
            << std::endl;

        // --- set the antenna ---
        tx_usrp->set_tx_antenna(tx_ant, tx_channel);

        // --- consolidate configuration
        std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time

        // --- checking LO and Ref locking status ---
        std::vector<std::string> sensor_names;
        sensor_names = tx_usrp->get_tx_sensor_names(tx_channel); // get the Tx sensor names for channel: tx_channel
                // ...... [Debug] --> print the list of available Tx sensors ......
                std::cout << "......................................" << std::endl;
                std::cout << "Available Tx sensors:" << std::endl;
                for (const auto& sensor_name : sensor_names) {
                    std::cout << "  - " << sensor_name
                            << std::endl
                            << std::endl;}
                std::cout << "......................................" << std::endl;
                // .............................................................
        if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")    // if "lo_locked" sensor is detected
            != sensor_names.end()) {
            uhd::sensor_value_t lo_locked = tx_usrp->get_tx_sensor("lo_locked", tx_channel);
            std::cout << boost::format("TX LO locking status: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());}

        sensor_names = tx_usrp->get_mboard_sensor_names(0); // there is only 1 motherboard in this USRP so the index of it is: 0
                // ...... [Debug] --> print the list of available motherboard sensors ......
                std::cout << "......................................" << std::endl;
                std::cout << "Available motherboard sensors:" << std::endl;
                for (const auto& sensor_name : sensor_names) {
                    std::cout << "  - " << sensor_name
                            << std::endl
                            << std::endl;}
                std::cout << "......................................" << std::endl;
                // .............................................................
        if (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked") != sensor_names.end()) {    // if "ref_locked" sensor is detected
            uhd::sensor_value_t ref_locked = tx_usrp->get_mboard_sensor("ref_locked", 0);
            std::cout << boost::format("TX reference locking status: %s ...") % ref_locked.to_pp_string()
                    << std::endl
                    << std::endl
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());}

        

        // --- print overall USRP info ---
        std::cout << boost::format("TX USRP Device Info: %s") % tx_usrp->get_pp_string() << std::endl;



    //// ====== Prepare for Transmitting ======
        // --- create a transmit streamer ---
        std::string cpu_format = "f32"; // Single-precision 32-bit data
        std::string wire_format = "s16"; // Signed 16-bit integer data
        uhd::stream_args_t stream_args(cpu_format, wire_format);
        std::vector<size_t> stream_args_channels;
        stream_args_channels.push_back(tx_channel);
        stream_args.channels = stream_args_channels;
        uhd::tx_streamer::sptr tx_stream = tx_usrp->get_tx_stream(stream_args);

        // Setup metadata
        uhd::tx_metadata_t tx_metadata;
        tx_metadata.start_of_burst = false;
        tx_metadata.end_of_burst   = false;

        // define buffer
        std::vector<std::complex<double>> buff(spb);

        // Set up data reading and read sample data from txt file to pre-assigned buffer
        // data is saved in "buff". Note: Tx doesn't have stream_cmd to issue. 
        std::ifstream signal_file(filename_read.c_str(), std::ifstream::binary);
        signal_file.read((char*)&buff.front(), buff.size() * sizeof(std::complex<double>));
        size_t num_tx_samps = size_t(signal_file.gcount() / sizeof(std::complex<double>));  // the number of samples will be transmitted at one time



    //// ====== Set sigint if user wants to stop ======
        std::signal(SIGINT, &sig_int_handler);
        std::cout << "Press Ctrl + C to stop transmitting..." << std::endl;



    //// ====== Continuously transmitting ======
        // Not 100% sure if there will be software/systmetic processing time between two calls of the send_from_file() function. 
        // If there is, then we need to modify the while-loop structure or logic in the send_from_file() and make the continuouty there
        // so that it can be a continuous action instead of a one-time action.  
        while (not stop_signal_called) {
            tx_stream->send(&buff.front(), num_tx_samps, tx_metadata);}



    //// ====== Wrap up ======
        // close file
        signal_file.close();

        // print Tx finishes
        std::cout << std::endl << "Tx Done!" << std::endl << std::endl;
        return EXIT_SUCCESS;
}
