# Abstraction: GameObject and Components

<img align="right" width="300px" src="./media/gameobject.jpg">

> "Allow a single entity to span multiple domains without coupling the domains to each other." Component Programming Pattern  - Robert Nystrom

## Introduction

We have previously discussed the [component game programming pattern](https://gameprogrammingpatterns.com/component.html)  to 'decouple' classes and make our games more maintainable (**Please read the chapter** it's very insightful!). 

Typically when we write Object-Oriented Code it can be tempting to create large inheritence structures like what is shown in the figure below. This can quickly become difficult software to maintain and to optimize for performance (Note in the diagram below 'EvilTrees' becomes ambiguous in where it belongs, and if we inherit from two differnt paths, we get the 'deadly diamond inheritance' problem).

<img width="300px" src="./media/inheritence.png">

>Diagram from: https://www.gamedev.net/tutorials/_/technical/game-programming/understanding-component-entity-systems-r3013/ (The one aspect I do like is the separation of 'static' and 'dynamic' however--that may be useful for optimization purposes of which components change or do not change)

So typically we favor using composition within our game objects, where game objects use a container data structure(e.g. a std::vector<Component>) to hold different components which in effect create a new type of game object based on the combinations of components held and their associated data. Using composition is also much more friendly in regards to *Data-Oriented Design*.

<img width="300px" src="./media/composition.png">

>Diagram from: https://www.gamedev.net/tutorials/_/technical/game-programming/understanding-component-entity-systems-r3013/ (This is a much more 'flat' hierarchy and allows us even more flexibility in how we create our entities. Note: We are likely to have a 'init','update','render' or associated member functions with each component.)

## Task 1 - GameObject (a.k.a GameEntity or GameActor) 

The GameObject class (sometimes also known as the GameEntity or GameActor class) is one of the most common custom data types for abstracting objects in 2D and 3D games. This class is typically what you will be building your game from, alongside a more general 'component' class.

### Your Task

Your task will be to follow the 'Component' section of the 'courses.mshah.io' course and implement a 'component pattern' within your current game. This may involve a heavy refactor of the code, or otherwise rebuilding the game from scratch -- the choice is yours.

1. **In practice, I don't ** how you do this, so long as you have a GameObject (or GameEntity) class with a container (e.g. std::vector) of components that can be added to achieve the functionality. 
2. You can modify the code however you like.
3. You should also think about how to retrieve components with a 'GetComponent' or 'GetComponents' function as well.

## Helpful Resources

Some additional resources to help you through this assignment

- [https://gameprogrammingpatterns.com/component.html](https://gameprogrammingpatterns.com/component.html)
  - Essential Reading -- The component programming pattern 
- [Creating the GameObject Class](https://www.youtube.com/watch?v=jzasDqPmtPI&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=5) 
  - Looks like a helpful C++/SDL2 tutorial on building Game objects.

## Deliverables

1. Add your project to this repository. It should have effectively the same functionality as before, with the exception that you have a container (e.g. std::vector, std::list, etc.) 'component' within the GameEntity class. 

# F.A.Q. (Instructor Anticipated Questions)

* Q: Do I have to incorporate my previous resource manager?
    * A: Yes -- we want to keep the previous designs that we have made.
* Q: `std::vector<Component> mComponents` is not compiling for some reason
    * A: Consider that if 'Component' is a base class, that you need to make `std::vector<Component*> mComponents` or `std::vector<std::shared_ptr<Component>>`.
        *  We need pointers in order for runtime polymorphism (i.e. dynamic dispatch) to work and call the right components from within our component vector.
* Q: Are shared_ptr's bad?
    * A: In practice, we probably would develop a 'handle' based system and have a component manager, similar to our resource manager. Shared_ptr's introduce a level of indirection, and they also have an internal atomic lock that can make them tricky to manage. That said, they make ownership and management of heap allocated data easy (e.g. if a vector examples on push_back, it's fairly trivial for the copy of shared_ptr's to work and increment/decrement the use_count without any bugs).

## Going Further

What is that, you finished Early? Did you enjoy this lab? Here are some (optional) ways to further this assignment.

- Build a component-based system that uses handles and a separate component manager (ECS)
 
## Found a bug?

If you found a mistake (big or small, including spelling mistakes) in this lab, kindly send me an e-mail. It is not seen as nitpicky, but appreciated! (Or rather, future generations of students will appreciate it!)

- Fun fact: The famous computer scientist Donald Knuth would pay folks one $2.56 for errors in his published works. [[source](https://en.wikipedia.org/wiki/Knuth_reward_check)]
- Unfortunately, there is no monetary reward in this course :)
