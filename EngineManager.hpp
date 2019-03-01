#include "Graphics/GraphicsManager.hpp"

namespace wlEngine {
    class EngineManager {
        public:
            static EngineManager* getwlEngine();
            ~EngineManager();

        private:
            static EngineManager* engine;

            EngineManager();
            void initializeManagers();

    };
}
