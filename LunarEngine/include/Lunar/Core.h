#pragma once

#if defined(_WIN32)
    #if defined(LUNAR_BUILD_DLL)
        #define LUNAR_API __declspec(dllexport)
    #else
        #define LUNAR_API __declspec(dllimport)
    #endif
#else
    #define LUNAR_API __attribute__((visibility("default")))
#endif

