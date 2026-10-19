#include "Lunar/Engine.h"
#include "Lunar/Module.h"
#include "Lunar/InternalLogging.h"
//#include "Lunar/Components/Logger.h"

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
        LunarSystems::InternalLogging::Init();
        LunarSystems::RunModuleTest();
    }
}
