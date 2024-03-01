# Engine Investigation

<img src="./media/engines.jpg"/>

For this portion of the assignment, you are going to review some source code to understand the structure of a game engine. 

**You will be modifying this README.md with your answeres (Search for TODO)**

## Horde3D Graphics Engine

Horde3D is a small and simple graphics engine. It was designed primarily to be integrated with other game engines and frameworks. Some features of the Horde3D engine are:

- It is a small graphics engine that supposedly has a relatively clean API.
- It is cross platform and uses the OpenGL API.
- It specializes in crowd simulation

### Your task
<img src="./media/horde3d.jpg" width=150px align="right"/>

Review the Horde3D reference manual here: http://horde3d.org/docs/manual.html You should read the manual in its entirety such that you can answer the following questions:

- Question: What might be the advantage of a handle-based system?
  - Answer: Much like pointers, handles can provide a method to obtain a reference to a shared resources. However, 
    handles provide more safety by adding additional layers of indirection—namely in that they must be accessed via 
    special functions, which can perform construction and validation on input. Once these handles are acquired, they 
    generally remain valid for the lifetime of the application (or until release.) 
- Question: What is one pro and one con of creating a C-based API with your engine?
  - Answer: C is highly portable, with support for many platforms (and, via native bindings, typically many other 
    languages.) However, C's portability is largely a direct result of its simplicity: C does not contain a number 
    of features considered common in many languages, nor does it provide extensive native functionality or data 
    structure. As such, providing a C-based API requires either writing your engine in C—generally a difficult 
    task—or converting from your native representation to C's interfaces and back again. The latter is common 
    practice—for example, most Vulkan drivers are implemented in C++ but provide a C API—but nonetheless requires 
    careful programming. Common boundary issues include handling return values, safe pointer handling, and exception 
    handling. 
- Question: What is a scene graph?
  - Answer: A scene graph is a graph (shocking), typically hierarchical, which describes the contents of a scene 
    (again, shocking.) This hierarchy also corresponds to the logical or spatial structure of the scene, and can be 
    used by various processes and algorithms that work across the scene. In Horde, this takes the form of a tree-based 
    XML document, where each element is a node in the graph. Notably, nodes can also describe geometric heirachies, 
    such as meshes, joints, and bones. 
- Question: What is a Pipeline in Horde3D? In your answer, discuss the purpose of having a 'pipeline XML document' in the context of an engine.
  - Answer: In Horde, a pipeline is a series of rendering steps (namely shaders). These stages can map to common types 
    of hardware shaders (vertex, geometry, tesselation, shader), and support various types of render targets. As 
    with scene graphs, Horde allows pipelines to be described entirely in XML; this allows the pipeline to be stored 
    in a unified document, with inputs, stages, and outputs. 

## GoDot Game Engine

The Godot game engine (https://godotengine.org/) is a free and open-source engine gaining lots of popularity in the 
past few years. Some features are:

- Cross platform game engine
- Free open source engine

Please read the following article and answer.

- Question: Read the following article (https://godotengine.org/article/why-isnt-godot-ecs-based-game-engine/) and answer in your own words -- how is the GoDot engine organized at a high-level? 

The Godot engine consists of many distinct components at different levels of abstraction, each of which 
may be organized differently. However, given the context of the aforementioned article, I'll focus on discussing 
how Godot's organization relates to its use of OOP principles in its core components.

Unlike many other game engines, including the one we've been building in this class, Godot does not make use of 
an entity-component-system (ECS). Instead, Godot relies on more traditional OOP, with core data and logic 
implemented in "nodes". Each element in a scene is a subclass of the `Node` class, with an extensive inheritance chain 
based on functionality. **Critically, this means that the scene graph is simply a hierarchy of nodes**; there's no 
distinct "scene" class that encapsulates a list of/tree of components. This is generally a much higher-level 
approach compared to an ECS.

Behind the scenes, nodes may interface with subsystems (such as physics, rendering, and audio), called "servers" that 
provide a node's underlying functionality. Servers are isolated, and may use ECSs internally to implement their 
functionality; however, these are not generally exposed to the average user. As the article explains: "nodes are just
interfaces to the actual data being processed inside servers, while in ECS the actual entities are what gets processed 
by the systems."

## Your Choice Engine/Framework

Pick one game engine that is listed here: https://gist.github.com/raysan5/909dc6cf33ed40223eb0dfe625c0de74

Answer the following to the best of your ability (There may be 1 or 2 that you cannot answer -- if you cannot answer too many questions, choose a different engine to receive full credit.):

- Question: Which engine did you choose?
  - Answer: Unreal Engine 5, since I'm currently learning it for another project.
- Question: Is the engine implemented primarily in C++
  - Answer: Yes.
- Question: Is there a scripting languages available with the engine?
  - Answer: Yes, in the form of Verse; however, it's pretty new, and it's not particularly prevalent outside of a few 
    high-level applications. Most functionality is instead (at least currently) implemented in either Blueprint, a 
    node-based visual editor, or directly in C++. 
- Question: Were there any commercial/indie games made in this engine?
  - Answer: Yes (but mostly in earlier versions); _Hello Neighbor_, _Abzu_, and _Rocket League_ are some of the 
    notable ones. 
- Question: What platforms does the engine support?
  - Answer: Most everything; Windows, macOS, Linux, Xbox, Playstation, Nintendo Wii U/Switch, iOS, Android.
- Question: Were there any Game Developer Conference or other interesting talks? (May need to search YouTube, try to find at least one presentation video or slideshow talking about the technical parts of the engine, code, or a game made with the engine and link it here.)
  - Answer: [This talk](https://www.youtube.com/watch?v=xLVJP-o0g28) on the making of _The Matrix Awakens_ demo has 
    some great insights into the newer features of Unreal Engine 5 specifically, namely massive photorealistic 
    environments.
- Question: What is the engines 'best' feature (i.e. why do people tend to use it? You may need to visit the website to get an idea.)
  - Answer: Probably the massive community and ongoing commitment from Epic Games? It's basically industry-default 
    at this point. It's also incredibly feature-rich and has pretty friendly licensing, especially for independent and small devs.
- Question: Is the code available?
  - Answer: Yes; the source code is accessible via their developer program, which is open-enrollment. It is not 
    permissively licensed.
- Question: What is one interesting thing you learned looking at the engine or the code, that you think you can implement in your codebase?
  - Answer: The intersection between novel Unreal features and "doable in my code" is pretty small. While not 
    entirely unique to Unreal, a basic content browser (with thumbnails!) and level selector would both be pretty 
    useful, and could be doable in a basic game engine.

## Deliverable

1. Modify this readme.md file with your answers.

## F.A.Q

- Q: How long do my answers need to be?
- A: Long enough that your answers are complete -- some can be 'yes/no' answers, but add details. Show your interest!
