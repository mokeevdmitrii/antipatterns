cmake_minimum_required(VERSION 3.15)
project(antipatterns)

set(SFML_INCLUDE_DIR SFML-2.5.1/include)
set(SFML_LIB_DIR SFML-2.5.1/lib)
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)

link_directories(SFML_LIB_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

set(CMAKE_CXX_STANDARD 17)

add_executable(antipatterns src/main.cpp src/Game.cpp src/Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h src/Creature.cpp src/Creature.h States/MainMenuState.cpp States/MainMenuState.h Resources/Button.cpp Resources/Button.h Resources/ButtonManager.cpp Resources/ButtonManager.h Resources/GraphicsSettings.cpp Resources/GraphicsSettings.h src/Player.cpp src/Player.h Components/PhysicsComponent.cpp Components/PhysicsComponent.h Components/GraphicsComponent.cpp Components/GraphicsComponent.h src/Enemy.cpp src/Enemy.h Components/HitboxComponent.cpp Components/HitboxComponent.h Resources/PauseMenu.cpp Resources/PauseMenu.h Components/AttributeComponent.cpp Components/AttributeComponent.h src/TileMap.cpp src/TileMap.h src/Tile.cpp src/Tile.h src/EnemySystem.cpp src/EnemySystem.h src/EnemySpawner.cpp src/EnemySpawner.h Enemies/Rat.cpp Enemies/Rat.h Resources/Json.cpp Resources/Json.h)
target_link_libraries (antipatterns sfml-graphics sfml-window sfml-audio sfml-system)
