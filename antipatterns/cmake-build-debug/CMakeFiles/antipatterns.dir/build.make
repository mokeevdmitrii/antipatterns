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

CMakeFiles/antipatterns.dir/States/State.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/States/State.cpp.o: ../States/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/antipatterns.dir/States/State.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/States/State.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/States/State.cpp

CMakeFiles/antipatterns.dir/States/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/States/State.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/States/State.cpp > CMakeFiles/antipatterns.dir/States/State.cpp.i

CMakeFiles/antipatterns.dir/States/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/States/State.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/States/State.cpp -o CMakeFiles/antipatterns.dir/States/State.cpp.s

CMakeFiles/antipatterns.dir/States/GameState.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/States/GameState.cpp.o: ../States/GameState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/antipatterns.dir/States/GameState.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/States/GameState.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/States/GameState.cpp

CMakeFiles/antipatterns.dir/States/GameState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/States/GameState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/States/GameState.cpp > CMakeFiles/antipatterns.dir/States/GameState.cpp.i

CMakeFiles/antipatterns.dir/States/GameState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/States/GameState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/States/GameState.cpp -o CMakeFiles/antipatterns.dir/States/GameState.cpp.s

CMakeFiles/antipatterns.dir/src/Creature.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/Creature.cpp.o: ../src/Creature.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/antipatterns.dir/src/Creature.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/Creature.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/Creature.cpp

CMakeFiles/antipatterns.dir/src/Creature.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/Creature.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/Creature.cpp > CMakeFiles/antipatterns.dir/src/Creature.cpp.i

CMakeFiles/antipatterns.dir/src/Creature.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/Creature.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/Creature.cpp -o CMakeFiles/antipatterns.dir/src/Creature.cpp.s

CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o: ../States/MainMenuState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/States/MainMenuState.cpp

CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/States/MainMenuState.cpp > CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.i

CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/States/MainMenuState.cpp -o CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.s

CMakeFiles/antipatterns.dir/Resources/Button.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Resources/Button.cpp.o: ../Resources/Button.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/antipatterns.dir/Resources/Button.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Resources/Button.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Button.cpp

CMakeFiles/antipatterns.dir/Resources/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Resources/Button.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Button.cpp > CMakeFiles/antipatterns.dir/Resources/Button.cpp.i

CMakeFiles/antipatterns.dir/Resources/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Resources/Button.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Button.cpp -o CMakeFiles/antipatterns.dir/Resources/Button.cpp.s

CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o: ../Resources/ButtonManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/ButtonManager.cpp

CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/ButtonManager.cpp > CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.i

CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/ButtonManager.cpp -o CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.s

CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o: ../Resources/GraphicsSettings.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/GraphicsSettings.cpp

CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/GraphicsSettings.cpp > CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.i

CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/GraphicsSettings.cpp -o CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.s

CMakeFiles/antipatterns.dir/src/Player.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/Player.cpp.o: ../src/Player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/antipatterns.dir/src/Player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/Player.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/Player.cpp

CMakeFiles/antipatterns.dir/src/Player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/Player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/Player.cpp > CMakeFiles/antipatterns.dir/src/Player.cpp.i

CMakeFiles/antipatterns.dir/src/Player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/Player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/Player.cpp -o CMakeFiles/antipatterns.dir/src/Player.cpp.s

CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o: ../Components/PhysicsComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Components/PhysicsComponent.cpp

CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Components/PhysicsComponent.cpp > CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.i

CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Components/PhysicsComponent.cpp -o CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.s

CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o: ../Components/GraphicsComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Components/GraphicsComponent.cpp

CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Components/GraphicsComponent.cpp > CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.i

CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Components/GraphicsComponent.cpp -o CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.s

CMakeFiles/antipatterns.dir/src/Enemy.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/Enemy.cpp.o: ../src/Enemy.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/antipatterns.dir/src/Enemy.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/Enemy.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/Enemy.cpp

CMakeFiles/antipatterns.dir/src/Enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/Enemy.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/Enemy.cpp > CMakeFiles/antipatterns.dir/src/Enemy.cpp.i

CMakeFiles/antipatterns.dir/src/Enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/Enemy.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/Enemy.cpp -o CMakeFiles/antipatterns.dir/src/Enemy.cpp.s

CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o: ../Components/HitboxComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Components/HitboxComponent.cpp

CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Components/HitboxComponent.cpp > CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.i

CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Components/HitboxComponent.cpp -o CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.s

CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o: ../Resources/PauseMenu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/PauseMenu.cpp

CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/PauseMenu.cpp > CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.i

CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/PauseMenu.cpp -o CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.s

CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o: ../Components/AttributeComponent.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Components/AttributeComponent.cpp

CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Components/AttributeComponent.cpp > CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.i

CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Components/AttributeComponent.cpp -o CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.s

CMakeFiles/antipatterns.dir/src/TileMap.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/TileMap.cpp.o: ../src/TileMap.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/antipatterns.dir/src/TileMap.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/TileMap.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/TileMap.cpp

CMakeFiles/antipatterns.dir/src/TileMap.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/TileMap.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/TileMap.cpp > CMakeFiles/antipatterns.dir/src/TileMap.cpp.i

CMakeFiles/antipatterns.dir/src/TileMap.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/TileMap.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/TileMap.cpp -o CMakeFiles/antipatterns.dir/src/TileMap.cpp.s

CMakeFiles/antipatterns.dir/src/Tile.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/Tile.cpp.o: ../src/Tile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building CXX object CMakeFiles/antipatterns.dir/src/Tile.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/Tile.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/Tile.cpp

CMakeFiles/antipatterns.dir/src/Tile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/Tile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/Tile.cpp > CMakeFiles/antipatterns.dir/src/Tile.cpp.i

CMakeFiles/antipatterns.dir/src/Tile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/Tile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/Tile.cpp -o CMakeFiles/antipatterns.dir/src/Tile.cpp.s

CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o: ../src/EnemySystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Building CXX object CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySystem.cpp

CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySystem.cpp > CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.i

CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySystem.cpp -o CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.s

CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o: ../src/EnemySpawner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_20) "Building CXX object CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySpawner.cpp

CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySpawner.cpp > CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.i

CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/src/EnemySpawner.cpp -o CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.s

CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o: ../Enemies/Rat.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_21) "Building CXX object CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Enemies/Rat.cpp

CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Enemies/Rat.cpp > CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.i

CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Enemies/Rat.cpp -o CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.s

CMakeFiles/antipatterns.dir/Resources/Json.cpp.o: CMakeFiles/antipatterns.dir/flags.make
CMakeFiles/antipatterns.dir/Resources/Json.cpp.o: ../Resources/Json.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_22) "Building CXX object CMakeFiles/antipatterns.dir/Resources/Json.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/antipatterns.dir/Resources/Json.cpp.o -c /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Json.cpp

CMakeFiles/antipatterns.dir/Resources/Json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/antipatterns.dir/Resources/Json.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Json.cpp > CMakeFiles/antipatterns.dir/Resources/Json.cpp.i

CMakeFiles/antipatterns.dir/Resources/Json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/antipatterns.dir/Resources/Json.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmitry/MIPT/PATTERNS/antipatterns/Resources/Json.cpp -o CMakeFiles/antipatterns.dir/Resources/Json.cpp.s

# Object files for target antipatterns
antipatterns_OBJECTS = \
"CMakeFiles/antipatterns.dir/src/main.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Game.cpp.o" \
"CMakeFiles/antipatterns.dir/States/State.cpp.o" \
"CMakeFiles/antipatterns.dir/States/GameState.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Creature.cpp.o" \
"CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o" \
"CMakeFiles/antipatterns.dir/Resources/Button.cpp.o" \
"CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o" \
"CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Player.cpp.o" \
"CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o" \
"CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Enemy.cpp.o" \
"CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o" \
"CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o" \
"CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o" \
"CMakeFiles/antipatterns.dir/src/TileMap.cpp.o" \
"CMakeFiles/antipatterns.dir/src/Tile.cpp.o" \
"CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o" \
"CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o" \
"CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o" \
"CMakeFiles/antipatterns.dir/Resources/Json.cpp.o"

# External object files for target antipatterns
antipatterns_EXTERNAL_OBJECTS =

antipatterns: CMakeFiles/antipatterns.dir/src/main.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Game.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/States/State.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/States/GameState.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Creature.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/States/MainMenuState.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Resources/Button.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Resources/ButtonManager.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Resources/GraphicsSettings.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Player.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Components/PhysicsComponent.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Components/GraphicsComponent.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Enemy.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Components/HitboxComponent.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Resources/PauseMenu.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Components/AttributeComponent.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/TileMap.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/Tile.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/EnemySystem.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/src/EnemySpawner.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Enemies/Rat.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/Resources/Json.cpp.o
antipatterns: CMakeFiles/antipatterns.dir/build.make
antipatterns: ../SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-window.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-audio.so.2.5.1
antipatterns: ../SFML-2.5.1/lib/libsfml-system.so.2.5.1
antipatterns: CMakeFiles/antipatterns.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmitry/MIPT/PATTERNS/antipatterns/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_23) "Linking CXX executable antipatterns"
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

