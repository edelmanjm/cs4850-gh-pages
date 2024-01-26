# Part 0 - Resource Manager 

> A resource manager for efficiently managing resources

# Description

For this portion of the assignment you are going to do a 'follow along exercise' to implement a resource manager to your previous game project. 

* You will complete the following chapter lessons on the courses.mshah.io series you have been following:
	* Polishing our Code (which includes: Code Organization, and Adding a Resource Manager)
	* You should submit your code (e.g. /src /include and any assets) to this folder after completing your owrk.
* Note: If you need instructions on how to get the course videos, please refer to the previous assignment.

## Task 1 - Resource Manager

Your goal for this assignment is to implement a `ResourceManager`. The resource managers job is to manage all of the assets that you load into your game engine, whether they are sound files, image files, 3D files, or configuration files. For the purpose of this assignment, you need to handle at least one resource (e.g. SDL_Texture).

### Resource Manager Structure

The suggested implementation is to use the [Singleton](https://en.wikipedia.org/wiki/Singleton_pattern) design pattern for your resource manager. This will make it fairly easy to create a single access point to access a shared SDL_Texture resource for example. You are welcome to refactor your resource manager using different patterns if you choose. 

Provided below is an example of a resource manager that you can use as a template.

```cpp
// #include <....> // Decide what data structures you need

// This is an example Resource Manager
// You can use this as a template for implementing your own.

class ResourceManager{
  private:
    ResourceManager();  // Private Singleton
    ResourceManager(ResourceManger const&); // Avoid copy constructor
    void operator=(ResourceManager const&); // Don't allow assignment.
    
    // ... // perhaps other private members
    // Consider the data type that you may need to store
    // your resources
    
  public:
  
  static ResourceManager &GetInstance();
  
  void LoadResource(std::string image_filename);
  
  SDL_Surface* GetResource(std::string key);
  
  // 'equivalent' to our constructor
  int StartUp();
  
  // 'equivalent' to our destructor
  int ShutDown();
  
  // ... Perhaps other public functions?
  // *Hint you need at least one other one for the datatype you are supporting*
}:
```

* Note: It is strongly recommended you read the [Singleton Chapter of Game Programming Patterns](https://gameprogrammingpatterns.com/singleton.html) textbook to understand the implementation and the trade offs of this design pattern.
* Provided is a supplemental video on Singleton Classes: [Design Patterns - Singleton Pattern | Explanation and Implementation in C++](https://www.youtube.com/watch?v=eLAvry56vLU&list=PLvv0ScY6vfd9wBflF0f6ynlDQuaeKYzyc&index=3)

## Helpful Resources for the Resource Manager

Some additional resources to help you through this assignment

1. My Video on the Singleton Pattern
	- [Design Patterns - Singleton Pattern | Explanation and Implementation in C++](https://youtu.be/eLAvry56vLU)
2. My series on C++ Programming
	- [The C++ Programming Language](https://www.youtube.com/playlist?list=PLvv0ScY6vfd8j-tlhYVPYgiIyXduu6m-L)
	- Useful C++ Data Structure(s) for this assignment.
   		- [STL std::unordered_map (C++11) | Modern Cpp Series](https://www.youtube.com/watch?v=pvVrNwZzCgk)
  		- [STL std::map | Modern Cpp Series](https://www.youtube.com/watch?v=5cGp0vx5u9Q&list=PLvv0ScY6vfd8j-tlhYVPYgiIyXduu6m-L&index=126&t=18s)
		- [A stack overflow discussion on map vs unordered map](https://stackoverflow.com/questions/2196995/is-there-any-advantage-of-using-map-over-unordered-map-in-case-of-trivial-keys)
3. Resources on Resource Managers
	- [Tutorial 15: ResourceManager, TextureCache!](https://www.youtube.com/watch?v=HBpmfrQINlo)
	- [A Resource Manager for Game Assets](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/a-resource-manager-for-game-assets-r3807/)
	- [Adding a Resource Management Class](http://eangogamedevelopment.blogspot.com/2017/01/part-21-completing-game-menu.html)




## Deliverables

1. Please upload the source code of your game
	- The expectation is that you will have a resource manager implemented for at the least handling textures.
  	- Note: It is advised to leave some SDL_Log messages to indicate that a resource is loaded only once -- this will also help you verify your resource manager is working.
   		- Later on, a 'logger class' to tell you what is going on in your game may also be advisable. 

# F.A.Q. (Instructor Anticipated Questions)

* Question: - How should I follow along the videos?
    - Type as I type, experiment, try things out, and experiment.
    - Just watching the videos on 2X will not be enough to absorb material, it's important to perform *active learning* by trying the examples.
    	- In most cases for the vidoes, I will leave my mistakes in so you can also see how I fix things, think, debug, etc.
    - **IMPORTANT**: I have provided source code for most of the videos as they progress. Take the time now to follow along the videos and experiment -- if you simply copy & paste, it may become hard later on to understand how to create your own original works.
* Q: Should we return textures, should we also return surfaces?
  * A: We probably will want to consider a resource manager that also handles surfaces, and can reuse those surfaces for texture generation. The reason is that a surface could have its pixels modified at run-time (e.g. replacing all red pixels to green to indicate a different 'character/team'). 
* Q: Should we create an interface from our resource manager (i.e. some base class we can derive from)
  * A: It is nice to but not necessary. For the purpose of this assignment, if you can create one resource manager, I'll assume folks could do that for multiple types of resources. In the most organized way, we'd have an interface that we'd code to:
	- ```cpp
		interface Manager{
			GetResource(type)
			LoadResource(type)
		};

		class SurfaceManager : implements Manager{
	
		};
		```
	- ^ Something like the above scenario
	- One thing to keep in mind if you choose to add a TextureManager is how you want to 'key' into the texture manager. Some folks are using the SDL_Surface filename which was loaded which I think is fine (i.e. having a map/unordered_map of textures). The TextureManager may have to call the SDL_SurfaceManager to load a surface if it otherwise does not exist. There are also other 'handle -based' systems that may be useful.


## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Try digging a bit more into smart pointers. I would probably recommend the shared_ptr for your resource manager, but you could build your own reference counted pointer if you choose.
	- While shared_ptr has some performance issues if you are creating lots of objects, it is a fine enough tool for the types of games we will be building..
- Consider making a 'global resource manager' type of class.
	- This global resource manager can be a singleton, and then contain individual instances of various resource managers that your game would actually use.
		- This may be a cleaner design, in that we only then would have one singleton in our game engine. The trade-off is that a global resource managaer composed of several other resource maangers starts to have lots of indirection (though the use of pointers) that may impact performance. We thus need to carefully consider the performance needs of our game versus our comfort level in some cases as developers.

## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
