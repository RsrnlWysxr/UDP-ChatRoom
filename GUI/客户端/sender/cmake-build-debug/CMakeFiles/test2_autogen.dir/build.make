# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = "/Users/liyihang/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/liyihang/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liyihang/QT_learn/test02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liyihang/QT_learn/test02/cmake-build-debug

# Utility rule file for test2_autogen.

# Include the progress variables for this target.
include CMakeFiles/test2_autogen.dir/progress.make

CMakeFiles/test2_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liyihang/QT_learn/test02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC for target test2"
	"/Users/liyihang/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/182.4505.18/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E cmake_autogen /Users/liyihang/QT_learn/test02/cmake-build-debug/CMakeFiles/test2_autogen.dir/AutogenInfo.cmake Debug

test2_autogen: CMakeFiles/test2_autogen
test2_autogen: CMakeFiles/test2_autogen.dir/build.make

.PHONY : test2_autogen

# Rule to build all files generated by this target.
CMakeFiles/test2_autogen.dir/build: test2_autogen

.PHONY : CMakeFiles/test2_autogen.dir/build

CMakeFiles/test2_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test2_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test2_autogen.dir/clean

CMakeFiles/test2_autogen.dir/depend:
	cd /Users/liyihang/QT_learn/test02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liyihang/QT_learn/test02 /Users/liyihang/QT_learn/test02 /Users/liyihang/QT_learn/test02/cmake-build-debug /Users/liyihang/QT_learn/test02/cmake-build-debug /Users/liyihang/QT_learn/test02/cmake-build-debug/CMakeFiles/test2_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test2_autogen.dir/depend

