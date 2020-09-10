// Copyright (C) 2020 Denis Isai

#ifndef LOGGING_H
#define LOGGING_H

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// system includes
#include <stdio.h>

// dependency includes
#include "gen-types.h"

//======================================================================================================================
// DEFINES
//======================================================================================================================

#define ENABLE_DEBUG     ON  // disable to remove prints and reduce file size; "-h"/error prints will not be shown
#define ENABLE_VERBOSITY OFF // enable if you want a lot of console spam with a lot of events

#if(TRUE == ENABLE_DEBUG)
    #define PRINT_OKAY(...) \
        do { printf("[ %sOKAY%s ] ", F_GRN, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_OKAY(...)
#endif

#if(TRUE == ENABLE_DEBUG)
    #define PRINT_WARN(...) \
        do { printf("[ %sWARN%s ] ", F_YEL, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_WARN(...)
#endif

#if(TRUE == ENABLE_DEBUG)
    #define PRINT_FAIL(...) \
        do { printf("[ %sFAIL%s ] ", F_RED, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_FAIL(...)
#endif

#if(TRUE == ENABLE_DEBUG)
    #define PRINT_INFO(...) \
        do { printf("[ %sINFO%s ] ", F_CYN, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_INFO(...)
#endif

#if(TRUE == ENABLE_DEBUG)
    #define PRINT_TEXT(...) \
        do { printf("  %s    %s   ", F_RST, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_TEXT(...)
#endif

#if(TRUE == ENABLE_DEBUG) && (ON == ENABLE_VERBOSITY)
    #define PRINT_VERB(...) \
        do { printf("[ %sVERB%s ] ", F_MAG, F_RST); printf(__VA_ARGS__); printf("%s\n", F_RST); } while(0)
#else
    #define PRINT_VERB(...)
#endif

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
