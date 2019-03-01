#include <cstdlib>

namespace wlEngine {
#define snew(T) StackNew(sizeof(T))
#define sdelete(P) StackDelete(P)

    void* StackNew(size_t size);
    void StackDelete(void* p);
}
