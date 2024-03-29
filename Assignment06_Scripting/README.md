# Your Information

**Note**: This project is built using CMake, using CPM to manage dependencies. I personally use CLion, and if you
want, you can simply open this repo in CLion and compile the project there. If, however, you prefer to compile from
the command line, you're welcome to do so. I personally use ninja + clang for my toolchain, but you're welcome to
use whatever you want (make, gcc, something else). The following commands are what I use; they should be run from
the root of the repository.

`cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S Assignment06_Scripting/part0/EngineLibrary -B
Assignment06_Scripting/part0/EngineLibrary/cmake-build-debug`

`cmake --build Assignment06_Scripting/part0/EngineLibrary/cmake-build-debug --target rose -j 14`

This will build a library called `rose` in the `cmake-build-debug` folder.

To run the Pong game, run `python3.12 pong.py` from the `EngineLibrary` folder. `pong.py` will automatically append 
`cmake-build-debug` to the path; if you're built library there, you shouldn't need to manually copy the rose library.
If you choose to build the library somewhere else, you should copy it to the `EngineLibrary` folder before running 
`pong.py`

* Name: Jonathan Edelman
* How many hours did it take you to complete this assignment? Approximately 20 hours, based on the git log.
* Did you collaborate or share ideas with any other students/TAs/Professors? No.
* Did you use any external resources? 
  * I used Stack Overflow to debug my CMake configuration, particularly related to finding and linking the correct 
    Python version. No specific resources provided a complete solution and are worth noting.
  * I utilized the SDL and pybind11 docs extensively for help using those libraries.
  * The font is courtesy of [Matt Lagg](https://www.mattlag.com/bitfonts/)
  * Font rendering utilizes a fork of [SDL_FontCache](https://github.com/grimfang4/SDL_FontCache) for convenience.
* (Optional) What was the most interesting part of the assignment? How would you improve this assignment?

# Assignment

This assignment consists of [part0](./part0)

# Rubric


<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>Part 0 - 100% (Core)</td>
      <td align="left">Did you complete pong game by connecting the sample engine to pybind11?</td>
    </tr>
  </tbody>
</table>


* Core is the material everyone can get through. I expect everyone to complete this. Coming to class, listening to lectures, and reviewing materials should be sufficient.
* Intermediate is a little more difficult. Very likely you will have to utilize office hours, piazza, etc.
* Advanced is more challenging. You will have to spend more time and very likely use outside materials. I do not expect everyone to complete the advanced section.

