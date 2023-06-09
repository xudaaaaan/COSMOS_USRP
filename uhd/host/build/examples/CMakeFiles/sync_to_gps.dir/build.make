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
include examples/CMakeFiles/sync_to_gps.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/sync_to_gps.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/sync_to_gps.dir/flags.make

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o: examples/CMakeFiles/sync_to_gps.dir/flags.make
examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o: ../examples/sync_to_gps.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o"
	cd /root/uhd/host/build/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o -c /root/uhd/host/examples/sync_to_gps.cpp

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.i"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/examples/sync_to_gps.cpp > CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.i

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.s"
	cd /root/uhd/host/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/examples/sync_to_gps.cpp -o CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.s

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.requires:

.PHONY : examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.requires

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.provides: examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.requires
	$(MAKE) -f examples/CMakeFiles/sync_to_gps.dir/build.make examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.provides.build
.PHONY : examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.provides

examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.provides.build: examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o


# Object files for target sync_to_gps
sync_to_gps_OBJECTS = \
"CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o"

# External object files for target sync_to_gps
sync_to_gps_EXTERNAL_OBJECTS =

examples/sync_to_gps: examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o
examples/sync_to_gps: examples/CMakeFiles/sync_to_gps.dir/build.make
examples/sync_to_gps: lib/libuhd.so.3.15.0
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/sync_to_gps: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/sync_to_gps: examples/CMakeFiles/sync_to_gps.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sync_to_gps"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sync_to_gps.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/sync_to_gps.dir/build: examples/sync_to_gps

.PHONY : examples/CMakeFiles/sync_to_gps.dir/build

examples/CMakeFiles/sync_to_gps.dir/requires: examples/CMakeFiles/sync_to_gps.dir/sync_to_gps.cpp.o.requires

.PHONY : examples/CMakeFiles/sync_to_gps.dir/requires

examples/CMakeFiles/sync_to_gps.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/sync_to_gps.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/sync_to_gps.dir/clean

examples/CMakeFiles/sync_to_gps.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/sync_to_gps.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/sync_to_gps.dir/depend
