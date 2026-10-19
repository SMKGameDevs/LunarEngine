/* Copyright (C) Mydnyte Wolfy | 2026
Origin Date: Oct 11, 2026
--- File Start --- */

#include "Console.h"

//External defines for daily use.
#define Log(Logger, Level, Message, Console)    Logger->Log(Lunar::LogLevel::Level, Message, Console)
#define Log(Logger, Level, Message)             Logger->Log(Lunar::LogLevel::Level, Message)
#define Log(Level, Message, Console)            Lunar::Logger::GetLogger()->Log(Lunar::LogLevel::Level, Message, Console)
#define Log(Level, Message)                     Lunar::Logger::GetLogger()->Log(Lunar::LogLevel::Level, Message)

namespace Lunar
{   
    //Enum for determining logging level.
    enum class LogLevel
    {
        Info        = 0,
        Warning     = 1,
        Error       = 2,
        Fatal       = 3
    }

    //static based class for logging stuffs
    class Logger
    {
    protected: 
        Logger();
        ~Logger();
        
    public:
        //create a pointer to a static object if first time run.
        void Init();
        std::unique_ptr<Logger> GetLogger();
        
        void Log(const LogLevel p_Level, const std::string& p_Message, std::unique_ptr<Console> p_Console)
    protected:
        //Actual logging
        void Info(const std::string& p_Message);
        void Warning(const std::string& p_Message);
        void Error(const std::string& p_Message);
        void Fatal(const std::string& p_Message);
        
        //Takes in the raw message, as well as the console.
        void Print(const std::string& p_Message, std::unique_ptr<Console> p_Console = nullptr);
    };
}