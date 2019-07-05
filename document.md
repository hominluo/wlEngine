# wlEngine Engine Design Document
Note: the engine is currently under development, the document tends to explain in a macro perspective.
## Terminology and Their Functions
### 1. GameObject and Entity
current `Entity` is sharing the same meaning as `GameObject`. They are forming the Parent-Child relationship with `Scene`. `GameObject` is capable of holding any `Component` Object. However, `GameObject` is not responsible for updating its components. (Of course, you are not restricted to do so if you want). The `GameObject` has a update function for you to override, which is called even if the engine is in *Editor* mode. Usually we control the GameObject through `Script`, but `Script` is a subclass of `Component` which is not updated when the engine is in *Editor* mode.

### 2. FixedArrayAllocator
fixedArrayAllocator is the memory allocator I am currently using.  It's mainly used to allocate `Component` and `GameObject` in run-time to avoid massive `new` and `delete` call. 
#### a. beacon
points to the next free memory area `Arena` ready for allocation
#### b. MemoryChunk
you can think of `MemoryChunk` as a vector that stores the objects. It tracks the count of the free memory of itself. Once `FixedArrayAllocator` finds the `MemoryChunk` is totally free (no object resides in it). The memoryChunk will be *deleted*
#### c. Arena
`Arena` is the smallest unit that stores the `GameObject`. It also has the information of the MemoryChunk it belongs to in the `chunk` pointer. Arena uses the freelist design. When it's free, `bytes` will store the next free Arena and will store the object when it's in use

#### Note:
`FixedArrayAllocator` still has lots of improvement we can work on and I am not satisfied in many ways it was designed. And I adimit I can't say for sure it actually boosts the run-time speed. However, it does give me the flexbility and the interface to improve. I will list some directions to improve it. But, unless I notice a significant need to change it, I will not touch it because it works perfectly for now.

#### Problems and Improvements:
1. Whoever uses the allocator needs to specify (estimate) the size of the allocator
2. When a `MemoryChunk` is totally freed, the memory will be destoryed immediately. The problem arise when the only memory inside a `MemoryChunk` is rapidly being repeatedly allocated and deallocated
3. Related to #2, we can delay the deallocation of the `MemoryChunk` for a few frames to avoid rapid deallocation of using *delete*
4. Every `Arena` stores a pointer to its memoryChunk, which creates a overhead
5. please confirm the current design of the `Arena` is acceptable (it currently hides the memory of the chunk pointer by casting when it's allocated to object)

### 3. System
`System` follows the concept of the ECS pattern. It's used to update the components and there is a update function called for each frame.

### 4. Manager
`Manager` doesn't have update function. It' used in the scenario like resource management, IO management etc. 

#### `EngineManager` 
 `EngineManager` a special manager which is the entry point and "the manager" of the engine. `EngineManager` 