# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/aa12413/Documents/cgcoursework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/aa12413/Documents/cgcoursework

# Include any dependencies generated for this target.
include CMakeFiles/cgExercise01.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cgExercise01.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cgExercise01.dir/flags.make

CMakeFiles/cgExercise01.dir/main01.o: CMakeFiles/cgExercise01.dir/flags.make
CMakeFiles/cgExercise01.dir/main01.o: main01.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /homes/aa12413/Documents/cgcoursework/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cgExercise01.dir/main01.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cgExercise01.dir/main01.o -c /homes/aa12413/Documents/cgcoursework/main01.cpp

CMakeFiles/cgExercise01.dir/main01.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cgExercise01.dir/main01.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /homes/aa12413/Documents/cgcoursework/main01.cpp > CMakeFiles/cgExercise01.dir/main01.i

CMakeFiles/cgExercise01.dir/main01.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cgExercise01.dir/main01.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /homes/aa12413/Documents/cgcoursework/main01.cpp -o CMakeFiles/cgExercise01.dir/main01.s

CMakeFiles/cgExercise01.dir/main01.o.requires:
.PHONY : CMakeFiles/cgExercise01.dir/main01.o.requires

CMakeFiles/cgExercise01.dir/main01.o.provides: CMakeFiles/cgExercise01.dir/main01.o.requires
	$(MAKE) -f CMakeFiles/cgExercise01.dir/build.make CMakeFiles/cgExercise01.dir/main01.o.provides.build
.PHONY : CMakeFiles/cgExercise01.dir/main01.o.provides

CMakeFiles/cgExercise01.dir/main01.o.provides.build: CMakeFiles/cgExercise01.dir/main01.o

# Object files for target cgExercise01
cgExercise01_OBJECTS = \
"CMakeFiles/cgExercise01.dir/main01.o"

# External object files for target cgExercise01
cgExercise01_EXTERNAL_OBJECTS =

cgExercise01: CMakeFiles/cgExercise01.dir/main01.o
cgExercise01: CMakeFiles/cgExercise01.dir/build.make
cgExercise01: /usr/lib/x86_64-linux-gnu/libGL.so
cgExercise01: /usr/lib/x86_64-linux-gnu/libGLU.so
cgExercise01: /usr/lib/x86_64-linux-gnu/libGLEW.so
cgExercise01: /usr/lib/x86_64-linux-gnu/libglut.so
cgExercise01: CMakeFiles/cgExercise01.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable cgExercise01"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cgExercise01.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cgExercise01.dir/build: cgExercise01
.PHONY : CMakeFiles/cgExercise01.dir/build

CMakeFiles/cgExercise01.dir/requires: CMakeFiles/cgExercise01.dir/main01.o.requires
.PHONY : CMakeFiles/cgExercise01.dir/requires

CMakeFiles/cgExercise01.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cgExercise01.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cgExercise01.dir/clean

CMakeFiles/cgExercise01.dir/depend:
	cd /homes/aa12413/Documents/cgcoursework && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/aa12413/Documents/cgcoursework /homes/aa12413/Documents/cgcoursework /homes/aa12413/Documents/cgcoursework /homes/aa12413/Documents/cgcoursework /homes/aa12413/Documents/cgcoursework/CMakeFiles/cgExercise01.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cgExercise01.dir/depend

