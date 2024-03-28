cmake_minimum_required(VERSION 3.27)
project(cs4850)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cmake)

find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

CPMAddPackage(
        NAME SDL
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG main)

CPMAddPackage(
        NAME pybind11
        GITHUB_REPOSITORY pybind/pybind11
        GIT_TAG smart_holder
)

#CPMAddPackage(
#        NAME units
#        VERSION 2.3.3
#        URL https://github.com/nholthaus/units/archive/refs/tags/v2.3.3.tar.gz
#)

#CPMAddPackage(
#        NAME Boost
#        GITHUB_REPOSITORY boostorg/boost
#        GIT_TAG boost-1.84.0
#)

include_directories(include)

link_libraries(SDL3::SDL3
#        units
#        Boost::algorithm
#        Boost::geometry
)

add_library(rose-lib
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
        src/entities/ProjectileEntity.cpp
        src/scenes/SpaceInvaders.cpp
        src/scenes/Scene.cpp
        src/scenes/PythonScene.cpp
        src/Renderer.cpp)

pybind11_add_module(rose
        src/Bindings.cpp)
target_link_libraries(rose PRIVATE rose-lib)

add_executable(space-invaders
        src/main.cpp)
target_link_libraries(space-invaders PRIVATE rose-lib)