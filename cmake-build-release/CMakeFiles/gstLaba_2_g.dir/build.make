# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /snap/clion/61/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/61/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leon/CLionProjects/gstLaba_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leon/CLionProjects/gstLaba_2/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/gstLaba_2_g.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gstLaba_2_g.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gstLaba_2_g.dir/flags.make

CMakeFiles/gstLaba_2_g.dir/generator.c.o: CMakeFiles/gstLaba_2_g.dir/flags.make
CMakeFiles/gstLaba_2_g.dir/generator.c.o: ../generator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leon/CLionProjects/gstLaba_2/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gstLaba_2_g.dir/generator.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gstLaba_2_g.dir/generator.c.o   -c /home/leon/CLionProjects/gstLaba_2/generator.c

CMakeFiles/gstLaba_2_g.dir/generator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gstLaba_2_g.dir/generator.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/leon/CLionProjects/gstLaba_2/generator.c > CMakeFiles/gstLaba_2_g.dir/generator.c.i

CMakeFiles/gstLaba_2_g.dir/generator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gstLaba_2_g.dir/generator.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/leon/CLionProjects/gstLaba_2/generator.c -o CMakeFiles/gstLaba_2_g.dir/generator.c.s

# Object files for target gstLaba_2_g
gstLaba_2_g_OBJECTS = \
"CMakeFiles/gstLaba_2_g.dir/generator.c.o"

# External object files for target gstLaba_2_g
gstLaba_2_g_EXTERNAL_OBJECTS =

gstLaba_2_g: CMakeFiles/gstLaba_2_g.dir/generator.c.o
gstLaba_2_g: CMakeFiles/gstLaba_2_g.dir/build.make
gstLaba_2_g: CMakeFiles/gstLaba_2_g.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leon/CLionProjects/gstLaba_2/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gstLaba_2_g"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gstLaba_2_g.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gstLaba_2_g.dir/build: gstLaba_2_g

.PHONY : CMakeFiles/gstLaba_2_g.dir/build

CMakeFiles/gstLaba_2_g.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gstLaba_2_g.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gstLaba_2_g.dir/clean

CMakeFiles/gstLaba_2_g.dir/depend:
	cd /home/leon/CLionProjects/gstLaba_2/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leon/CLionProjects/gstLaba_2 /home/leon/CLionProjects/gstLaba_2 /home/leon/CLionProjects/gstLaba_2/cmake-build-release /home/leon/CLionProjects/gstLaba_2/cmake-build-release /home/leon/CLionProjects/gstLaba_2/cmake-build-release/CMakeFiles/gstLaba_2_g.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gstLaba_2_g.dir/depend

