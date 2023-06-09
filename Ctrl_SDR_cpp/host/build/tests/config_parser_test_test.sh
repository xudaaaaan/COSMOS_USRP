#!/bin/sh
export PATH=/root/uhd/host/build/tests:$PATH
export LD_LIBRARY_PATH=/root/uhd/host/build/lib:/root/uhd/host/build/tests:/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
export UHD_RFNOC_DIR=/root/uhd/host/include/uhd/rfnoc
config_parser_test 
