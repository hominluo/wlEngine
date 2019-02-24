#include "Graphics/GraphicsManager.hpp"

namespace wlEngine {
    class wlEngine {
        public:
            static wlEngine* getwlEngine();
            ~wlEngine();

        private:
            static wlEngine* engine;

            wlEngine();
            void initializeManagers();

    };
}
