#pragma once

#include <iostream>
#include <cstddef>

namespace wlEngine {
    template<typename T>
    void destroy(T* ptr) {
        T::destroy(ptr);
    }

    template <typename T, size_t N>
    class ComponentAllocator {
    private:
        struct ComponentMemoryChunk {
            struct Arena {
                static_assert(sizeof(T) > sizeof(void*), "Component Class has to have a size larger than a size of a pointer");
                char bytes[sizeof(T)];
                ComponentMemoryChunk* chunk;
            }  arena[N]; //store N arena, 1 arena for 1 object of type T

            size_t freeCount = N;
            /**
             * @brief Initialize Component Allocator
             */
            ComponentMemoryChunk()  {
                size_t i = 0;
                for (; i < N - 1; i++) {
                    arena[i].chunk = this;
                    *reinterpret_cast<Arena**>(arena[i].bytes) = &arena[i+1];
                }
                arena[i].chunk = this;
                *reinterpret_cast<Arena**>(arena[i].bytes) = nullptr;
            }
            
            ~ComponentMemoryChunk() = default;
        };
    public:
        ComponentAllocator() {
			beacon = allocateNewChunk();
        }
        
        ~ComponentAllocator() = default;
        
        template<typename... Args>
        T* allocate(Args&& ... params) {
            
            auto succ = *reinterpret_cast<typename ComponentMemoryChunk::Arena**>(beacon->bytes);
            auto temp = beacon;
            
            beacon->chunk->freeCount -= 1;
            if (succ)
                beacon = succ;
            else
                beacon = allocateNewChunk();

            return new (reinterpret_cast<T*>(temp)) T(params...);
        }

        void deallocate(T* ptr) {
            auto arenaPtr = reinterpret_cast<typename ComponentMemoryChunk::Arena*>(ptr);
            auto chunk = arenaPtr->chunk;
            chunk->freeCount += 1;
            
            if (beacon->chunk->freeCount == N && chunk != beacon->chunk && chunkCount != 1) {
                chunkCount -= 1;
                delete beacon->chunk;
                beacon = nullptr;
            }
            
            *reinterpret_cast<typename ComponentMemoryChunk::Arena**>(arenaPtr->bytes) = beacon;
            beacon = arenaPtr;
        }
    private:
        typename ComponentMemoryChunk::Arena* beacon;
        size_t chunkCount;

        typename ComponentMemoryChunk::Arena* allocateNewChunk() {
            chunkCount += 1;
            auto chunk = new ComponentMemoryChunk;
            return chunk->arena;
        }
    };
}


