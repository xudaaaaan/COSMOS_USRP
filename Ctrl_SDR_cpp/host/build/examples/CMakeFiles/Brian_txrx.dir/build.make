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
include examples/CMakeFiles/Brian_txrx.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/Brian_txrx.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/Brian_txrx.dir/flags.make

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o: examples/CMakeFiles/Brian_txrx.dir/flags.make
examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o: ../examples/Brian_txrx.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o"
	cd /root/uhd/host/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o -c /root/uhd/host/examples/Brian_txrx.cpp

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.i"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/examples/Brian_txrx.cpp > CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.i

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.s"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/examples/Brian_txrx.cpp -o CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.s

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.requires:

.PHONY : examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.requires

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.provides: examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/Brian_txrx.dir/build.make examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.provides.build
.PHONY : examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.provides

examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.provides.build: examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o


# Object files for target Brian_txrx
Brian_txrx_OBJECTS = \
"CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o"

# External object files for target Brian_txrx
Brian_txrx_EXTERNAL_OBJECTS =

examples/Brian_txrx: examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o
examples/Brian_txrx: examples/CMakeFiles/Brian_txrx.dir/build.make
examples/Brian_txrx: lib/libuhd.so.3.15.0
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/Brian_txrx: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/Brian_txrx: examples/CMakeFiles/Brian_txrx.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Brian_txrx"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Brian_txrx.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/Brian_txrx.dir/build: examples/Brian_txrx

.PHONY : examples/CMakeFiles/Brian_txrx.dir/build

examples/CMakeFiles/Brian_txrx.dir/requires: examples/CMakeFiles/Brian_txrx.dir/Brian_txrx.cpp.o.requires

.PHONY : examples/CMakeFiles/Brian_txrx.dir/requires

examples/CMakeFiles/Brian_txrx.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/Brian_txrx.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/Brian_txrx.dir/clean

examples/CMakeFiles/Brian_txrx.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/Brian_txrx.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/Brian_txrx.dir/depend

