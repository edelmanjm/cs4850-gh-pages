# Your Information

**Note**: This project is built using CMake, using CPM to manage dependencies. I personally use CLion, and if you 
want, you can simply open this repo in CLion and compile the project there. If, however, you prefer to compile from 
the command line, you're welcome to do so. I personally use ninja + clang for my toolchain, but you're welcome to 
use whatever you want (make, gcc, something else). The following commands are what I use; they should be run from 
the root of the repository.

`cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S Assignment05_GameEngineStudy/part1 -B 
Assignment05_GameEngineStudy/part1/cmake-build-debug`

`cmake --build Assignment05_GameEngineStudy/part1/cmake-build-debug --target assignment5-part1 -j 14`

Once built, the executables can be run from the `cmake-build-debug` directory.

* Name: 
* How many hours did it take you to complete this assignment? 
* Did you collaborate or share ideas with any other students/TAs/Professors? 
* Did you use any external resources? 
  * (tbd if any)
  * (tbd if any)
  * (tbd if any)
* (Optional) What was the most interesting part of the assignment? How would you improve this assignment?

# Assignment

This assignment consists of [part0](./part0), [part1](./part1) 

# Rubric


<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>Part 0 - 50% (Core)</td>
      <td align="left">Did you complete the readme.md with your answers? Did you answer them completely and in your own words?</td>
    </tr>
  </tbody>
</table>

<table>
  <tbody>
    <tr>
      <th>Points</th>
      <th align="center">Description</th>
    </tr>
    <tr>
      <td>Part 1 - 50% (Core)</td>
      <td align="left">Did you update your game with the specified requirements? Did you commit your source code of a working build of the game?</td>
    </tr>
  </tbody>
</table>

* Core is the material everyone can get through. I expect everyone to complete this. Coming to class, listening to lectures, and reviewing materials should be sufficient.
* Intermediate is a little more difficult. Very likely you will have to utilize office hours, piazza, etc.
* Advanced is more challenging. You will have to spend more time and very likely use outside materials. I do not expect everyone to complete the advanced section.

