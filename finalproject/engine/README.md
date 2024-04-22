## Add any additional notes here

## Game/Engine Publicity

**Project Website**: *please edit the project website with a link here* (See part 3)

## Compilation Instructions

This project is built using CMake, using CPM to manage dependencies. I personally use CLion, and if you
want, you can simply open this repo in CLion and compile the project there. If, however, you prefer to compile from
the command line, you're welcome to do so. I personally use ninja + clang for my toolchain, but you're welcome to
use whatever you want (make, gcc, something else). The following commands are what I use; they should be run from
the root of the repository.

`cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S finalproject/engine -B finalproject/engine/cmake-build-debug`

`cmake --build finalproject/engine/cmake-build-debug --target rose -j 14`

This will build a library called `rose` in the `cmake-build-debug` folder.

To run the Pong game, run `python3.12 asteroids.py` from the `finalproject/engine/asteroids` folder. `asteroids.py` will 
automatically append `cmake-build-debug` to the path; if you're built library there, you shouldn't need to manually 
copy the rose library. If you choose to build the library somewhere else, you should copy it to the 
`finalproject/engine/release` folder before running `python3.12 asteroids.py`. A prebuilt binary is provided for 
macOS (Darwin/x86).

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. These are the required files you should have 

### ./engine Directory Organization

- docs 
    - Source Code Documentation
- assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)

**Additional Notes:** 

1. src and include should only contain ".cpp" or ".hpp" files. Why? It makes it very fast to do a backup of your game project as one example. Secondly, binary files that are generated often clutter up directories. I should not see any binaries in your repository, you may use a '.gitignore' file to help prevent this automatically. 
