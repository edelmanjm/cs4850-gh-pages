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
        VERSION v2.11.1
        URL https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz
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

pybind11_add_module(cs4850 src/bindings.cpp)

add_executable(assignment6-part0
        src/main.cpp
        src/Application.cpp
        src/ResourceManager.cpp
        src/Scene.cpp
        src/components/Component.cpp
        src/components/Collision2DComponent.cpp
        src/components/InputComponent.cpp
        src/components/TextureComponent.cpp
        src/components/TransformComponent.cpp
        src/entities/EnemyEntity.cpp
        src/entities/GameEntity.cpp
        src/entities/PlayerGameEntity.cpp
        src/entities/ProjectileEntity.cpp)