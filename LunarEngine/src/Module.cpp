/* Copyright (C) Mydnyte Wolfy | 2026
Origin date: Sept 24, 2026
--- File Start --- */

#include "Lunar/Module.h"
#include "Lunar/InternalLogging.h"

using namespace LunarSystems;

//Module Library
void ModuleLibrary::Init() {m_Modules.emplace(typeid(ModuleLibrary).name(), nullptr);}

void ModuleLibrary::PushToLibrary(ModuleBase* p_Module, const std::string& p_TypeInfo)
{
    /*TODO ADD SCAN CONDITION*/
    TRACE("ModuleLib::PushMessage", "Emplace into buffer");
    m_Modules.emplace(p_TypeInfo, p_Module);
    
    int i = 0;
    for (auto Module : m_Modules)
    { 
        
        TRACE(m_Modules, "<- Module Stack: " + Module.first);
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
    TRACE("ModuleLib::GetModule", "Scanning for module of type: " + (std::string)typeid(T).name());
    auto Iter = ScanForModule<T>();
    return static_cast<T*>(GrabModule(Iter));
}

template<typename T>
std::string ModuleLibrary::GetModuleName()
{
    TRACE("MoudleLib::GetModuleName", "Got Name: " + (std::string)typeid(T).name());
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
    INFO("ModuleLib::SystemTest", "Initializing System Test");
        
    ModuleLibrary::Init();
    if (ModuleLibrary::GetModule<TestModule>() != nullptr) {ERROR("ModuleLib::SystemTest", "ModuleLib init failed");}
        
    TestModule* tMod = new TestModule("awawa");
    if (ModuleLibrary::GetModule<TestModule>() == nullptr) {WARN("ModuleLib::SystemTest", "ModuleLibrary Push failed."); }
    if (ModuleLibrary::GetModule<TestModule>() == tMod) {INFO("ModuleLib::SystemTest", "ModuleLibrary Push Sync.");}
    
    ModuleLibrary::GetModule<TestModule>()->PrintName();
    delete tMod;
    if (ModuleLibrary::GetModule<TestModule>() != nullptr) {ERROR("ModuleLib::SystemTeest", "ModuleLibrary Delete failed.");}
        
    ModuleLibrary::ShutdownLibrary();
}