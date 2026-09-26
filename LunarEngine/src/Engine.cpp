#include "Lunar/Engine.h"
#include "Lunar/Module.h"

#include <iostream>

namespace Lunar
{
    Engine::Engine()
    {
        std::cout << "[LunarEngine] Initialized\n";
    }

    Engine::~Engine()
    {
        std::cout << "[LunarEngine] Shutdown\n";
    }

    void Engine::Run()
    {
        LunarSystems::RunModuleTest();
        std::cout << "[LunarEngine] Running\n";
    }
}
