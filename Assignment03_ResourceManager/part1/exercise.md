# Exercise.md (Edit sections of this file)

Read [Horde3D Usage Guide](http://www.horde3d.org/docs/html/_usageguide.html)'s ([web archived link](https://web.archive.org/web/20240118064147/http://www.horde3d.org/docs/html/_usageguide.html)) section on Resource Management (4 paragraphs).

1. What are some pros and cons to having a single resource manager for all of your resources (i.e. game assets)?

**Pros**:
- High reusability. Anything managed by the resource manager (textures, shaders, models, etc.) can be referenced 
  multiple times without having to be reloaded. 
- Well-defined and implemented loading. Optimizations that are applied to the resource manager (e.g. deferred 
  loading or resource streaming) apply to all resources that it manages.
- Consistency. It's easier to maintain common conventions and structures when using a resource manager. 

**Cons**:
- Single point of failure. Any issues with the resource manager can cripple the entire program. 
- Scalability/lack of parallelization. If poorly implemented, the resource manager may not be able to parallelize 
  efficiently due interdependencies within the resource manager. This is a particularly important issue when 
  multithreading and attempting to share state; trashing can also become an issue.
- Limited flexibility. The single resource manager pattern may not always fit the needs of the rest of the program.

2. What are some advantages of having a 'virtualized resource' in Horde3D?

**Advantage 1**: Performance. Applications can choose how to load resources into memory in a way that's 
appropriately optimized for their use case.

**Advantage 2**: Portability and platform-independence. Rather than concerning itself with working on every operating 
system and platform under the sun, Horde3D can delegate these responsibilities—either to OS calls, application calls, 
or another library. This massively reduces the scope of Horde3D while simplified its programming.


-------------------------------------------------------

> (Text archived here)
> http://www.horde3d.org/docs/html/_usageguide.html
>
>
> Resource Management
>A resource is a data object that is required to render the scene, for example a texture or shader. One important property of resources is that they are reusable. This means that they can be referenced by several different objects like scene nodes but only have to be loaded once. Every resource is identified by a name that is unique for the resource type and by which the resource can referenced from other objects.
>
>All resources are managed by a resource manager. The resource manager contains a list of resources and ensures that they are only loaded once and reused after that. It is also responsible for finding, accessing and removing resources. In contrast to some other engines, Horde3D uses one single manager for all resources and not different ones for each type of resource. To make resource handling more robust, the manager is applying reference counting. A resource can only be removed if it is no longer referenced by some other object, e.g. another resource or scene node. It is also possible to perform explicit garbage collection in order to release and remove all unused resources.
>
>Horde3D uses deferred loading of resources. This means that resource creation and loading are discrete steps. This separation brings the advantage that the data doesn't need to be available immediately when the resource is added and makes it in principle possible to have a dedicated thread for background loading. When the resource is created, it is initialized with type-specific default data and is already available to be referenced by other objects. After creation the resource can be loaded and filled with the desired data. In this process the basic data structures are set up and initialized. After loading it is usually possible to alter the data values of a resource but not the data structure. For a texture as an example this means that the color values of all pixels can be changed but not the dimensions or color depth of the image. When a resource has already been loaded, it can not be loaded again but it is possible to unload the resource and thus reset it to the initial state it had directly after creation.
>
>The loading of resources is completely virtualized in Horde3D. The engine doesn't do any file accesses and just expects a memory block from the application. It is up to the application to decide from where to get this block, e.g. to read it from an appropriate file. The advantage of this system is that Horde3D doesn't force the user to have some specific archive format. Resource data can come from any source and could even be streamed over a network. It is also possible to generate the data block dynamically to realize procedural content.
