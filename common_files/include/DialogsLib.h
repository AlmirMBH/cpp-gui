#pragma once

#ifdef MU_WINDOWS
    #ifdef DIALOGS_LIB_EXPORTS
        #define DIALOGS_LIB_API __declspec(dllexport)
    #else
        #define DIALOGS_LIB_API __declspec(dllimport)
    #endif
#else
    #ifdef DIALOGS_LIB_EXPORTS
        #define DIALOGS_LIB_API __attribute__((visibility("default")))
    #else
        #define DIALOGS_LIB_API
    #endif
#endif


