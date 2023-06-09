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
include examples/CMakeFiles/rx_samples_c.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/rx_samples_c.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/rx_samples_c.dir/flags.make

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o: examples/CMakeFiles/rx_samples_c.dir/flags.make
examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o: ../examples/rx_samples_c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o"
	cd /root/uhd/host/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o   -c /root/uhd/host/examples/rx_samples_c.c

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/rx_samples_c.dir/rx_samples_c.c.i"
	cd /root/uhd/host/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/uhd/host/examples/rx_samples_c.c > CMakeFiles/rx_samples_c.dir/rx_samples_c.c.i

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/rx_samples_c.dir/rx_samples_c.c.s"
	cd /root/uhd/host/build/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/uhd/host/examples/rx_samples_c.c -o CMakeFiles/rx_samples_c.dir/rx_samples_c.c.s

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.requires:

.PHONY : examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.requires

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.provides: examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.requires
	$(MAKE) -f examples/CMakeFiles/rx_samples_c.dir/build.make examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.provides.build
.PHONY : examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.provides

examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.provides.build: examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o


# Object files for target rx_samples_c
rx_samples_c_OBJECTS = \
"CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o"

# External object files for target rx_samples_c
rx_samples_c_EXTERNAL_OBJECTS =

examples/rx_samples_c: examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o
examples/rx_samples_c: examples/CMakeFiles/rx_samples_c.dir/build.make
examples/rx_samples_c: lib/libuhd.so.3.15.0
examples/rx_samples_c: examples/getopt/libgetopt.a
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_regex.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_thread.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_system.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libpthread.so
examples/rx_samples_c: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
examples/rx_samples_c: examples/CMakeFiles/rx_samples_c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable rx_samples_c"
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rx_samples_c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/rx_samples_c.dir/build: examples/rx_samples_c

.PHONY : examples/CMakeFiles/rx_samples_c.dir/build

examples/CMakeFiles/rx_samples_c.dir/requires: examples/CMakeFiles/rx_samples_c.dir/rx_samples_c.c.o.requires

.PHONY : examples/CMakeFiles/rx_samples_c.dir/requires

examples/CMakeFiles/rx_samples_c.dir/clean:
	cd /root/uhd/host/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/rx_samples_c.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/rx_samples_c.dir/clean

examples/CMakeFiles/rx_samples_c.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/examples /root/uhd/host/build /root/uhd/host/build/examples /root/uhd/host/build/examples/CMakeFiles/rx_samples_c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/rx_samples_c.dir/depend

