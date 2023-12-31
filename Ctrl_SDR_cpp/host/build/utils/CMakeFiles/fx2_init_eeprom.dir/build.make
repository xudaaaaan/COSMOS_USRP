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
include utils/CMakeFiles/fx2_init_eeprom.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/fx2_init_eeprom.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/fx2_init_eeprom.dir/flags.make

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o: utils/CMakeFiles/fx2_init_eeprom.dir/flags.make
utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o: ../utils/fx2_init_eeprom.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o"
	cd /root/uhd/host/build/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o -c /root/uhd/host/utils/fx2_init_eeprom.cpp

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.i"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/utils/fx2_init_eeprom.cpp > CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.i

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.s"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/utils/fx2_init_eeprom.cpp -o CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.s

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.requires:

.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.requires

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.provides: utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/fx2_init_eeprom.dir/build.make utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.provides.build
.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.provides

utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.provides.build: utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o


# Object files for target fx2_init_eeprom
fx2_init_eeprom_OBJECTS = \
"CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o"

# External object files for target fx2_init_eeprom
fx2_init_eeprom_EXTERNAL_OBJECTS =

utils/fx2_init_eeprom: utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o
utils/fx2_init_eeprom: utils/CMakeFiles/fx2_init_eeprom.dir/build.make
utils/fx2_init_eeprom: lib/libuhd.so.3.15.0
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_regex.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_thread.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_system.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libpthread.so
utils/fx2_init_eeprom: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
utils/fx2_init_eeprom: utils/CMakeFiles/fx2_init_eeprom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fx2_init_eeprom"
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fx2_init_eeprom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/fx2_init_eeprom.dir/build: utils/fx2_init_eeprom

.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/build

utils/CMakeFiles/fx2_init_eeprom.dir/requires: utils/CMakeFiles/fx2_init_eeprom.dir/fx2_init_eeprom.cpp.o.requires

.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/requires

utils/CMakeFiles/fx2_init_eeprom.dir/clean:
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -P CMakeFiles/fx2_init_eeprom.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/clean

utils/CMakeFiles/fx2_init_eeprom.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/utils /root/uhd/host/build /root/uhd/host/build/utils /root/uhd/host/build/utils/CMakeFiles/fx2_init_eeprom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/fx2_init_eeprom.dir/depend

