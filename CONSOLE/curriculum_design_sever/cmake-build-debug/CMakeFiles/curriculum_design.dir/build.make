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
CMAKE_SOURCE_DIR = /Users/liyihang/curriculum_design/curriculum_design_sever

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/curriculum_design.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/curriculum_design.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/curriculum_design.dir/flags.make

CMakeFiles/curriculum_design.dir/main.cpp.o: CMakeFiles/curriculum_design.dir/flags.make
CMakeFiles/curriculum_design.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/curriculum_design.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/curriculum_design.dir/main.cpp.o -c /Users/liyihang/curriculum_design/curriculum_design_sever/main.cpp

CMakeFiles/curriculum_design.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/curriculum_design.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liyihang/curriculum_design/curriculum_design_sever/main.cpp > CMakeFiles/curriculum_design.dir/main.cpp.i

CMakeFiles/curriculum_design.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/curriculum_design.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liyihang/curriculum_design/curriculum_design_sever/main.cpp -o CMakeFiles/curriculum_design.dir/main.cpp.s

# Object files for target curriculum_design
curriculum_design_OBJECTS = \
"CMakeFiles/curriculum_design.dir/main.cpp.o"

# External object files for target curriculum_design
curriculum_design_EXTERNAL_OBJECTS =

curriculum_design: CMakeFiles/curriculum_design.dir/main.cpp.o
curriculum_design: CMakeFiles/curriculum_design.dir/build.make
curriculum_design: /usr/local/Cellar/qt/5.12.0/lib/QtWidgets.framework/QtWidgets
curriculum_design: /usr/local/Cellar/qt/5.12.0/lib/QtGui.framework/QtGui
curriculum_design: /usr/local/Cellar/qt/5.12.0/lib/QtCore.framework/QtCore
curriculum_design: CMakeFiles/curriculum_design.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable curriculum_design"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/curriculum_design.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/curriculum_design.dir/build: curriculum_design

.PHONY : CMakeFiles/curriculum_design.dir/build

CMakeFiles/curriculum_design.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/curriculum_design.dir/cmake_clean.cmake
.PHONY : CMakeFiles/curriculum_design.dir/clean

CMakeFiles/curriculum_design.dir/depend:
	cd /Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liyihang/curriculum_design/curriculum_design_sever /Users/liyihang/curriculum_design/curriculum_design_sever /Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug /Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug /Users/liyihang/curriculum_design/curriculum_design_sever/cmake-build-debug/CMakeFiles/curriculum_design.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/curriculum_design.dir/depend

