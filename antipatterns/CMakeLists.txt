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

add_executable(antipatterns src/main.cpp src/Game.cpp src/Game.h src/Clock.cpp src/Clock.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h src/GameObject.cpp src/GameObject.h)
target_link_libraries (antipatterns sfml-graphics sfml-window sfml-audio sfml-system)
