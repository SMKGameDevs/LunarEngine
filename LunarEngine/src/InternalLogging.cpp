/* Copyright (C) Mydnyte Wolfy | 2026
Origin date: Sept 26, 2026
--- File Start --- */

#include "Lunar/InternalLogging.h"

//Messager
using namespace LunarSystems;

Messager::Messager() {}
Messager::~Messager() {}

void Messager::SetColor(std::array<float, 3> p_Color) {m_Color = p_Color;}

void Messager::ToConsole(const std::string& p_Message, bool p_UseColor) 
{
    if (p_UseColor)
    {
        
    }
    
    //todo Else
    std::cout << p_Message << std::endl;
    
    m_LastMessage = p_Message;
}

void Messager::operator>>(const std::string& p_Message) 
{
    ToConsole(p_Message);
}

std::string Messager::operator<<(std::string& p_Return)
{
        p_Return = m_LastMessage;
    
    return p_Return;
}

//Internal Logging
InternalLogging::InternalLogging() {}

InternalLogging::~InternalLogging() {}

void InternalLogging::Init()
{
    if (m_InternalLogging == nullptr)
    {
        m_InternalLogging = new InternalLogging();
        
        m_MessageBuilder = "";
        m_Messager = new Messager();
    }
    else
    {
        std::cout << "Internal Logger already initialized. Please use GetInstance()" << std::endl;
    }
}

InternalLogging* InternalLogging::GetInstance()
{
    InternalLogging* ReturnPtr = nullptr;
    if (m_InternalLogging == nullptr)
    {
        std::cout << "Internal Loggger not available. Please run Init() to start" << std::endl;
    }
    else
    {
        ReturnPtr = m_InternalLogging;
    }
    return ReturnPtr;
}

void InternalLogging::Shutdown()
{
    if (m_InternalLogging != nullptr)
    {
        delete m_Messager;
        delete m_InternalLogging;
    }
    else
    {
        std::cout << "Internal Logger not running." << std::endl;
    }
}

void InternalLogging::PushMessage(LogType p_LogLevel, const std::string& p_Location, const std::string& p_Message)
{
    std::string ToPush = "";
    for (auto Item : m_Format.m_FormatOrder)
    {
        if (Item == "%Level%")
        {
            ToPush.append(TypeConverter(p_LogLevel));
        }
        else if (Item == "%Location%")
        {
            ToPush.append(p_Location);
        }
        else if (Item == "%Message%")
        {
            ToPush.append(p_Message);
        }
        else
        {
            ToPush.append(Item);
        }
    }
    
    m_Messager->ToConsole(ToPush);
}

void InternalLogging::SetFormat(std::vector<std::string> p_String)
{
    m_Format.m_FormatOrder = p_String;
}

//TODO OPERATORS

std::string InternalLogging::TypeConverter(LogType p_LogType)
{
    switch (p_LogType)
    {
        case LogType::Trace:
            return "Trace";
        case LogType::Info:
            return "Info";
        case LogType::Warning:
            return "Warning";
        case LogType::Error:
            return "Error";
        case LogType::Critical:
            return "Critical";
        default:
            return "Unknown";
    }
}
