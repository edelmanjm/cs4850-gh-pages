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

add_executable(assignment5-part1
        src/main.cpp
        src/Application.cpp
        src/ResourceManager.cpp
        src/components/Component.cpp
        src/components/Collision2DComponent.cpp
        src/components/InputComponent.cpp
        src/components/TextureComponent.cpp
        src/components/TransformComponent.cpp
        src/entities/EnemyEntity.cpp
        src/entities/GameEntity.cpp
        src/entities/PlayerGameEntity.cpp
        src/entities/ProjectileEntity.cpp)