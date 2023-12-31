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
include utils/CMakeFiles/uhd_image_loader.dir/depend.make

# Include the progress variables for this target.
include utils/CMakeFiles/uhd_image_loader.dir/progress.make

# Include the compile flags for this target's objects.
include utils/CMakeFiles/uhd_image_loader.dir/flags.make

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o: utils/CMakeFiles/uhd_image_loader.dir/flags.make
utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o: ../utils/uhd_image_loader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o"
	cd /root/uhd/host/build/utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o -c /root/uhd/host/utils/uhd_image_loader.cpp

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.i"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/uhd/host/utils/uhd_image_loader.cpp > CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.i

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.s"
	cd /root/uhd/host/build/utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/uhd/host/utils/uhd_image_loader.cpp -o CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.s

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.requires:

.PHONY : utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.requires

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.provides: utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.requires
	$(MAKE) -f utils/CMakeFiles/uhd_image_loader.dir/build.make utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.provides.build
.PHONY : utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.provides

utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.provides.build: utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o


# Object files for target uhd_image_loader
uhd_image_loader_OBJECTS = \
"CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o"

# External object files for target uhd_image_loader
uhd_image_loader_EXTERNAL_OBJECTS =

utils/uhd_image_loader: utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o
utils/uhd_image_loader: utils/CMakeFiles/uhd_image_loader.dir/build.make
utils/uhd_image_loader: lib/libuhd.so.3.15.0
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_regex.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_thread.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_system.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libpthread.so
utils/uhd_image_loader: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
utils/uhd_image_loader: utils/CMakeFiles/uhd_image_loader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uhd_image_loader"
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uhd_image_loader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
utils/CMakeFiles/uhd_image_loader.dir/build: utils/uhd_image_loader

.PHONY : utils/CMakeFiles/uhd_image_loader.dir/build

utils/CMakeFiles/uhd_image_loader.dir/requires: utils/CMakeFiles/uhd_image_loader.dir/uhd_image_loader.cpp.o.requires

.PHONY : utils/CMakeFiles/uhd_image_loader.dir/requires

utils/CMakeFiles/uhd_image_loader.dir/clean:
	cd /root/uhd/host/build/utils && $(CMAKE_COMMAND) -P CMakeFiles/uhd_image_loader.dir/cmake_clean.cmake
.PHONY : utils/CMakeFiles/uhd_image_loader.dir/clean

utils/CMakeFiles/uhd_image_loader.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/utils /root/uhd/host/build /root/uhd/host/build/utils /root/uhd/host/build/utils/CMakeFiles/uhd_image_loader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : utils/CMakeFiles/uhd_image_loader.dir/depend

