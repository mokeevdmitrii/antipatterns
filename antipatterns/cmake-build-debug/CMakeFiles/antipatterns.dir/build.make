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
CMAKE_COMMAND = /opt/clion-2019.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmitry/MIPT/PATTERNS/antipatterns

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/antipatterns.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/antipatterns.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/antipatterns.dir/flags.make

CMakeFiles/antipatterns.dir/src/main.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/antipatterns.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/main.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/main.cpp

CMakeFiles/antipatterns.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/main.cpp > CMakeFiles/antipatterns.dir/src/main.cpp.i

CMakeFiles/antipatterns.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/main.cpp -o CMakeFiles/antipatterns.dir/src/main.cpp.s

CMakeFiles/antipatterns.dir/src/Game.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/Game.cpp.o: ../src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/antipatterns.dir/src/Game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/Game.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/Game.cpp

CMakeFiles/antipatterns.dir/src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/Game.cpp > CMakeFiles/antipatterns.dir/src/Game.cpp.i

CMakeFiles/antipatterns.dir/src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/Game.cpp -o CMakeFiles/antipatterns.dir/src/Game.cpp.s

CMakeFiles/antipatterns.dir/Clock.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Clock.cpp.o: ../Clock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/antipatterns.dir/Clock.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Clock.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Clock.cpp

CMakeFiles/antipatterns.dir/Clock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Clock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Clock.cpp > CMakeFiles/antipatterns.dir/Clock.cpp.i

CMakeFiles/antipatterns.dir/Clock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Clock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Clock.cpp -o CMakeFiles/antipatterns.dir/Clock.cpp.s

# Object files for target antipatterns
antipatterns_OBJECTS = \
"CMakeFiles/antipatterns.dir/src/main.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Game.cpp.o" \
"CMakeFiles/antipatterns.dir/Clock.cpp.o"

# External object files for target antipatterns
antipatterns_EXTERNAL_OBJECTS =

antipatterns: CMakeFiles/antipatterns.dir/src/main.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Game.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Clock.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/build.make
antipatterns: ../SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-window.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-audio.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-system.so.2.5.1
antipatterns: CMakeFiles/antipatterns.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable antipatterns"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/antipatterns.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/antipatterns.dir/build: antipatterns

.PHONY : CMakeFiles/antipatterns.dir/build

CMakeFiles/antipatterns.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/antipatterns.dir/cmake_clean.cmake
.PHONY : CMakeFiles/antipatterns.dir/clean

CMakeFiles/antipatterns.dir/depend:
	cd /home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmitry/MIPT/PATTERNS/antipatterns /home/dmitry/MIPT/PATTERNS/antipatterns /home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug /home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug /home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles/antipatterns.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/antipatterns.dir/depend

