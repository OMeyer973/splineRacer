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
CMAKE_SOURCE_DIR = /home/olivier/Documents/splineRunner/splineRacer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olivier/Documents/splineRunner/splineRacer-build

# Include any dependencies generated for this target.
include TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/depend.make

# Include the progress variables for this target.
include TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/progress.make

# Include the compile flags for this target's objects.
include TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/flags.make

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/flags.make
TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o: /home/olivier/Documents/splineRunner/splineRacer/TP_splineTest/splineTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olivier/Documents/splineRunner/splineRacer-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o"
	cd /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o -c /home/olivier/Documents/splineRunner/splineRacer/TP_splineTest/splineTest.cpp

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.i"
	cd /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olivier/Documents/splineRunner/splineRacer/TP_splineTest/splineTest.cpp > CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.i

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.s"
	cd /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olivier/Documents/splineRunner/splineRacer/TP_splineTest/splineTest.cpp -o CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.s

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.requires:

.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.requires

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.provides: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.requires
	$(MAKE) -f TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/build.make TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.provides.build
.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.provides

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.provides.build: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o


# Object files for target TP_splineTest_splineTest
TP_splineTest_splineTest_OBJECTS = \
"CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o"

# External object files for target TP_splineTest_splineTest
TP_splineTest_splineTest_EXTERNAL_OBJECTS =

TP_splineTest/TP_splineTest_splineTest: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o
TP_splineTest/TP_splineTest_splineTest: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/build.make
TP_splineTest/TP_splineTest_splineTest: glimac/libglimac.a
TP_splineTest/TP_splineTest_splineTest: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP_splineTest/TP_splineTest_splineTest: /usr/lib/x86_64-linux-gnu/libSDL.so
TP_splineTest/TP_splineTest_splineTest: /usr/lib/x86_64-linux-gnu/libGL.so.1
TP_splineTest/TP_splineTest_splineTest: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP_splineTest/TP_splineTest_splineTest: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olivier/Documents/splineRunner/splineRacer-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP_splineTest_splineTest"
	cd /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP_splineTest_splineTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/build: TP_splineTest/TP_splineTest_splineTest

.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/build

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/requires: TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/splineTest.cpp.o.requires

.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/requires

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/clean:
	cd /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest && $(CMAKE_COMMAND) -P CMakeFiles/TP_splineTest_splineTest.dir/cmake_clean.cmake
.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/clean

TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/depend:
	cd /home/olivier/Documents/splineRunner/splineRacer-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olivier/Documents/splineRunner/splineRacer /home/olivier/Documents/splineRunner/splineRacer/TP_splineTest /home/olivier/Documents/splineRunner/splineRacer-build /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest /home/olivier/Documents/splineRunner/splineRacer-build/TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP_splineTest/CMakeFiles/TP_splineTest_splineTest.dir/depend

