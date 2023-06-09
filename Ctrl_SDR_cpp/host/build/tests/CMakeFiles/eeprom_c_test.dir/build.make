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
include tests/CMakeFiles/eeprom_c_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/eeprom_c_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/eeprom_c_test.dir/flags.make

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o: tests/CMakeFiles/eeprom_c_test.dir/flags.make
tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o: ../tests/eeprom_c_test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o"
	cd /root/uhd/host/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o   -c /root/uhd/host/tests/eeprom_c_test.c

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.i"
	cd /root/uhd/host/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/uhd/host/tests/eeprom_c_test.c > CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.i

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.s"
	cd /root/uhd/host/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/uhd/host/tests/eeprom_c_test.c -o CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.s

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.requires:

.PHONY : tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.requires

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.provides: tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.requires
	$(MAKE) -f tests/CMakeFiles/eeprom_c_test.dir/build.make tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.provides.build
.PHONY : tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.provides

tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.provides.build: tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o


# Object files for target eeprom_c_test
eeprom_c_test_OBJECTS = \
"CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o"

# External object files for target eeprom_c_test
eeprom_c_test_EXTERNAL_OBJECTS =

tests/eeprom_c_test: tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o
tests/eeprom_c_test: tests/CMakeFiles/eeprom_c_test.dir/build.make
tests/eeprom_c_test: lib/libuhd.so.3.15.0
tests/eeprom_c_test: tests/common/libuhd_test.a
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_regex.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_system.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libpthread.so
tests/eeprom_c_test: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
tests/eeprom_c_test: tests/CMakeFiles/eeprom_c_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable eeprom_c_test"
	cd /root/uhd/host/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eeprom_c_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/eeprom_c_test.dir/build: tests/eeprom_c_test

.PHONY : tests/CMakeFiles/eeprom_c_test.dir/build

tests/CMakeFiles/eeprom_c_test.dir/requires: tests/CMakeFiles/eeprom_c_test.dir/eeprom_c_test.c.o.requires

.PHONY : tests/CMakeFiles/eeprom_c_test.dir/requires

tests/CMakeFiles/eeprom_c_test.dir/clean:
	cd /root/uhd/host/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/eeprom_c_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/eeprom_c_test.dir/clean

tests/CMakeFiles/eeprom_c_test.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/tests /root/uhd/host/build /root/uhd/host/build/tests /root/uhd/host/build/tests/CMakeFiles/eeprom_c_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/eeprom_c_test.dir/depend

