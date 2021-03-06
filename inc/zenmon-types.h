// Copyright (C) 2020 Denis Isai

#ifndef ZENMON_TYPES_H
#define ZENMON_TYPES_H

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// generic includes
#include "gen-types.h"

// local includes
#include "zenmon-cfg.h"

//======================================================================================================================
// DEFINES
//======================================================================================================================
// used to change the colour of text when the value goes above a threshold
#define CHK_LIM(value, threshold, colour) ((value >= threshold) ? colour : F_RST)

//======================================================================================================================
// TYPES
//======================================================================================================================
typedef struct metricTypeTag // data related to a single k10temp metric
{
      FILE* FD;
    uint32  min;
    uint32  now;
    uint32  max;
    uint32  avg;
    uint16  hst[LEN_PLOT_D_X];
} metricType;

typedef struct metricsTypeTag // all k10temp metrics
{
    metricType vcore; // millivolts
    metricType acore; //     amperes
    metricType wcore; //     watts
    metricType  vsoc; // millivolts
    metricType  asoc; //     amperes
    metricType  wsoc; //     watts
    metricType  cdie; //    °Celsius
    metricType  cctl; //    °Celsius
    metricType cccd0; //    °Celsius
    metricType cccd1; //    °Celsius
} metricsType;

typedef struct graphBufferTypeTag // graph buffers
{
    uint8 vcore[LEN_PLOT_BUF]; // millivolts
    uint8 acore[LEN_PLOT_BUF]; //     amperes
    uint8 wcore[LEN_PLOT_BUF]; //     watts
    uint8  vsoc[LEN_PLOT_BUF]; // millivolts
    uint8  asoc[LEN_PLOT_BUF]; //     amperes
    uint8  wsoc[LEN_PLOT_BUF]; //     watts
    uint8  cdie[LEN_PLOT_BUF]; //    °Celsius
    uint8  cctl[LEN_PLOT_BUF]; //    °Celsius
    uint8 cccd0[LEN_PLOT_BUF]; //    °Celsius
    uint8 cccd1[LEN_PLOT_BUF]; //    °Celsius
} graphBufferType;

typedef struct cpuUsgTypeTag // cpu thread usage
{
    uint32 lastIdle; // data from last measurement cycle
    uint32 lastSum;  // data from last measurement cycle
    uint16 idle;     // (100 - idle) gives the usage %
} cpuUsgType;

typedef struct sysLoadTypeTag // system load
{
    FILE*      mhzFD;
    FILE*      usgFD;
    FILE*      ramFD;
    uint16     cpuMhz[CPU_CORES];
    cpuUsgType cpuUsg[CPU_THREADS];
    uint32     ramUsg;
    uint32     ramAll;
} sysLoadType;

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
