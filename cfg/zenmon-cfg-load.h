// Copyright (C) 2020 Denis Isai

#ifndef ZENMON_CFG_LOAD_H
#define ZENMON_CFG_LOAD_H

// Block characters for CPU/RAM bars
//         0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
// U+258x  ▀  ▁  ▂  ▃  ▄  ▅  ▆  ▇  █  ▉  ▊  ▋  ▌  ▍  ▎  ▏
// U+259x  ▐  ░  ▒  ▓  ▔  ▕  ▖  ▗  ▘  ▙  ▚  ▛  ▜  ▝  ▞  ▟

//======================================================================================================================
// DEFINES
//======================================================================================================================
// file paths; these are checked at runtime and if any are missing the program will notify and exit
#define FILE_MHZ         "/proc/cpuinfo"                 // cpu core   frequency
#define FILE_USG         "/proc/stat"                    // cpu thread usage
#define FILE_RAM         "/proc/meminfo"                 // RAM        usage

// load window size
#define LEN_LOAD_W_X        47u                          // X size in characters
#define LEN_LOAD_W_Y        25u                          // Y size in characters

// static configuration
#define CPU_CORES           16u
#define CPU_THREADS         32u
#define SEG_PER_BOX          8u                          // the full block has 8 segments
#define LEN_LINE           512u                          // I don't expect any lines to be longer

#define SUBBARS_PER_BOX      8u                          // number of horizontal/vertical sub/boxes per full box

// RAM usage bar config
#define RAM_AVAIL_OFFSET    13u                          // characters to skip when reading the available RAM line
#define RAM_TOTAL_OFFSET     9u                          // characters to skip when reading the total     RAM line
#define RAM_BAR_LEN      (LEN_LOAD_W_X - 4u)             // RAM bar length in characters
#define RAM_BAR_LIM      (RAM_BAR_LEN  / 2u)             // bar turns red at 50% RAM usage

// core MHz bars config
#define MHZ_OFFSET          10u                          // characters to skip when reading the MHz line
#define MHZ_CPU_MAX       5000u                          // max value of the MHz bar in MHz
#define MHZ_BAR_LEN          5u                          // height of the MHz bar in lines
#define MHZ_BAR_LIM          4u                          // bar turns red at 80% MHz of MAX
#define MHZ_PER_BOX      (MHZ_CPU_MAX / MHZ_BAR_LEN)     // value of a full bar in MHz
#define MHZ_PER_SEG      (MHZ_PER_BOX / SUBBARS_PER_BOX) // value of a sub-bar  in MHz

// thread usage bars config; permille instead of percent is used because of high bar granularity
#define USG_CPU_MAX       1000u                          // reference value for 100% load
#define USG_BAR_LEN          5u                          // height of the usage bar in lines
#define USG_BAR_LIM          4u                          // bar turns red at 80% usg of MAX
#define USG_PER_BOX      (USG_CPU_MAX / USG_BAR_LEN)     // value of a full bar in usage
#define USG_PER_SEG      (USG_PER_BOX / SUBBARS_PER_BOX) // value of a sub-bar  in usage

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
