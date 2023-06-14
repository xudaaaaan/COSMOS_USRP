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
    3. Should "mboard_sensor_idx = 0;" or "mboard_sensor_idx = 1;"?
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
 * @param ant
 * @param channel
 * @param subdev
 * @param args
 * @param gain
 * @param file
 * @param spb
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
        const double IF_freq = 3e9;    // 1st-stage IF center frequency, in Hz, should be 3 GHz. Then PAAM will keep UPC from 3 GHz to 28 GHz. 
    

        // variables to be set by po
        std::string args, filename_read, tx_ant, tx_subdev;
        size_t spb, tx_channel;
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
            ("ant", po::value<std::string>(&tx_ant)->default_value("TX/RX"), "antenna selection")
            ("channel", po::value<size_t>(&tx_channel)->default_value(0), "which channels to use (specify 0 or 1 for single channel usage)")
            ("subdev", po::value<std::string>(&tx_subdev)->default_value("B:0"), "subdevice specification")  // for now just keep it as: B:channel
            ("args", po::value<std::string>(&args)->default_value("addr=10.37.21.1"), "USRP addresses, default is for the portable node mob4")

            // RF parameters
            ("gain", po::value<double>(&gain)->default_value(0), "gain for the Tx USRP, 0~31.5dB")

            // sounding signal/transmission
            ("file", po::value<std::string>(&filename_read)->default_value(""), "name of the txt file to read samples - will be a known file name")
            ("spb", po::value<size_t>(&spb)->default_value(10000), "samples per buffer");



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
        if (not vm.count("ant")) {
            std::cerr << "Please specify the antenna port with --ant" << std::endl;
            return ~0;}
        if (not vm.count("channel")) {
            std::cerr << "Please specify the channel on USRP with --channel" << std::endl;
            return ~0;}
        if (not vm.count("subdev")) {
            std::cerr << "Please specify the subdev with --subdev" << std::endl;
            return ~0;}
        if (not vm.count("args")) {
            std::cerr << "Please specify the USRP address with --args" << std::endl;
            return ~0;}
        if (not vm.count("gain")) {
            std::cerr << "Please specify the RF gain with --gain" << std::endl;
            return ~0;}
        if (not vm.count("file")) {
            std::cerr << "Please specify the sounding signal source file name with --file" << std::endl;
            return ~0;}
        if (not vm.count("spb")) {
            std::cerr << "Please specify the buffer size with --spb" << std::endl;
            return ~0;}



    //// ====== Configure USRP ======
        // --- create a usrp device ---
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % args
                << std::endl;
        uhd::usrp::multi_usrp::sptr tx_usrp = uhd::usrp::multi_usrp::make(args);

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
        tx_usrp->set_tx_rate(rate);        
        std::cout << boost::format("TX sampling rate has been set to: %f Msps...") % (tx_usrp->get_tx_rate() / 1e6)
            << std::endl;

        // --- set IF tuning ---
        uhd::tune_request_t tune_request(IF_freq);  // specify the frequency
        tune_request.args = uhd::device_addr_t("mode_n=integer");   // tune the USRP with integer-N mode
        tx_usrp->set_tx_freq(tune_request, tx_channel);
        std::cout << boost::format("TX IF frequency has been set to: %f MHz...") % (tx_usrp->get_tx_freq(tx_channel) / 1e6)
            << std::endl;

        // --- set RF gain ---
        tx_usrp->set_tx_gain(gain, tx_channel);
        std::cout << boost::format("TX gain has been set to: %f dB...") % tx_usrp->get_tx_gain(tx_channel)
            << std::endl;

        // --- set the antenna ---
        tx_usrp->set_tx_antenna(tx_ant, tx_channel);

        // --- checking LO and Ref locking status ---
        std::vector<std::string> sensor_names = tx_usrp->get_tx_sensor_names(tx_channel);
        if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")    // if "lo_locked" sensor is detected
            != sensor_names.end()) {
            uhd::sensor_value_t lo_locked = tx_usrp->get_tx_sensor("lo_locked", tx_channel);
            std::cout << boost::format("TX LO locking status: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());}
        const size_t mboard_sensor_idx = 0;
        sensor_names = tx_usrp->get_mboard_sensor_names(mboard_sensor_idx);
        if ((ref == "external")
            and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")    // if reference is external & "ref_locked" sensor is detected
                    != sensor_names.end())) {
            uhd::sensor_value_t ref_locked = tx_usrp->get_mboard_sensor("ref_locked", mboard_sensor_idx);
            std::cout << boost::format("TX reference locking status: %s ...") % ref_locked.to_pp_string()
                    << std::endl
                    << std::endl
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());}

        // --- solidate configuration
        std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time

        // --- print overall USRP info ---
        std::cout << boost::format("USRP Device Info: %s") % tx_usrp->get_pp_string() << std::endl;



    //// ====== Prepare for Transmitting ======
        // --- create a transmit streamer ---
        // refer to: https://files.ettus.com/manual/page_configuration.html#config_stream_args_cpu_format
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
        std::vector<std::complex<double>>  buff(spb);

        // Set up data reading and read sample data from txt file to pre-assigned buffer
        // data is saved in "buff". Note: Tx doesn't have stream_cmd to issue. 
        std::ifstream signal_file(filename_read.c_str(), std::ifstream::binary);
        signal_file.read((char*)&buff.front(), buff.size() * sizeof(std::complex<double>));
        size_t num_tx_samps = size_t(signal_file.gcount() / sizeof(std::complex<double>));  // the number of samples will be transmitted at one time



    //// ====== Continuously transmitting ======
        // Not 100% sure if there will be software/systmetic processing time between two calls of the send_from_file() function. 
        // If there is, then we need to modify the while-loop structure or logic in the send_from_file() and make the continuouty there
        // so that it can be a continuous action instead of a one-time action.  
        while (not stop_signal_called) {
            tx_stream->send(&buff.front(), num_tx_samps, tx_metadata);
        }



    //// ====== Set sigint if user wants to stop ======
        std::signal(SIGINT, &sig_int_handler);
        std::cout << "Press Ctrl + C to stop transmitting..." << std::endl;


    //// ====== Wrap up ======
        // close file
        signal_file.close();

        // print Tx finishes
        std::cout << std::endl << "Tx Done!" << std::endl << std::endl;
        return EXIT_SUCCESS;
}
