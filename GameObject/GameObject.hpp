#include <set>

#include "Transform.hpp"

#include "../Graphics/Texture.hpp"
namespace wlEngine {
    class GameObject {
    public:
        bool moveToParent(GameObject*);
    private:
        uint tag; 

        Texture* texture;
        Transform* transform;

        std::set<GameObject*> childs;

        void render();
    };
}
