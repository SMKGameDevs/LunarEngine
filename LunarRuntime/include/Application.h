/* Copyright (C) Mydnyte Wolfy @ 2026
Origin Date Sept 24, 2026
--- File Start --- */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <Lunar/Engine.h>
#include <Lunar/Module.h>

namespace LunarRuntime
{
    
    class Application
    {
    public:
        Application();
        ~Application();
        
        void Start();
        
    private:
        Lunar::Engine* p_EngineInstance = nullptr;
    };
}
