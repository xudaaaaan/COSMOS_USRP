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
 * @param rx_usrp a created usrp object
 * @param rx_channel the Rx port of USRP
 * @param filename_write the name of the file that will store the data
 * @param spb buffer size, should equals to "num_requested_samples"
 * @param num_requested_samples the total number of samples that will be captured
 * @param start_streaming_delay the delay that USRP will wait after it receives a 1 PPS trigger
 **********************************************************************/
template <typename samp_type>
void recv_to_file(uhd::usrp::multi_usrp::sptr rx_usrp,      // a USRP object
    size_t              rx_channel,                         // channel of Rx port
    const std::string&  filename_write,                     // file name to save data
    size_t              spb,                                // buffer size to save data (samples per buffer)
    size_t              num_requested_samples,              // total number of samples to be received
    double              start_streaming_delay               // how many seconds to start streaming after the Rx USRP receives its first 1 PPS
    )
{
        // ====== Define Variables ======
            // system parameters
            size_t num_received_samps       = 0;        // number of samples have received so far
            size_t num_rx_samps_tmp         = 0;
            const double timeout            = 10.0;     // in sec

            // --- create a receive streamer ---
            std::string cpu_format = "f32"; // Single-precision 32-bit data
            std::string wire_format = "s16"; // Signed 16-bit integer data
            uhd::stream_args_t stream_args(cpu_format, wire_format);
            std::vector<size_t> stream_args_channels;
            stream_args_channels.push_back(rx_channel);
            stream_args.channels = stream_args_channels;
            uhd::rx_streamer::sptr rx_stream = rx_usrp->get_rx_stream(stream_args);

            // Rx metadata
            uhd::rx_metadata_t rx_metadata;

            // define buffer
            std::vector<std::complex<double>> buff(spb);

            // Set up data writing
            std::ofstream data_file;
            char full_file_name[200];
            strcpy(full_file_name, filename_write.c_str());
            strcat(full_file_name, ".dat");
            data_file.open(full_file_name, std::ofstream::binary);

            // Set up metadata writing
            std::ofstream metadata_file;
            char full_metafile_name[200];

        // ====== Configure streaming ======
            uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE);    // streaming mode: continuous
            // Number of samples to receive
            stream_cmd.num_samps  = size_t(num_requested_samples);  // number of samples to receive every time
            // time to receive samples
            stream_cmd.stream_now = false;  // do NOT set it as true - otherwise the synchronization status will be lost!
            uhd::time_spec_t time_to_recv = uhd::time_spec_t(start_streaming_delay);
            stream_cmd.time_spec  = time_to_recv;   // when to stream (related to synchronization) - stream_now & time_spec
            // issue the streaming command
            rx_stream->issue_stream_cmd(stream_cmd);    // configure the USRP accordingly

        // ====== Start ======
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Rx: capturing will start in " << time_to_recv.get_real_secs() << " seconds..."
                << std::endl;

            const auto start_time = std::chrono::steady_clock::now();   // Mark the starting timestamp

        // ====== Receive and Write Data ======
            // Receive samples into the pre-assigned buffer
            num_rx_samps_tmp =
                rx_stream->recv(&buff.front(), buff.size(), rx_metadata, timeout);

            // Define error cases
                // - 1 - Time out
                if (rx_metadata.error_code == uhd::rx_metadata_t::ERROR_CODE_TIMEOUT) {
                    std::cout << boost::format("Timeout while streaming") << std::endl;
                    throw std::runtime_error("Timeout");}
                // - 2 - Overflow
                if (rx_metadata.error_code == uhd::rx_metadata_t::ERROR_CODE_OVERFLOW) {
                    std::cerr
                        << boost::format(
                            "Got an overflow indication. Please consider the following:\n"
                            "  Your write medium must sustain a rate of %fMB/s.\n"
                            "  Dropped samples will not be written to the file.\n"
                            "  Please modify this example for your purposes.\n")
                            % (rx_usrp->get_rx_rate() * sizeof(samp_type) / 1e6);
                    throw std::runtime_error("Overflow");}
                // - 3 - Other errors
                if (rx_metadata.error_code != uhd::rx_metadata_t::ERROR_CODE_NONE) {
                    std::string error = str(boost::format("Receiver error: %s") % rx_metadata.strerror());
                    throw std::runtime_error(error);}

            // update Rx sample counter
            num_received_samps += num_rx_samps_tmp;

            // write data to file from buffer
            data_file.write((const char*)&buff.front(), num_rx_samps_tmp * sizeof(samp_type));       

            // Mark the ending timestamp
            const auto actual_stop_time = std::chrono::steady_clock::now();

        // ====== Wrap up ======
            // close files
            data_file.close();

            // shut down receiver
            stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
            rx_stream->issue_stream_cmd(stream_cmd);       

            // print Rx finishes
            std::cout<<std::endl;
            std::cout<< "Rx Done!" <<std::endl;

        // ====== Status check ======
            std::cout << std::endl;
            const double actual_duration_seconds =
                std::chrono::duration<float>(actual_stop_time - start_time).count();

            std::cout << boost::format("Received %d samples in %f seconds") % num_received_samps
                            % actual_duration_seconds
                    << std::endl;
            const double rate_checked = (double)num_received_samps / actual_duration_seconds;
            std::cout << (rate_checked / 1e6) << " Msps" << std::endl;

        // ====== Process Metadata ======
            long long rx_starting_tick = rx_metadata.time_spec.to_ticks(200e6);
            double rx_starting_sec = rx_metadata.time_spec.get_real_secs();
            std::cout << "Metadata Here... " << std::endl;
            std::cout << "  Streaming starting tick = " << rx_starting_tick << std::endl;
            std::cout << "  Streaming starting sec = " << rx_starting_sec 
                        << std::endl
                        << std::endl;
            
            strcpy(full_metafile_name, filename_write.c_str());
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
        // USRP Config - USRP 2974 (mob4-1)
            // RF 2 - Tx(H)+Rx(H); RF3 - Tx(V)+Rx(V). We are using the Rx port on RF3
        const std::string rx_ant = "TX/RX"; // antenna port selection: https://files.ettus.com/manual/page_dboards.html#dboards_ubx
        const size_t rx_channel = 0;
        const std::string rx_subdev = "B:1";    // section "Subdev Specifications" & "N310-specific Features" of: https://files.ettus.com/manual/page_usrp_n3xx.html#n3xx_feature_list_mg
        const std::string rx_args = "addr=10.37.6.2"; // sdr1-in2 address

        // Timing
        const std::string pps = "external"; // https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a57a5580ba06d7d6a037c9ef64f1ea361
        const std::string ref = "external"; // https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a73ed40009d0d3787c183d42423d25026

        // RF configuration
        const double rx_rate = 200e6;  // Rx sampling rate, in Samples/sec
        const double IF_freq = 3e9;    // 1st-stage IF center frequency, in Hz, should be 3 GHz. Then PAAM will keep UPC from 3 GHz to 28 GHz.


    // variables to be set by po
    std::string filename_write;
    size_t num_requested_samples, spb, num_rep;
    double rx_gain, total_time, start_delay;


    // setup the program options
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        ("help", "help message")

        // RF parameters
        ("gain", po::value<double>(&rx_gain)->default_value(6), "gain for the RF chain")

        // sounding signal/receiving
        ("file", po::value<std::string>(&filename_write)->default_value("usrp_samples.dat"), "name of the file to write binary samples to")
        ("nsamps", po::value<size_t>(&num_requested_samples)->default_value(10000), "total number of samples to receive (requested)")     
        ("rep", po::value<size_t>(&num_rep)->default_value(10), "total number of samples to receive (requested)")   // not useful for now  
        ("delay", po::value<double>(&start_delay)->default_value(3.0), "delay time before streaming when receives the first 1 PPS after configuration")
    ;
    spb = num_requested_samples;    // samples per buffer



    //// ====== Preparation ======
        // clang-format on
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // print the help message
        if (vm.count("help")) {
            std::cout << boost::format("UHD RX samples to file %s") % desc << std::endl;
            return ~0;}

        // input check
        if (not vm.count("rx_gain")) {
            std::cerr << "Please specify the RF gain with --rx_gain" << std::endl;
            return ~0;}
        if (not vm.count("filename_write")) {
            std::cerr << "Please specify the target file name to store data with --file" << std::endl;
            return ~0;}
        if (not vm.count("num_requested_samples")) {
            std::cerr << "Please specify the total number of samples to receive with --num_requested_samples" << std::endl;
            return ~0;}



    //// ====== Configure USRP ======
        // --- create a usrp device ---
        std::cout << std::endl;
        std::cout << boost::format("Creating the usrp device with: %s...") % rx_args
                << std::endl;
        uhd::usrp::multi_usrp::sptr rx_usrp = uhd::usrp::multi_usrp::make(rx_args);

        // --- select subdevice (always use default value) ---
        rx_usrp->set_rx_subdev_spec(rx_subdev);

        // --- set timing ---
        rx_usrp->set_clock_source(ref); // ref as external
        rx_usrp->set_time_source(pps);  // pps as external 
        std::cout<<boost::format("The reference clock source is: %s...") % ref
            <<std::endl;
        std::cout<<boost::format("The PPS signal source is: %s...") % pps
            <<std::endl;
        rx_usrp->set_time_unknown_pps(uhd::time_spec_t(0.0));   // set timestamp: https://files.ettus.com/manual/classuhd_1_1usrp_1_1multi__usrp.html#a413014bf3aea4a8ea2d268b4a3b390e9
        std::cout << boost::format("Device timestamp has been set to 0.")
            << std::endl;

        // --- set sampling rate ---
        rx_usrp->set_rx_rate(rx_rate);      
        std::cout << boost::format("RX sampling rate has been set to: %f Msps...") % (rx_usrp->get_rx_rate() / 1e6)
            << std::endl;
        
        // --- set IF tuning ---
        uhd::tune_request_t tune_request(IF_freq);  // specify the frequency
        tune_request.args = uhd::device_addr_t("mode_n=integer");   // tune the USRP with integer-N mode
        rx_usrp->set_rx_freq(tune_request, rx_channel);
        std::cout << boost::format("RX IF frequency has been set to: %f MHz...") % (rx_usrp->get_rx_freq(rx_channel) / 1e6)
            << std::endl;

        // --- set RF gain ---
        rx_usrp->set_rx_gain(rx_gain, channel);
        std::cout << boost::format("RX gain has been set to: %f dB...") % rx_usrp->get_rx_gain(channel)
            << std::endl;

        // --- set the antenna ---
        rx_usrp->set_rx_antenna(rx_ant, rx_channel);

        // --- consolidate configuration
        std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time

        // --- checking LO and Ref locking status ---
        std::vector<std::string> rx_sensor_names;
        rx_sensor_names = rx_usrp->get_rx_sensor_names(rx_channel); // get the Rx sensor names for channel: rx_channel
        if (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "lo_locked")    // if "lo_locked" sensor is detected
            != rx_sensor_names.end()) {
            uhd::sensor_value_t lo_locked = rx_usrp->get_rx_sensor("lo_locked", rx_channel);
            std::cout << boost::format("RX LO locking status: %s ...") % lo_locked.to_pp_string()
                    << std::endl;
            UHD_ASSERT_THROW(lo_locked.to_bool());}
                // ...... [Debug] --> print the list of available Rx sensors ......
                    std::cout << "......................................" << std::endl;
                    std::cout << "Available RX sensors:" << std::endl;
                    for (const auto& sensor_name : rx_sensor_names) {
                        std::cout << "  - " << sensor_name
                                << std::endl
                                << std::endl;}
                    std::cout << "......................................" << std::endl;
                // .............................................................

        rx_sensor_names = rx_usrp->get_mboard_sensor_names(0); // there is only 1 motherboard in this USRP so the index of it is: 0
        if (std::find(rx_sensor_names.begin(), rx_sensor_names.end(), "ref_locked") != rx_sensor_names.end()) {    // if "ref_locked" sensor is detected
            uhd::sensor_value_t ref_locked = rx_usrp->get_mboard_sensor("ref_locked", 0);
            std::cout << boost::format("RX reference locking status: %s ...") % ref_locked.to_pp_string()
                    << std::endl
                    << std::endl
                    << std::endl;
            UHD_ASSERT_THROW(ref_locked.to_bool());}
                // ...... [Debug] --> print the list of available motherboard sensors ......
                    std::cout << "......................................" << std::endl;
                    std::cout << "Available motherboard sensors:" << std::endl;
                    for (const auto& sensor_name : rx_sensor_names) {
                        std::cout << "  - " << sensor_name
                                << std::endl
                                << std::endl;}
                    std::cout << "......................................" << std::endl;
                // .............................................................

        // --- print overall USRP info ---
        std::cout << boost::format("RX USRP Device Info: %s") % rx_usrp->get_pp_string() << std::endl;









 
    
    //// ====== Start Rx ======
        /*****************************************************
            Need to implement the automation functions here
        *****************************************************/ 

        // Actual receiving action: 
        recv_to_file<std::complex<double>>(rx_usrp, rx_channel, filename_write, spb, num_requested_samples, start_delay);










    
    return EXIT_SUCCESS;
}
