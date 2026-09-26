/* Copyright (C) Mydnyte Wolfy | 2026
Origin date: Sept 24, 2026
--- File Start --- */

#include "Lunar/Module.h"

using namespace LunarSystems;

//Module Library
void ModuleLibrary::Init() {m_Modules.emplace(typeid(ModuleLibrary).name(), nullptr);}

void ModuleLibrary::PushToLibrary(ModuleBase* p_Module, const std::string& p_TypeInfo)
{
    /*TODO ADD SCAN CONDITION*/
    m_Modules.emplace(p_TypeInfo, p_Module);
    
    for (auto Module : m_Modules)
    {
        std::cout << "PUSH: " << Module.first << " " << Module.second << std::endl;
    }
}

void ModuleLibrary::PopFromLibrary(ModuleBase* p_ModuleBase, const std::string& p_TypeInfo)
{
    /*TODO SCAN*/
    m_Modules.erase(p_TypeInfo);
}

template<typename T>
T* ModuleLibrary::GetModule()
{
    //std::cout << typeid(T).name() << std::endl;
    auto Iter = ScanForModule<T>();
    return static_cast<T*>(GrabModule(Iter));
}

template<typename T>
std::string ModuleLibrary::GetModuleName()
{
    std::cout << "NAME: " << typeid(T).name() << std::endl;
    return typeid(T).name();
}
int ModuleLibrary::ShutdownLibrary() {return 0;}

void ModuleLibrary::LibrarySwitchVerboseErrorLoggingMode(bool p_AllowVerbose) {/*TODO*/}

template<typename T>
std::map<std::string, ModuleBase*>::iterator ModuleLibrary::ScanForModule()
{
    return m_Modules.find(typeid(T).name()); //Returns m_Modules.end() if not found.
}

ModuleBase* ModuleLibrary::GrabModule(std::map<std::string, ModuleBase*>::iterator p_ModuleID)
{
    if (p_ModuleID == m_Modules.end()) {return nullptr;}
    
    ModuleBase* Module = p_ModuleID->second;
    return Module;
}
// Module Base
ModuleBase::ModuleBase() {}
ModuleBase::~ModuleBase() {}

template<typename T>
void ModuleBase::OnInit(ModuleBase* p_Module)
{
    ModuleLibrary::PushToLibrary(p_Module, ModuleLibrary::GetModuleName<T>());
}

template<typename T>
void ModuleBase::OnDestroy(ModuleBase* p_Module) //Remove a pointer. If found.
{
    ModuleLibrary::PopFromLibrary(p_Module, ModuleLibrary::GetModuleName<T>());
}

//Module
template<typename T>
Module<T>::Module()
{
    OnInit<T>(this);
}

template<typename T>
Module<T>::~Module()
{
    OnDestroy<T>(this);
}

void LunarSystems::RunModuleTest()
{
    std::cout << "Starting Module Test." << std::endl;
        
    ModuleLibrary::Init();
    if (ModuleLibrary::GetModule<TestModule>() != nullptr) {std::cout << "ModuleLibrary init failed." << std::endl;}
        
    TestModule* tMod = new TestModule("awawa");
    if (ModuleLibrary::GetModule<TestModule>() == nullptr) {std::cout << "ModuleLibrary Push failed." << std::endl;}
    if (ModuleLibrary::GetModule<TestModule>() == tMod) {std::cout << "ModuleLibrary Push Sync." << std::endl;}
    
    ModuleLibrary::GetModule<TestModule>()->PrintName();
    delete tMod;
    if (ModuleLibrary::GetModule<TestModule>() != nullptr) {std::cout << "ModuleLibrary Delete failed." << std::endl;}
        
    ModuleLibrary::ShutdownLibrary();
}