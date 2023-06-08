var page_devices =
[
    [ "General Application Notes", "page_general.html", [
      [ "Tuning Notes", "page_general.html#general_tuning", [
        [ "Two-stage tuning process", "page_general.html#general_tuning_process", [
          [ "Tuning the receive chain:", "page_general.html#general_tuning_rxchain", null ]
        ] ],
        [ "DSP Tuning", "page_general.html#general_tuning_dsp", null ],
        [ "Sign of DSP frequency on TX vs. RX tuning", "page_general.html#general_tuning_dsp_sign", null ],
        [ "RF front-end settling time", "page_general.html#general_tuning_rfsettling", [
          [ "Pseudo-code for dealing with settling time after tuning on receive:", "page_general.html#general_tuning_waitcode", null ]
        ] ]
      ] ],
      [ "Sample rate notes", "page_general.html#general_sampleratenotes", [
        [ "Automatic master-clock selection", "page_general.html#general_sampleratenotes_automatic", null ],
        [ "Master clock rate and Nyquist", "page_general.html#general_sampleratenotes_nyquist", null ]
      ] ],
      [ "Overflow/Underflow Notes", "page_general.html#general_ounotes", [
        [ "Overflow notes", "page_general.html#general_ounotes_overflow", null ],
        [ "Underrun notes", "page_general.html#general_ounotes_underrun", null ]
      ] ],
      [ "Threading Notes", "page_general.html#general_threading", [
        [ "Thread safety notes", "page_general.html#general_threading_safety", null ],
        [ "Thread priority scheduling", "page_general.html#general_threading_prio", null ]
      ] ],
      [ "Miscellaneous Notes", "page_general.html#general_misc", [
        [ "Support for dynamically loadable modules", "page_general.html#general_misc_dynamic", null ],
        [ "Disabling or redirecting prints to stdout", "page_general.html#general_misc_prints", null ]
      ] ]
    ] ],
    [ "Device Identification", "page_identification.html", [
      [ "Identifying USRP Devices", "page_identification.html#id_identifying", [
        [ "Common device identifiers", "page_identification.html#id_identifying_common", null ],
        [ "Device discovery via command line", "page_identification.html#id_identifying_cmdline", null ],
        [ "Device discovery through the API", "page_identification.html#id_identifying_api", null ],
        [ "Device properties", "page_identification.html#id_identifying_props", null ]
      ] ],
      [ "Naming a USRP Device", "page_identification.html#id_naming", [
        [ "Set a custom name", "page_identification.html#id_naming_set", null ],
        [ "Discovery via name", "page_identification.html#id_naming_discovery", null ]
      ] ]
    ] ],
    [ "Configuring Devices and Streamers", "page_configuration.html", [
      [ "Device Configuration through address string", "page_configuration.html#config_devaddr", null ],
      [ "Specifying the Subdevice", "page_configuration.html#config_subdev", [
        [ "USRP Family Motherboard Slot Names", "page_configuration.html#config_subdev_slotnames", null ],
        [ "USRP Family Motherboard Slot Names", "page_configuration.html#config_subdev_default", null ],
        [ "Daughterboard Frontend Names", "page_configuration.html#config_subdev_dbnames", null ]
      ] ],
      [ "Streaming Arguments (Stream Args)", "page_configuration.html#config_stream_args", null ]
    ] ],
    [ "Multiple USRP configurations", "page_multiple.html", [
      [ "Introduction", "page_multiple.html#multiple_intro", null ],
      [ "Setting up devices", "page_multiple.html#multiple_setup", null ],
      [ "Channel and Device Numbering", "page_multiple.html#multiple_channumbers", null ],
      [ "MIMO Operation", "page_multiple.html#multiple_mimo", null ]
    ] ],
    [ "Firmware and FPGA Images", "page_images.html", [
      [ "Images Overview", "page_images.html#images_overview", null ],
      [ "Pre-built Images", "page_images.html#images_prebuild", [
        [ "UHD Images Downloader", "page_images.html#images_prebuilt_downloader", null ],
        [ "Platform installers", "page_images.html#images_prebuilt_installers", null ],
        [ "Archive install", "page_images.html#images_prebuilt_archive", null ]
      ] ],
      [ "Building Images", "page_images.html#images_building", [
        [ "Xilinx FPGA builds", "page_images.html#images_building_xilinx", null ],
        [ "ZPU firmware builds", "page_images.html#images_building_zpu", null ],
        [ "Altera FPGA builds", "page_images.html#images_building_altera", null ],
        [ "FX2 firmware builds", "page_images.html#images_building_fx2", null ]
      ] ]
    ] ],
    [ "Transport Notes", "page_transport.html", [
      [ "Introduction", "page_transport.html#transport_intro", null ],
      [ "UDP Transport (Sockets)", "page_transport.html#transport_udp", [
        [ "Transport parameters", "page_transport.html#transport_udp_params", null ],
        [ "Flow control parameters", "page_transport.html#transport_udp_flow", null ],
        [ "Resize socket buffers", "page_transport.html#transport_udp_sockbufs", null ],
        [ "Latency Optimization", "page_transport.html#transport_udp_latency", null ],
        [ "Linux specific notes", "page_transport.html#transport_udp_linux", null ],
        [ "Windows specific notes", "page_transport.html#transport_udp_windows", null ]
      ] ],
      [ "USB Transport (LibUSB)", "page_transport.html#transport_usb", [
        [ "Transport parameters", "page_transport.html#transport_usb_params", null ],
        [ "Setup Udev for USB (Linux)", "page_transport.html#transport_usb_udev", null ],
        [ "Install USB driver (Windows)", "page_transport.html#transport_usb_installwin", null ]
      ] ],
      [ "PCIe Transport (NI-RIO)", "page_transport.html#transport_pcie", [
        [ "Transport parameters", "page_transport.html#transport_pcie_params", null ]
      ] ]
    ] ],
    [ "Device Synchronization", "page_sync.html", [
      [ "Common Reference Signals", "page_sync.html#sync_commonref", [
        [ "PPS and 10 MHz reference signals", "page_sync.html#sync_commonref_pps", null ],
        [ "MIMO cable reference signals", "page_sync.html#sync_commonref_mimo", null ]
      ] ],
      [ "Synchronizing the Device Time", "page_sync.html#sync_time", [
        [ "Method 1 - poll the USRP time registers", "page_sync.html#sync_time_reg", null ],
        [ "Method 2 - query the GPSDO for seconds", "page_sync.html#sync_time_gpsdo", null ],
        [ "Method 3 - MIMO cable", "page_sync.html#sync_time_mimocable", null ]
      ] ],
      [ "Synchronizing Channel Phase", "page_sync.html#sync_phase", [
        [ "Align CORDICs in the DSP", "page_sync.html#sync_phase_cordics", null ],
        [ "Align LOs in the front-end (SBX, UBX)", "page_sync.html#sync_phase_lo", null ],
        [ "Align LOs in the front-end (others)", "page_sync.html#sync_phase_lootherfe", null ]
      ] ]
    ] ],
    [ "Device Calibration", "page_calibration.html", [
      [ "Self-Calibration", "page_calibration.html#calibration_self", [
        [ "Calibration Utilities", "page_calibration.html#calibration_self_utils", null ],
        [ "Calibration Data", "page_calibration.html#calibration_data", null ],
        [ "Ignoring Calibration Files", "page_calibration.html#ignore_cal_file", null ]
      ] ]
    ] ],
    [ "The Module Peripheral Manager (MPM) Architecture", "page_mpm.html", [
      [ "Architecture Overview", "page_mpm.html#mpm_arch", null ],
      [ "Device Claiming", "page_mpm.html#mpm_arch_claiming", null ],
      [ "Network vs. Embedded Mode", "page_mpm.html#mpm_modes", null ],
      [ "Debugging Tools", "page_mpm.html#mpm_debug", null ],
      [ "Hijack Mode", "page_mpm.html#mpm_shell_hijack", null ]
    ] ],
    [ "DPDK, Data Plane Development Kit", "page_dpdk.html", [
      [ "DPDK Overview", "page_dpdk.html#dpdk_overview", null ],
      [ "DPDK Setup", "page_dpdk.html#dpdk_setup", [
        [ "DPDK Installation Instructions", "page_dpdk.html#dpdk_installation", null ],
        [ "System Configuration", "page_dpdk.html#dpdk_system_configuration", null ],
        [ "NIC Configuration", "page_dpdk.html#dpdk_nic_config", null ]
      ] ],
      [ "Using DPDK in UHD", "page_dpdk.html#dpdk_using", [
        [ "Enabling DPDK with UHD Device Args", "page_dpdk.html#dpdk_device_args", null ],
        [ "Thread Priorities with DPDK", "page_dpdk.html#dpdk_thread_priorities", null ]
      ] ]
    ] ],
    [ "Configuration Files", "page_configfiles.html", [
      [ "Format of the configuration files", "page_configfiles.html#configfiles_format", null ],
      [ "Configuring USRPs", "page_configfiles.html#configfiles_usrps", null ],
      [ "Location of configuration files", "page_configfiles.html#configfiles_location", null ]
    ] ],
    [ "Compat Numbers", "page_compat.html", [
      [ "Major and Minor Compat Numbers", "page_compat.html#compat_minor_major", null ],
      [ "B200-Series Compat Numbers", "page_compat.html#compat_b2", null ],
      [ "X300 and USRP2/N210 Series Compat Numbers", "page_compat.html#compat_x3u2", null ],
      [ "MPM Devices (N310, E320)", "page_compat.html#compat_mpm", null ],
      [ "RFNoC Components", "page_compat.html#compat_rfnoc", null ],
      [ "FAQ", "page_compat.html#compat_faq", [
        [ "Why is only one version of the compat number supported?", "page_compat.html#compat_faq_why1", null ],
        [ "Why are there so many different compat numbers?", "page_compat.html#compat_faq_whymany", null ]
      ] ]
    ] ],
    [ "USRP2 and N2x0 Series", "page_usrp2.html", "page_usrp2" ],
    [ "USRP N3xx Series", "page_usrp_n3xx.html", "page_usrp_n3xx" ],
    [ "USRP B2x0 Series", "page_usrp_b200.html", "page_usrp_b200" ],
    [ "USRP E3xx Series", "page_usrp_e3xx.html", [
      [ "Comparative features list", "page_usrp_e3xx.html#e3xx_feature_list", [
        [ "E310", "page_usrp_e3xx.html#e3xx_feature_list_e310", null ],
        [ "E320", "page_usrp_e3xx.html#e3xx_feature_list_e320", null ]
      ] ],
      [ "E310 Overview", "page_usrp_e3xx.html#e310_overview", [
        [ "The Zynq CPU/FPGA and host operating system", "page_usrp_e3xx.html#e310_zynq", null ],
        [ "E310 Migration Guide to MPM architecture", "page_usrp_e3xx.html#e31x_migration", null ]
      ] ],
      [ "E320 Overview", "page_usrp_e3xx.html#e320_overview", [
        [ "The Zynq CPU/FPGA and host operating system", "page_usrp_e3xx.html#e320_zynq", null ],
        [ "The STM32 microcontroller", "page_usrp_e3xx.html#e320_micro", null ],
        [ "The SD card", "page_usrp_e3xx.html#e3xx_sdcard", null ]
      ] ],
      [ "Getting started", "page_usrp_e3xx.html#e3xx_getting_started", [
        [ "Assembling the E3XX", "page_usrp_e3xx.html#e3xx_getting_started_assembling", null ],
        [ "Updating the file system", "page_usrp_e3xx.html#e3xx_getting_started_fs_update", [
          [ "E310/E312/E313 file system", "page_usrp_e3xx.html#e31x_fs", null ],
          [ "E320 file system", "page_usrp_e3xx.html#e320_fs", null ],
          [ "Updating the SD card", "page_usrp_e3xx.html#update_sdcard", null ]
        ] ]
      ] ],
      [ "Building custom filesystems and SD card images", "page_usrp_e3xx.html#e3xx_fsbuild", [
        [ "Using Docker to build filesystems", "page_usrp_e3xx.html#e3xx_fsbuild_docker", null ],
        [ "Serial connection", "page_usrp_e3xx.html#e3xx_getting_started_serial", [
          [ "Connecting to the microcontroller", "page_usrp_e3xx.html#e320_getting_started_serial_micro", null ]
        ] ],
        [ "SSH connection", "page_usrp_e3xx.html#e3xx_getting_started_ssh", null ],
        [ "Network Connectivity", "page_usrp_e3xx.html#e3xx_getting_started_connectivity", null ],
        [ "Security-related settings", "page_usrp_e3xx.html#e3xx_getting_started_security", null ],
        [ "Updating the FPGA", "page_usrp_e3xx.html#e3xx_getting_started_fpga_update", null ]
      ] ],
      [ "Using an E3XX USRP from UHD", "page_usrp_e3xx.html#e3xx_usage", [
        [ "Device arguments", "page_usrp_e3xx.html#e3xx_usage_device_args", null ],
        [ "The sensor API", "page_usrp_e3xx.html#e3xx_usage_sensors", [
          [ "E31X Sensors", "page_usrp_e3xx.html#e310_sensors", null ],
          [ "E320 Sensors", "page_usrp_e3xx.html#e320_sensors", null ]
        ] ]
      ] ],
      [ "Remote Management", "page_usrp_e3xx.html#e3xx_rasm", [
        [ "Mender: Remote update capability", "page_usrp_e3xx.html#e3xx_rasm_mender", null ],
        [ "Salt: Remote configuration management and execution", "page_usrp_e3xx.html#e3xx_rasm_salt", null ]
      ] ],
      [ "Troubleshooting", "page_usrp_e3xx.html#e3xx_troubleshooting", [
        [ "E320 Built-in Self-Test (BiST)", "page_usrp_e3xx.html#e3xx_troubleshooting_bist", null ]
      ] ],
      [ "Theory of Operation", "page_usrp_e3xx.html#e3xx_theory_of_ops", null ],
      [ "Modifying and compiling UHD and MPM for the E320", "page_usrp_e3xx.html#e3xx_software_dev", [
        [ "Compiling MPM natively", "page_usrp_e3xx.html#e3xx_software_dev_mpm_native", null ],
        [ "Obtaining an SDK", "page_usrp_e3xx.html#e3xx_software_dev_sdk", null ],
        [ "SDK Usage", "page_usrp_e3xx.html#e3xx_software_dev_sdkusage", [
          [ "Building UHD", "page_usrp_e3xx.html#e3xx_software_dev_uhd", null ],
          [ "Building GNU Radio", "page_usrp_e3xx.html#e3xx_software_dev_gr", null ]
        ] ]
      ] ],
      [ "E310-specific Features", "page_usrp_e3xx.html#e31x_device", [
        [ "Front Panel", "page_usrp_e3xx.html#e31x_hw_front_panel", null ],
        [ "Rear Panel", "page_usrp_e3xx.html#e31x_hw_rear_panel", null ],
        [ "Clock and Time Synchronization", "page_usrp_e3xx.html#e31x_hw_sync", null ],
        [ "PPS - Pulse Per Second", "page_usrp_e3xx.html#e31x_hw_pps", null ],
        [ "Internal GPS", "page_usrp_e3xx.html#e31x_hw_gps", null ],
        [ "Internal GPIO", "page_usrp_e3xx.html#e31x_hw_gpio", null ],
        [ "Debugging custom FPGA designs with Xilinx Chipscope", "page_usrp_e3xx.html#e31x_hw_chipscope", null ],
        [ "Battery notes", "page_usrp_e3xx.html#e312_battery", [
          [ "Connector", "page_usrp_e3xx.html#e312_battery_connector", null ],
          [ "Driver", "page_usrp_e3xx.html#e312_battery_information", null ],
          [ "Calibration Procedure", "page_usrp_e3xx.html#e312_battery_calibration", null ]
        ] ],
        [ "Daughterboard notes", "page_usrp_e3xx.html#e31x_dboards", [
          [ "Frontend tuning", "page_usrp_e3xx.html#e31x_dboard_e310_tuning", null ],
          [ "Frontend gain", "page_usrp_e3xx.html#e31x_dboard_e310_gain", null ],
          [ "Frontend LO lock status", "page_usrp_e3xx.html#e31x_dboard_e310_pll", null ],
          [ "Frontend Filter and Antenna Switches", "page_usrp_e3xx.html#e31x_dboard_e310_band_select", null ],
          [ "Frontend Side A Filter and Antenna Switches", "page_usrp_e3xx.html#e31x_dboard_e310_frontend_a_switches", null ],
          [ "Frontend Side B Filter and Antenna Switches", "page_usrp_e3xx.html#e31x_dboard_e310_frontend_b_switches", null ]
        ] ]
      ] ],
      [ "E320-specific Features", "page_usrp_e3xx.html#e320_neon", [
        [ "Front and Rear Panel", "page_usrp_e3xx.html#e320_panels", null ],
        [ "Front Panel GPIO", "page_usrp_e3xx.html#e320_gpio", null ],
        [ "EEPROM flags", "page_usrp_e3xx.html#e320_eeprom_flags", null ]
      ] ],
      [ "E3XX FPGA Register Map", "page_usrp_e3xx.html#e3xx_regmap", null ]
    ] ],
    [ "USRP X3x0 Series", "page_usrp_x3x0.html", "page_usrp_x3x0" ],
    [ "USRP1", "page_usrp1.html", [
      [ "Comparative features list", "page_usrp1.html#usrp1_features", null ],
      [ "Specify a Non-standard Image", "page_usrp1.html#usrp1_imgs", null ],
      [ "Missing and Emulated Features", "page_usrp1.html#usrp1_emul", [
        [ "List of emulated features", "page_usrp1.html#usrp1_emul_list", null ],
        [ "List of missing features", "page_usrp1.html#usrp1_emul_listmissing", null ]
      ] ],
      [ "Hardware Setup Notes", "page_usrp1.html#usrp1_hw", [
        [ "External clock modification", "page_usrp1.html#usrp1_hw_extclk", null ]
      ] ],
      [ "Known Issues", "page_usrp1.html#usrp1_known_issues", null ]
    ] ],
    [ "USRP B100 Series", "page_usrp_b100.html", [
      [ "Comparative features list", "page_usrp_b100.html#b100_features", null ],
      [ "Specify a Non-standard Image", "page_usrp_b100.html#b100_imgs", null ],
      [ "Changing the Master Clock Rate", "page_usrp_b100.html#b100_mcr", [
        [ "Set 61.44 MHz - uses external VCXO", "page_usrp_b100.html#b100_mcr_vcxo", null ],
        [ "Set other rates - uses internal VCO", "page_usrp_b100.html#b100_mcr_vco", null ]
      ] ],
      [ "Hardware setup notes", "page_usrp_b100.html#b100_hw", [
        [ "Front panel LEDs", "page_usrp_b100.html#b100_hw_leds", null ]
      ] ],
      [ "Miscellaneous", "page_usrp_b100.html#b100_misc", [
        [ "Available Sensors", "page_usrp_b100.html#b100_misc_sensors", null ],
        [ "Known Issues", "page_usrp_b100.html#b100_known_issues", null ]
      ] ]
    ] ],
    [ "USRP-E1x0 Series", "page_usrp_e1x0.html", "page_usrp_e1x0" ],
    [ "Daughterboards", "page_dboards.html", "page_dboards" ],
    [ "TwinRX Daughterboard", "page_twinrx.html", [
      [ "TwinRX Properties", "page_twinrx.html#twinrx_dboards", [
        [ "Master Clock Rate, Sampling Rate, and Tick Rate", "page_twinrx.html#twinrx_dboards_mcr", null ],
        [ "Frequency Bands", "page_twinrx.html#twinrx_frequency_bands", null ],
        [ "Local Oscillator Sharing", "page_twinrx.html#twinrx_lo_sharing", null ],
        [ "Antenna Routing", "page_twinrx.html#twinrx_antenna_routing", null ]
      ] ]
    ] ],
    [ "OctoClock", "page_octoclock.html", [
      [ "Feature list", "page_octoclock.html#octoclock_features", null ],
      [ "Detecting an Ethernet-compatible device", "page_octoclock.html#detecting_new_unit", null ],
      [ "Upgrading your device", "page_octoclock.html#upgrading_device", [
        [ "Getting the latest firmware images", "page_octoclock.html#getting_latest", null ],
        [ "Burning the bootloader onto the device", "page_octoclock.html#bootloader", null ],
        [ "Uploading the firmware via Ethernet", "page_octoclock.html#firmware", null ],
        [ "Updating the device's EEPROM", "page_octoclock.html#eeprom", null ]
      ] ],
      [ "Using your device", "page_octoclock.html#usage", [
        [ "The boot process", "page_octoclock.html#boot_process", null ],
        [ "Selecting a reference", "page_octoclock.html#selecting", null ],
        [ "Front Panel LEDs", "page_octoclock.html#front_panel_leds", null ],
        [ "Communication with UHD", "page_octoclock.html#uhd", null ]
      ] ]
    ] ]
];