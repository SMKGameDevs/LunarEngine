/* Copyright (C) Mydnyte Wolfy | 2026
Origin date: Sept 26, 2026
--- FIle Start ---*/
 
#include "Lunar/Core.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string> 
#include <array>

//Build switch
#ifdef LUNAR_DEBUG //Has all logging

#define TRACE(Location, Message)    LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Trace, Location, Message)
#define INFO(Location, Message)     LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Info, Location, Message)
#define WARN(Location, Message)     LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Warning, Location, Message)
#define ERROR(Location, Message)    LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Error, Location, Message)
#define CRITICAL(Location, Message) LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Critical, Location, Message)

#endif
#ifdef LUNAR_RELEASE //Has warn and errors

#define TRACE(Location, Message)    //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Trace, Location, Message)
#define INFO(Location, Message)     //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Info, Location, Message)
#define WARN(Location, Message)     LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Warning, Location, Message)
#define ERROR(Location, Message)    LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Error, Location, Message)
#define CRITICAL(Location, Message) LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Critical, Location, Message)

#endif
#ifdef LUNAR_NO_TERMINAL //disables all

#define TRACE(Location, Message)    //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Trace, Location, Message)
#define INFO(Location, Message)     //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Info, Location, Message)
#define WARN(Location, Message)     //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Warning, Location, Message)
#define ERROR(Location, Message)    //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Error, Location, Message)
#define CRITICAL(Location, Message) //LunarSystems::InternalLogging::PushMessage(LunarSystems::LogType::Critical, Location, Message)

#endif

//Logging shite
namespace LunarSystems
{
    enum class LogType
    {
        Trace       = 0,
        Info        = 1,
        Warning     = 2,
        Error       = 3,
        Critical    = 4,
        NOAPPLY     = 5
    };
    
    struct LogFormat
    {
        std::vector<std::string> m_FormatOrder;
        bool m_UseColors;
    };
    
    class Messager
    {
    protected:
        Messager();
        ~Messager();
        
        void SetColor(std::array<float, 3> p_Color);
        
        void ToConsole(const std::string& p_Message, bool p_UseColor = false);
        void ToConsole(const std::string& p_Message, void* p_Console, bool p_UseColor = false) { ToConsole(p_Message, p_UseColor); }
        
        void operator>>(const std::string& p_Message);
        std::string operator<<(std::string& p_Return);
        
        friend class InternalLogging;
    private:
        void* m_ConsoleList;
        std::array<float, 3> m_Color;
        std::string m_LastMessage = "";
    };
    
    class LUNAR_API InternalLogging
    {
    private:
        InternalLogging(); //Do not use
        ~InternalLogging();
        
    public:
        static void Init();
        static InternalLogging* GetInstance();
        static void Shutdown();
        
        static void PushMessage(LogType p_LogLevel, const std::string& p_Location, const std::string& p_Message);
        static void PushMessage(LogType p_LogType, const char* p_Location, const std::string& p_Message)
        {
            std::string p_LocationUpdated = p_Location;
            PushMessage(p_LogType, p_LocationUpdated, p_Message.c_str());
        }
        
        template<typename T>
        static void PushMessage(LogType p_LogLevel, T p_Location, const std::string& p_Message ) //Auto inference. Less clean, but reliable
        {
            std::string Type = typeid(T).name();
            PushMessage(p_LogLevel, Type, p_Message);
        }
        
        static void SetFormat(std::vector<std::string> p_String);
        
        void operator>>(LogType p_LogLevel) {}
        void operator>>(const std::string& p_Message) {}
        const std::string& operator<<(const std::string& p_Return) {}
        
        //Logger >> Trace >> "This is some info";
    private:
        static std::string TypeConverter(LogType p_LogType);
        
        static inline LogFormat m_Format =
        {
          .m_FormatOrder = {"[", "%Level%", "] | ", "%Location%", " : ", " | ", "%Message%"},
          .m_UseColors = false
        };
        static inline std::string m_MessageBuilder = "";
        
        static inline Messager* m_Messager = nullptr;
        static inline InternalLogging* m_InternalLogging = nullptr;
    };
}