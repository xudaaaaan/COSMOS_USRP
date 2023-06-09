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
include examples/CMakeFiles/benchmark_streamer.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/benchmark_streamer.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/benchmark_streamer.dir/flags.make

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o: examples/CMakeFiles/benchmark_streamer.dir/flags.make
examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o: ../examples/benchmark_streamer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o"
	cd /root/uhd/host/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o -c /root/uhd/host/examples/benchmark_streamer.cpp

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.i"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/examples/benchmark_streamer.cpp > CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.i

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.s"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/examples/benchmark_streamer.cpp -o CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.s

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.requires:

.PHONY : examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.requires

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.provides: examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/benchmark_streamer.dir/build.make examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.provides.build
.PHONY : examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.provides

examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.provides.build: examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o


# Object files for target benchmark_streamer
benchmark_streamer_OBJECTS = \
"CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o"

# External object files for target benchmark_streamer
benchmark_streamer_EXTERNAL_OBJECTS =

examples/benchmark_streamer: examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o
examples/benchmark_streamer: examples/CMakeFiles/benchmark_streamer.dir/build.make
examples/benchmark_streamer: lib/libuhd.so.3.15.0
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/benchmark_streamer: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/benchmark_streamer: examples/CMakeFiles/benchmark_streamer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable benchmark_streamer"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/benchmark_streamer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/benchmark_streamer.dir/build: examples/benchmark_streamer

.PHONY : examples/CMakeFiles/benchmark_streamer.dir/build

examples/CMakeFiles/benchmark_streamer.dir/requires: examples/CMakeFiles/benchmark_streamer.dir/benchmark_streamer.cpp.o.requires

.PHONY : examples/CMakeFiles/benchmark_streamer.dir/requires

examples/CMakeFiles/benchmark_streamer.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/benchmark_streamer.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/benchmark_streamer.dir/clean

examples/CMakeFiles/benchmark_streamer.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/benchmark_streamer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/benchmark_streamer.dir/depend

