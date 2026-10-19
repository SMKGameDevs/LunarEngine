/* Copyright (C) Mydnyte Wolfy | 2026
Origin Date: Oct 11, 2026
--- File Start --- */

#include "Core.h"
#include <format>
#include <iostream>
#include <stdio.h>
#include <memory>
#include <concepts>
#include <map>


namespace Lunar
{
    //Console types
    enum class LUNAR_API ConsoleType
    {
        Terminal    = 0, //standard terminal
        Engine      = 1, //Console built into the engine.
        Other       = 2 //Any unrecognized console. I.E. If someone builds a terminal in their game.
    };
    
    enum class LUNAR_API TextAttributes
    {
        RESET       = 0,
        RED         = 1,
        GREEN       = 2,
        YELLOW      = 3,
        BLUE        = 4,
        PURPLE      = 5,
        CYAN        = 6,
        WHITE       = 7,

        BOLD        = 8,
        ULINE       = 9,
        ITALIC      = 10,

        BG_RESET    = 11,
        BG_RED      = 12,
        BG_GREEN    = 13,
        BG_YELLOW   = 14,
        BG_BLUE     = 15,
        BG_PURPLE   = 16,
        BG_CYAN     = 17,
        BG_WHITE    = 18
    };
    
    //wrapper for a standardized console. Can be used as standalone output to OS, or to something made in the engine.
    class LUNAR_API Console
    {
    private:
    
        Console();
        ~Console(); //MUST remove itself from the map

        //Shutdown all consoles
        static void KillAll();

        static std::map<std::shared_ptr<Console>, const std::string_view>::iterator CheckForConsole(const std::string_view p_Name);

    public:
        //Templatey stuffs
        template<std::derived_from<Console> T>
        static const std::shared_ptr<T> Create(const std::string_view p_Name) //must inherit parent console class
        {
            //Check Console first
            if(CheckForConsole() != m_ActiveConsoleList.end())  //if a console exists:
            {
                return nullptr;
            }
            else                                                //if no console exists:
            {
                auto NewConsole = std::make_shared<T>;
                m_ActiveConsoleList.emplace(NewConsole, p_Name);//Implicit cast to Base

                return NewConsole;
            }
        } 

        template<std::derived_from<Console> T>
        static const std::shared_ptr<T> GetConsole(const std::string_view p_Name)
        {
            auto ConsoleMapIterator = CheckForConsole();
            if( ConsoleMapIterator == m_ActiveConsoleList.end())    //If no console is found
            {
                return nullptr;
            }
            else                                                    //If a console exists
            {
                auto MapPtr = ConsoleMapIterator->first; //get the ptr

                if(auto TypedMapPtr = std::dynamic_pointer_cast<T>(MapPtr)) //If cast can be done
                {
                    return TypedMapPtr;
                }
                else                                                        //If cast cannot be done
                {
                    return nullptr;
                }
            }
        }

        //determine the console type and use appropriate print.
        virtual void Print(const std::string& p_Message) = 0;
        
        //Kills this specific instance
        void Kill();


    private:
        static std::map<std::shared_ptr<Console>, const std::string_view> m_ActiveConsoleList;

        //information about the console details. Type, format, more.
        struct LUNAR_API ConsoleInfo
        {
            ConsoleType m_Type;
            std::string m_Format;
            bool m_UseColoring;
            //font
            //size
            std::string m_OS;
        };
    };

    //Native console.
    class LUNAR_API NativeConsole : public Console
    {
    public:
        NativeConsole();
        ~NativeConsole();


    };
}