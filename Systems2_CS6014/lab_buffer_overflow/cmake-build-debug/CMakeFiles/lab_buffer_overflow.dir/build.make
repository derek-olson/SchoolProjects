# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab_buffer_overflow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab_buffer_overflow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab_buffer_overflow.dir/flags.make

CMakeFiles/lab_buffer_overflow.dir/main.cpp.o: CMakeFiles/lab_buffer_overflow.dir/flags.make
CMakeFiles/lab_buffer_overflow.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab_buffer_overflow.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab_buffer_overflow.dir/main.cpp.o -c /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/main.cpp

CMakeFiles/lab_buffer_overflow.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab_buffer_overflow.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/main.cpp > CMakeFiles/lab_buffer_overflow.dir/main.cpp.i

CMakeFiles/lab_buffer_overflow.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab_buffer_overflow.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/main.cpp -o CMakeFiles/lab_buffer_overflow.dir/main.cpp.s

# Object files for target lab_buffer_overflow
lab_buffer_overflow_OBJECTS = \
"CMakeFiles/lab_buffer_overflow.dir/main.cpp.o"

# External object files for target lab_buffer_overflow
lab_buffer_overflow_EXTERNAL_OBJECTS =

lab_buffer_overflow: CMakeFiles/lab_buffer_overflow.dir/main.cpp.o
lab_buffer_overflow: CMakeFiles/lab_buffer_overflow.dir/build.make
lab_buffer_overflow: CMakeFiles/lab_buffer_overflow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab_buffer_overflow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab_buffer_overflow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab_buffer_overflow.dir/build: lab_buffer_overflow

.PHONY : CMakeFiles/lab_buffer_overflow.dir/build

CMakeFiles/lab_buffer_overflow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab_buffer_overflow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab_buffer_overflow.dir/clean

CMakeFiles/lab_buffer_overflow.dir/depend:
	cd /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug /Users/derekolson/DerekOlson/CS6014/lab_buffer_overflow/cmake-build-debug/CMakeFiles/lab_buffer_overflow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab_buffer_overflow.dir/depend

