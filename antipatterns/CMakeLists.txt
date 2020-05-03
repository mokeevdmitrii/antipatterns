cmake_minimum_required(VERSION 3.10)
project(antipatterns)

set(SFML_INCLUDE_DIR SFML-2.5.1/include)
set(SFML_LIB_DIR SFML-2.5.1/lib)
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)

link_directories(SFML_LIB_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif ()

set(CMAKE_CXX_STANDARD 17)

add_executable(antipatterns src/main.cpp src/Game.cpp States/State.cpp States/GameState.cpp src/Creature.cpp
        States/MainMenuState.cpp Resources/Button.cpp Resources/ButtonManager.cpp Resources/GraphicsSettings.cpp
        src/Player.cpp Components/PhysicsComponent.cpp Components/GraphicsComponent.cpp src/Enemy.cpp
        Components/HitboxComponent.cpp Resources/PauseMenu.cpp Components/AttributeComponent.cpp src/TileMap.cpp
        src/Tile.cpp src/EnemySystem.cpp Enemies/EnemySpawner.cpp Enemies/Rat.cpp Resources/Json.cpp
        Components/Parameters/Attribute.cpp Components/Parameters/Attribute.h Components/Parameters/Effect.cpp
        Components/Parameters/Effect.h Components/SkillComponent.cpp Components/SkillComponent.h Components/Parameters/Skill.cpp Components/Parameters/Skill.h Components/Parameters/Timer.cpp Components/Parameters/Timer.h Components/Parameters/AttributeFormulas.cpp Components/Parameters/AttributeFormulas.h Resources/Constants.cpp Resources/Constants.h src/Room.cpp src/Room.h src/Exit.cpp src/Exit.h src/EnemyTypes.h Resources/Utility.cpp Resources/Utility.h Resources/Filenames.h src/UniqueDatabase.cpp src/UniqueDatabase.h Enemies/Enemies.h src/Input/InputHandler.cpp src/Input/InputHandler.h src/Input/Command.cpp src/Input/Command.h src/EnemyState.cpp src/EnemyState.h)
target_link_libraries(antipatterns sfml-graphics sfml-window sfml-audio sfml-system)
