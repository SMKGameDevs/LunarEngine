#pragma once

#include "Lunar/Core.h"

namespace Lunar
{
    class LUNAR_API Engine
    {
    public:
        Engine();
        ~Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        void Run();
    };
}
