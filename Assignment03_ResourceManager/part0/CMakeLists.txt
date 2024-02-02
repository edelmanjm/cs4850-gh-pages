cmake_minimum_required(VERSION 3.27)
project(cs4850)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cmake)

CPMAddPackage(
        NAME SDL
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG main)

include_directories(include)

link_libraries(SDL3::SDL3)

add_executable(assignment3-part0
        include/Application.h
        src/main.cpp
        src/Sprite.cpp
        src/entities/EnemyEntity.cpp
        src/entities/GameEntity.cpp
        src/entities/PlayerGameEntity.cpp
        src/entities/ProjectileEntity.cpp
        src/Application.cpp)