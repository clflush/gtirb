# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/eschulte/lisp/local-projects/gtirb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/eschulte/lisp/local-projects/gtirb

# Include any dependencies generated for this target.
include src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/depend.make

# Include the progress variables for this target.
include src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/progress.make

# Include the compile flags for this target's objects.
include src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/flags.make

src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o: src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/flags.make
src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o: src/test/testInputBinary/TestInputBinary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/eschulte/lisp/local-projects/gtirb/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o"
	cd /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o -c /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary/TestInputBinary.cpp

src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.i"
	cd /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary/TestInputBinary.cpp > CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.i

src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.s"
	cd /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary/TestInputBinary.cpp -o CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.s

# Object files for target gtirbTestInputBinary16
gtirbTestInputBinary16_OBJECTS = \
"CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o"

# External object files for target gtirbTestInputBinary16
gtirbTestInputBinary16_EXTERNAL_OBJECTS =

bin/gtirbTestInputBinary16: src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/TestInputBinary.cpp.o
bin/gtirbTestInputBinary16: src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/build.make
bin/gtirbTestInputBinary16: src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/eschulte/lisp/local-projects/gtirb/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/gtirbTestInputBinary16"
	cd /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtirbTestInputBinary16.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/build: bin/gtirbTestInputBinary16

.PHONY : src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/build

src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/clean:
	cd /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary && $(CMAKE_COMMAND) -P CMakeFiles/gtirbTestInputBinary16.dir/cmake_clean.cmake
.PHONY : src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/clean

src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/depend:
	cd /home/eschulte/lisp/local-projects/gtirb && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/eschulte/lisp/local-projects/gtirb /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary /home/eschulte/lisp/local-projects/gtirb /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary /home/eschulte/lisp/local-projects/gtirb/src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/test/testInputBinary/CMakeFiles/gtirbTestInputBinary16.dir/depend

