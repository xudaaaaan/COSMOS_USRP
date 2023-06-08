//
// Copyright 2018 Ettus Research, A National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
//
// Description:
//
// This example demonstrates using the Replay block to replay data from a file.
// It streams the file data to the Replay block, where it is recorded, then it
// is played back to the radio.

#include <uhd/device3.hpp>
#include <uhd/rfnoc/radio_ctrl.hpp>
#include <uhd/rfnoc/replay_block_ctrl.hpp>
#include <uhd/utils/safe_main.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <csignal>
#include <fstream>
#include <thread>


namespace po = boost::program_options;

using std::cout;
using std::endl;


///////////////////////////////////////////////////////////////////////////////

static volatile bool stop_signal_called = false;

// Ctrl+C handler
void sig_int_handler(int)
{
    stop_signal_called = true;
}


int UHD_SAFE_MAIN(int argc, char* argv[])
{
    // We use sc16 in this example, but the replay block only uses 64-bit words
    // and is not aware of the CPU or wire format.
    std::string wire_format("sc16");
    std::string cpu_format("sc16");

    // Constants related to the Replay block
    const size_t replay_word_size = 8; // Size of words used by replay block
    const size_t bytes_per_sample = 4; // Complex signed 16-bit is 32 bits per sample
    const size_t samples_per_word = 2; // Number of sc16 samples per word
    const size_t replay_spp = 2000; // SC16 Samples per packet generated by Replay block


    ///////////////////////////////////////////////////////////////////////////
    // Handle command line options

    std::string args, radio_args, file, ant, ref;
    double rate, freq, gain, bw;
    size_t radio_id, radio_chan, replay_id, replay_chan, nsamps;

    po::options_description desc("Allowed Options");
    // clang-format off
    desc.add_options()
        ("help", "help message")
        ("args", po::value<std::string>(&args)->default_value(""), "multi uhd device address args")
        ("radio-id", po::value<size_t>(&radio_id)->default_value(0), "radio block to use (e.g., 0 or 1).")
        ("radio-chan", po::value<size_t>(&radio_chan)->default_value(0), "radio channel to use")
        ("radio-args", po::value<std::string>(&radio_args), "radio arguments")
        ("replay-id", po::value<size_t>(&replay_id)->default_value(0), "replay block to use (e.g., 0 or 1)")
        ("replay_chan", po::value<size_t>(&replay_chan)->default_value(0), "replay channel to use")
        ("nsamps", po::value<size_t>(&nsamps)->default_value(0), "number of samples to play (0 for infinite)")
        ("file", po::value<std::string>(&file)->default_value("usrp_samples.dat"), "name of the file to read binary samples from")
        ("freq", po::value<double>(&freq), "RF center frequency in Hz")
        ("rate", po::value<double>(&rate), "rate of radio block")
        ("gain", po::value<double>(&gain), "gain for the RF chain")
        ("ant", po::value<std::string>(&ant), "antenna selection")
        ("bw", po::value<double>(&bw), "analog front-end filter bandwidth in Hz")
        ("ref", po::value<std::string>(&ref)->default_value("internal"), "reference source (internal, external, mimo)")
    ;
    // clang-format on
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // Print help message
    if (vm.count("help")) {
        cout << boost::format("UHD/RFNoC Replay samples from file %s") % desc << endl;
        cout << "This application uses the Replay block to playback data from a file to "
                "a radio"
             << endl
             << endl;
        return EXIT_FAILURE;
    }


    ///////////////////////////////////////////////////////////////////////////
    // Create USRP device and block controls

    cout << "Creating the USRP device with: " << args << ". . .\n" << endl;
    uhd::device3::sptr usrp = uhd::device3::make(args);

    // Create handle for radio object
    uhd::rfnoc::block_id_t radio_ctrl_id(0, "Radio", radio_id);
    uhd::rfnoc::radio_ctrl::sptr radio_ctrl;
    radio_ctrl = usrp->get_block_ctrl<uhd::rfnoc::radio_ctrl>(radio_ctrl_id);
    std::cout << "Using radio " << radio_id << ", channel " << radio_chan << std::endl;


    // Check if the replay block exists on this device
    uhd::rfnoc::block_id_t replay_ctrl_id(0, "Replay", replay_id);
    uhd::rfnoc::replay_block_ctrl::sptr replay_ctrl;
    if (!usrp->has_block(replay_ctrl_id)) {
        cout << "Unable to find block \"" << replay_ctrl_id << "\"" << endl;
        return EXIT_FAILURE;
    }
    replay_ctrl = usrp->get_block_ctrl<uhd::rfnoc::replay_block_ctrl>(replay_ctrl_id);
    std::cout << "Using replay block " << replay_id << ", channel " << replay_chan
              << std::endl;


    ///////////////////////////////////////////////////////////////////////////
    // Configure radio

    // Lock clocks
    if (vm.count("ref")) {
        radio_ctrl->set_clock_source(ref);
    }
    
    // Apply any radio arguments provided
    radio_ctrl->set_args(radio_args);

    // Set the center frequency
    if (not vm.count("freq")) {
        std::cerr << "Please specify the center frequency with --freq" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << boost::format("Setting TX Freq: %f MHz...") % (freq / 1e6) << std::endl;
    radio_ctrl->set_tx_frequency(freq, radio_chan);
    std::cout << boost::format("Actual TX Freq: %f MHz...")
                     % (radio_ctrl->get_tx_frequency(radio_chan) / 1e6)
              << std::endl
              << std::endl;

    // Set the sample rate
    if (vm.count("rate")) {
        std::cout << boost::format("Setting TX Rate: %f Msps...") % (rate / 1e6)
                  << std::endl;
        radio_ctrl->set_rate(rate);
        std::cout << boost::format("Actual TX Rate: %f Msps...")
                         % (radio_ctrl->get_rate() / 1e6)
                  << std::endl
                  << std::endl;
    }

    // Set the RF gain
    if (vm.count("gain")) {
        std::cout << boost::format("Setting TX Gain: %f dB...") % gain << std::endl;
        radio_ctrl->set_tx_gain(gain, radio_chan);
        std::cout << boost::format("Actual TX Gain: %f dB...")
                         % radio_ctrl->get_tx_gain(radio_chan)
                  << std::endl
                  << std::endl;
    }

    // Set the analog front-end filter bandwidth
    if (vm.count("bw")) {
        std::cout << boost::format("Setting TX Bandwidth: %f MHz...") % (bw / 1e6)
                  << std::endl;
        radio_ctrl->set_tx_bandwidth(bw, radio_chan);
        std::cout << boost::format("Actual TX Bandwidth: %f MHz...")
                         % (radio_ctrl->get_tx_bandwidth(radio_chan) / 1e6)
                  << std::endl
                  << std::endl;
    }

    // Set the antenna
    if (vm.count("ant")) {
        radio_ctrl->set_tx_antenna(ant, radio_chan);
    }

    // Allow for some setup time
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    ///////////////////////////////////////////////////////////////////////////
    // Connect Replay block to radio

    uhd::rfnoc::graph::sptr replay_graph = usrp->create_graph("rfnoc_replay");
    usrp->clear();
    std::cout << "Connecting " << replay_ctrl->get_block_id() << " ==> "
              << radio_ctrl->get_block_id() << std::endl;
    replay_graph->connect(replay_ctrl->get_block_id(),
        replay_chan,
        radio_ctrl->get_block_id(),
        radio_chan,
        replay_spp);

    // Inform replay block that it has an RX streamer connected to it
    replay_ctrl->set_rx_streamer(true, replay_chan);


    ///////////////////////////////////////////////////////////////////////////
    // Setup streamer to Replay block

    uint64_t noc_id;
    uhd::device_addr_t streamer_args;
    uhd::stream_args_t stream_args(cpu_format, wire_format);
    uhd::tx_streamer::sptr tx_stream;
    uhd::tx_metadata_t tx_md;

    streamer_args["block_id"]   = replay_ctrl->get_block_id().to_string();
    streamer_args["block_port"] = str(boost::format("%d") % replay_chan);
    stream_args.args            = streamer_args;
    tx_stream                   = usrp->get_tx_stream(stream_args);

    // Make sure that streamer SPP is a multiple of the Replay block word size
    size_t tx_spp = tx_stream->get_max_num_samps();
    if (tx_spp % samples_per_word != 0) {
        // Round SPP down to a multiple of the word size
        tx_spp = (tx_spp / samples_per_word) * samples_per_word;
        tx_stream.reset();
        streamer_args["spp"] = boost::lexical_cast<std::string>(tx_spp);
        stream_args.args     = streamer_args;
        tx_stream            = usrp->get_tx_stream(stream_args);
    }

    cout << "Using streamer args: " << stream_args.args.to_string() << endl;


    ///////////////////////////////////////////////////////////////////////////
    // Read the data to replay

    // Open the file
    std::ifstream infile(file.c_str(), std::ifstream::binary);
    if (!infile.is_open()) {
        std::cerr << "Could not open specified file" << std::endl;
        return EXIT_FAILURE;
    }

    // Get the file size
    infile.seekg(0, std::ios::end);
    size_t file_size = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // Calculate the number of 64-bit words and samples to replay
    size_t words_to_replay   = file_size / replay_word_size;
    size_t samples_to_replay = words_to_replay * replay_word_size / bytes_per_sample;

    // Create buffer
    std::vector<char> tx_buffer(words_to_replay * replay_word_size);
    char* tx_buf_ptr = &tx_buffer[0];

    // Read file into buffer, rounded down to number of words
    infile.read(tx_buf_ptr, words_to_replay * replay_word_size);
    infile.close();


    ///////////////////////////////////////////////////////////////////////////
    // Configure replay block

    // Configure a buffer in the on-board memory at address 0 that's equal in
    // size to the file we want to play back (rounded down to a multiple of
    // 64-bit words). Note that it is allowed to playback a different size or
    // location from what was recorded.
    replay_ctrl->config_record(0, words_to_replay * replay_word_size, replay_chan);
    replay_ctrl->config_play(0, words_to_replay * replay_word_size, replay_chan);

    // Set samples per packet for Replay block playback
    replay_ctrl->set_words_per_packet(replay_spp / samples_per_word, replay_chan);

    // Display replay configuration
    cout << boost::format("Replay file size:     %d bytes (%d qwords, %d samples)")
                % (words_to_replay * replay_word_size) % words_to_replay
                % samples_to_replay
         << endl;

    cout << boost::format("Record base address:  0x%X")
                % replay_ctrl->get_record_addr(replay_chan)
         << endl;
    cout << boost::format("Record buffer size:   %d bytes")
                % replay_ctrl->get_record_size(replay_chan)
         << endl;
    cout << boost::format("Record fullness:      %d")
                % replay_ctrl->get_record_fullness(replay_chan)
         << endl;
    cout << boost::format("Play base address:    0x%X")
                % replay_ctrl->get_play_addr(replay_chan)
         << endl;
    cout << boost::format("Play buffer size:     %d bytes")
                % replay_ctrl->get_play_size(replay_chan)
         << endl;

    // Restart record buffer repeatedly until no new data appears on the Replay
    // block's input. This will flush any data that was buffered on the input.
    uint32_t fullness;
    cout << boost::format("Restarting record buffer...") << endl;
    do {
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::duration time_diff;

        replay_ctrl->record_restart(replay_chan);

        // Make sure the record buffer doesn't start to fill again
        start_time = std::chrono::system_clock::now();
        do {
            fullness = replay_ctrl->get_record_fullness(replay_chan);
            if (fullness != 0)
                break;
            time_diff = std::chrono::system_clock::now() - start_time;
            time_diff = std::chrono::duration_cast<std::chrono::milliseconds>(time_diff);
        } while (time_diff.count() < 250);
    } while (fullness);


    ///////////////////////////////////////////////////////////////////////////
    // Send data to replay (record the data)

    cout << "Sending data to be recorded..." << endl;
    tx_md.start_of_burst = true;
    tx_md.end_of_burst   = true;
    size_t num_tx_samps  = tx_stream->send(tx_buf_ptr, samples_to_replay, tx_md);

    if (num_tx_samps != samples_to_replay) {
        cout << boost::format("ERROR: Unable to send %d samples") % samples_to_replay
             << endl;
        return EXIT_FAILURE;
    }


    ///////////////////////////////////////////////////////////////////////////
    // Wait for data to be stored in on-board memory

    cout << "Waiting for recording to complete..." << endl;
    while (replay_ctrl->get_record_fullness(replay_chan)
           < words_to_replay * replay_word_size)
        ;


    ///////////////////////////////////////////////////////////////////////////
    // Start replay of data

    uhd::stream_cmd_t stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);

    if (nsamps <= 0) {
        // Replay the entire buffer over and over
        stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS;
        stream_cmd.num_samps   = words_to_replay;
        cout << boost::format("Issuing replay command for %d words in continuous mode...")
                    % stream_cmd.num_samps
             << endl;
    } else {
        // Replay nsamps, wrapping back to the start of the buffer if nsamps is
        // larger than the buffer size.
        stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_NUM_SAMPS_AND_DONE;
        stream_cmd.num_samps   = nsamps / samples_per_word;
        cout << boost::format("Issuing replay command for %d words...")
                    % stream_cmd.num_samps
             << endl;
    }
    stream_cmd.stream_now = true;
    replay_ctrl->issue_stream_cmd(stream_cmd, replay_chan);


    ///////////////////////////////////////////////////////////////////////////
    // Wait until user says to stop

    // Setup SIGINT handler (Ctrl+C)
    std::signal(SIGINT, &sig_int_handler);
    cout << "Replaying data (Press Ctrl+C to stop)..." << endl;

    while (not stop_signal_called)
        ;

    // Remove SIGINT handler
    std::signal(SIGINT, SIG_DFL);


    ///////////////////////////////////////////////////////////////////////////
    // Issue stop command

    stream_cmd.stream_mode = uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS;
    cout << endl << "Stopping replay..." << endl;
    replay_ctrl->issue_stream_cmd(stream_cmd, replay_chan);

    // The stop takes effect after the current command has completed, so use
    // halt to stop the command in progress and clear any queued commands.
    replay_ctrl->play_halt(replay_chan);


    ///////////////////////////////////////////////////////////////////////////
    // Wait for any buffered replay data to finish playing out

    uint16_t prev_packet_count, packet_count;

    cout << "Waiting for replay data to flush... ";
    prev_packet_count =
        replay_ctrl->sr_read64(uhd::rfnoc::SR_READBACK_REG_GLOBAL_PARAMS, replay_chan)
        >> 32;
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        packet_count =
            replay_ctrl->sr_read64(uhd::rfnoc::SR_READBACK_REG_GLOBAL_PARAMS, replay_chan)
            >> 32;
        if (packet_count == prev_packet_count)
            break;
        prev_packet_count = packet_count;
    }

    cout << endl;

    return EXIT_SUCCESS;
}
