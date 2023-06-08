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
include examples/CMakeFiles/tx_waveforms.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/tx_waveforms.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/tx_waveforms.dir/flags.make

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o: examples/CMakeFiles/tx_waveforms.dir/flags.make
examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o: ../examples/tx_waveforms.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o"
	cd /root/uhd/host/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o -c /root/uhd/host/examples/tx_waveforms.cpp

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.i"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/examples/tx_waveforms.cpp > CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.i

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.s"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/examples/tx_waveforms.cpp -o CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.s

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.requires:

.PHONY : examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.requires

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.provides: examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/tx_waveforms.dir/build.make examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.provides.build
.PHONY : examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.provides

examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.provides.build: examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o


# Object files for target tx_waveforms
tx_waveforms_OBJECTS = \
"CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o"

# External object files for target tx_waveforms
tx_waveforms_EXTERNAL_OBJECTS =

examples/tx_waveforms: examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o
examples/tx_waveforms: examples/CMakeFiles/tx_waveforms.dir/build.make
examples/tx_waveforms: lib/libuhd.so.3.15.0
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/tx_waveforms: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/tx_waveforms: examples/CMakeFiles/tx_waveforms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tx_waveforms"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tx_waveforms.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/tx_waveforms.dir/build: examples/tx_waveforms

.PHONY : examples/CMakeFiles/tx_waveforms.dir/build

examples/CMakeFiles/tx_waveforms.dir/requires: examples/CMakeFiles/tx_waveforms.dir/tx_waveforms.cpp.o.requires

.PHONY : examples/CMakeFiles/tx_waveforms.dir/requires

examples/CMakeFiles/tx_waveforms.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/tx_waveforms.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/tx_waveforms.dir/clean

examples/CMakeFiles/tx_waveforms.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/tx_waveforms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/tx_waveforms.dir/depend

