# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/uhd/host

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/uhd/host/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/rfnoc_rx_to_file.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/rfnoc_rx_to_file.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/rfnoc_rx_to_file.dir/flags.make

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o: examples/CMakeFiles/rfnoc_rx_to_file.dir/flags.make
examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o: ../examples/rfnoc_rx_to_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o"
	cd /root/uhd/host/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o -c /root/uhd/host/examples/rfnoc_rx_to_file.cpp

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.i"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/examples/rfnoc_rx_to_file.cpp > CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.i

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.s"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/examples/rfnoc_rx_to_file.cpp -o CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.s

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.requires:

.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.requires

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.provides: examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/rfnoc_rx_to_file.dir/build.make examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.provides.build
.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.provides

examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.provides.build: examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o


# Object files for target rfnoc_rx_to_file
rfnoc_rx_to_file_OBJECTS = \
"CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o"

# External object files for target rfnoc_rx_to_file
rfnoc_rx_to_file_EXTERNAL_OBJECTS =

examples/rfnoc_rx_to_file: examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o
examples/rfnoc_rx_to_file: examples/CMakeFiles/rfnoc_rx_to_file.dir/build.make
examples/rfnoc_rx_to_file: lib/libuhd.so.3.15.0
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/rfnoc_rx_to_file: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/rfnoc_rx_to_file: examples/CMakeFiles/rfnoc_rx_to_file.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rfnoc_rx_to_file"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rfnoc_rx_to_file.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/rfnoc_rx_to_file.dir/build: examples/rfnoc_rx_to_file

.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/build

examples/CMakeFiles/rfnoc_rx_to_file.dir/requires: examples/CMakeFiles/rfnoc_rx_to_file.dir/rfnoc_rx_to_file.cpp.o.requires

.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/requires

examples/CMakeFiles/rfnoc_rx_to_file.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/rfnoc_rx_to_file.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/clean

examples/CMakeFiles/rfnoc_rx_to_file.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/rfnoc_rx_to_file.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/rfnoc_rx_to_file.dir/depend
