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
include utils/CMakeFiles/b2xx_fx3_utils.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/b2xx_fx3_utils.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/b2xx_fx3_utils.dir/flags.make

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o: utils/CMakeFiles/b2xx_fx3_utils.dir/flags.make
utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o: ../utils/b2xx_fx3_utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o"
	cd /root/uhd/host/build/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o -c /root/uhd/host/utils/b2xx_fx3_utils.cpp

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.i"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/utils/b2xx_fx3_utils.cpp > CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.i

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.s"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/utils/b2xx_fx3_utils.cpp -o CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.s

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.requires:

.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.requires

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.provides: utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/b2xx_fx3_utils.dir/build.make utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.provides.build
.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.provides

utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.provides.build: utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o


# Object files for target b2xx_fx3_utils
b2xx_fx3_utils_OBJECTS = \
"CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o"

# External object files for target b2xx_fx3_utils
b2xx_fx3_utils_EXTERNAL_OBJECTS =

utils/b2xx_fx3_utils: utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o
utils/b2xx_fx3_utils: utils/CMakeFiles/b2xx_fx3_utils.dir/build.make
utils/b2xx_fx3_utils: lib/libuhd.so.3.15.0
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_regex.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_thread.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_system.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libpthread.so
utils/b2xx_fx3_utils: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
utils/b2xx_fx3_utils: utils/CMakeFiles/b2xx_fx3_utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable b2xx_fx3_utils"
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/b2xx_fx3_utils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/b2xx_fx3_utils.dir/build: utils/b2xx_fx3_utils

.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/build

utils/CMakeFiles/b2xx_fx3_utils.dir/requires: utils/CMakeFiles/b2xx_fx3_utils.dir/b2xx_fx3_utils.cpp.o.requires

.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/requires

utils/CMakeFiles/b2xx_fx3_utils.dir/clean:
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -P CMakeFiles/b2xx_fx3_utils.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/clean

utils/CMakeFiles/b2xx_fx3_utils.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/utils /root/uhd/host/build /root/uhd/host/build/utils /root/uhd/host/build/utils/CMakeFiles/b2xx_fx3_utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/b2xx_fx3_utils.dir/depend

