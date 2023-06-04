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

# Utility rule file for test_n3x0.

# Include the progress variables for this target.
include tests/devtest/CMakeFiles/test_n3x0.dir/progress.make

tests/devtest/CMakeFiles/test_n3x0:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/uhd/host/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running device test on all connected N3XX devices:"
	cd /root/uhd/host/build/tests/devtest && /usr/bin/python3 /root/uhd/host/tests/devtest/run_testsuite.py --src-dir /root/uhd/host/tests/devtest --devtest-pattern n3x0 --device-filter n3xx --build-type Release --build-dir /root/uhd/host/build --python-interp /usr/bin/python3

test_n3x0: tests/devtest/CMakeFiles/test_n3x0
test_n3x0: tests/devtest/CMakeFiles/test_n3x0.dir/build.make

.PHONY : test_n3x0

# Rule to build all files generated by this target.
tests/devtest/CMakeFiles/test_n3x0.dir/build: test_n3x0

.PHONY : tests/devtest/CMakeFiles/test_n3x0.dir/build

tests/devtest/CMakeFiles/test_n3x0.dir/clean:
	cd /root/uhd/host/build/tests/devtest && $(CMAKE_COMMAND) -P CMakeFiles/test_n3x0.dir/cmake_clean.cmake
.PHONY : tests/devtest/CMakeFiles/test_n3x0.dir/clean

tests/devtest/CMakeFiles/test_n3x0.dir/depend:
	cd /root/uhd/host/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/uhd/host /root/uhd/host/tests/devtest /root/uhd/host/build /root/uhd/host/build/tests/devtest /root/uhd/host/build/tests/devtest/CMakeFiles/test_n3x0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/devtest/CMakeFiles/test_n3x0.dir/depend

