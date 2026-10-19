#include <Lunar/Engine.h>
#include "Application.h"

using namespace LunarRuntime;

Application::Application() {p_EngineInstance = new Lunar::Engine();}
Application::~Application() {delete p_EngineInstance;}

void Application::Start()
{
    
    
    
    std::cout << "Application Loading." << std::endl;
    p_EngineInstance->Run();
    
}