/* Copyright (C) Mydnyte Wolfy | 2026
 Origin date: Sept 24, 2026
 --- File Start --- */

#pragma once

#include "Core.h"
#include <typeinfo>
#include <string>
#include <map>

#include <iostream>
#include <stdio.h>

namespace LunarSystems
{
    class LUNAR_API ModuleBase;
    
    /* ------------------------------------------------------------------- */
    class LUNAR_API ModuleLibrary //Keeps a callable list of all active modules.
    {
    private:
        ModuleLibrary() {}
        ~ModuleLibrary() {}
        
    public:
        static void Init();
        static void PushToLibrary(ModuleBase* p_Module, const std::string& p_TypeInfo);
        static void PopFromLibrary(ModuleBase* p_Module, const std::string& p_TypeInfo);
        
        static int ShutdownLibrary(); //shuts down all modules. Returns the number of modules in library that failed to shutdown.
        
        template<typename T>
        static T* GetModule(); //return the module. lol
        
        template<typename T>
        static std::string GetModuleName();
        //Utils
        static void LibrarySwitchVerboseErrorLoggingMode(bool p_AllowVerbose = false);
        
    private:
        template<typename T>
        static std::map<std::string, ModuleBase*>::iterator ScanForModule();
        
        static ModuleBase* GrabModule(std::map<std::string, ModuleBase*>::iterator p_ModuleID);
        
        static inline std::map<std::string, ModuleBase*> m_Modules = {};
    };
    
    /* -------------------------------------------------------- */
    class ModuleBase //Creates the core callable structure for modules
    {
    public:
        ModuleBase();
        virtual ~ModuleBase();
    
    protected:
        template<typename T>
        void OnInit(ModuleBase* p_Module); //Push a pointer to a given module.
        
        template<typename T>
        void OnDestroy(ModuleBase* p_Module); //Remove a pointer. If found.
    };
    
    /* -------------------------------------------------- */
    template<typename T>
    class LUNAR_API Module : public ModuleBase //The top level Module. Direct inheritence to the specific types. 
    {
    public:
        
        Module();
        ~Module();
    };
    
    /* Test Module */
    
    class LUNAR_API TestModule : public Module<TestModule>
    {
    public:
        TestModule(std::string Name) {m_Name = Name;}
        ~TestModule() {}
        void PrintName() {std::cout << m_Name << std::endl;}
        
    private:
        
        std::string m_Name;
    };
    
    void LUNAR_API RunModuleTest();
}