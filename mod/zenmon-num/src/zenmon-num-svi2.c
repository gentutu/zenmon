// Copyright (C) 2020 Denis Isai

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// system includes
#include "stdio.h"
#include "stdlib.h"

// generic includes
#include "gen-types.h"

// local includes
#include "zenmon-types.h"

//======================================================================================================================
// VARIABLES
//======================================================================================================================
static stateType num_svi2_state = DEINIT;

static metricsType* mDB; // svi2 metrics database

//======================================================================================================================
// FUNCTION DECLARATIONS
//======================================================================================================================
static sint32 svi2_getSingleStatus(      FILE* const file);
static void   svi2_setSingleMinMax(metricType* const type);
static void   svi2_setSingleAvg(   metricType* const metric);

//======================================================================================================================
// API DEFINITIONS
//======================================================================================================================
void svi2_init(metricsType* const inDB) //-------------------------------------------------------------------- svi2_init
{
    mDB = inDB;

    num_svi2_state = INIT;
}

void svi2_deinit(void) //----------------------------------------------------------------------------------- svi2_deinit
{
    num_svi2_state = DEINIT;
}

statusType svi2_getStatus(void) //----------------------------------------------------------------------- svi2_getStatus
{
    statusType status = NOK;

    if(INIT == num_svi2_state)
    {
        // electrical (core)
        (*mDB).vcore.now = svi2_getSingleStatus((*mDB).vcore.FD);                            // mV
        (*mDB).acore.now = svi2_getSingleStatus((*mDB).acore.FD); (*mDB).acore.now /= 1000u; //  A
        (*mDB).wcore.now = (*mDB).vcore.now * (*mDB).acore.now / 1000u;                      //  W

        // electrical (soc)
        (*mDB).vsoc.now  = svi2_getSingleStatus((*mDB).vsoc.FD);                             // mv
        (*mDB).asoc.now  = svi2_getSingleStatus((*mDB).asoc.FD); (*mDB).asoc.now  /= 1000u;  //  A
        (*mDB).wsoc.now  = (*mDB).vsoc.now * (*mDB).asoc.now / 1000u;                        //  W

        // temperature
        (*mDB).cdie.now  = svi2_getSingleStatus((*mDB).cdie.FD);  (*mDB).cdie.now  /= 1000u; // °C
        (*mDB).cctl.now  = svi2_getSingleStatus((*mDB).cctl.FD);  (*mDB).cctl.now  /= 1000u; // °C
        (*mDB).cccd0.now = svi2_getSingleStatus((*mDB).cccd0.FD); (*mDB).cccd0.now /= 1000u; // °C
        (*mDB).cccd1.now = svi2_getSingleStatus((*mDB).cccd1.FD); (*mDB).cccd1.now /= 1000u; // °C

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType svi2_setMinMax(void) //----------------------------------------------------------------------- svi2_setMinMax
{
    statusType status = NOK;

    if(INIT == num_svi2_state)
    {
        // electrical (core)
        svi2_setSingleMinMax(&((*mDB).vcore));
        svi2_setSingleMinMax(&((*mDB).acore));
        svi2_setSingleMinMax(&((*mDB).wcore));

        // electrical (soc)
        svi2_setSingleMinMax(&((*mDB).vsoc));
        svi2_setSingleMinMax(&((*mDB).asoc));
        svi2_setSingleMinMax(&((*mDB).wsoc));

        // temperature
        svi2_setSingleMinMax(&((*mDB).cdie));
        svi2_setSingleMinMax(&((*mDB).cctl));
        svi2_setSingleMinMax(&((*mDB).cccd0));
        svi2_setSingleMinMax(&((*mDB).cccd1));

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType svi2_setAvg(void) //----------------------------------------------------------------------------- svi2_setAvg
{
    statusType status = NOK;

    static uint8 waitCycles = 1u;

    if(INIT == num_svi2_state)
    {
        if(AVG_CYCLES < waitCycles) // wait 10 cycles
        {
            // electrical
            svi2_setSingleAvg(&((*mDB).vcore));
            svi2_setSingleAvg(&((*mDB).acore));
            svi2_setSingleAvg(&((*mDB).wcore));

            svi2_setSingleAvg(&((*mDB).vsoc));
            svi2_setSingleAvg(&((*mDB).asoc));
            svi2_setSingleAvg(&((*mDB).wsoc));

            // temperature
            svi2_setSingleAvg(&((*mDB).cdie));
            svi2_setSingleAvg(&((*mDB).cctl));
            svi2_setSingleAvg(&((*mDB).cccd0));
            svi2_setSingleAvg(&((*mDB).cccd1));
        }
        else
        {
            waitCycles++;
        }

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType svi2_printTable(uint16 xPos, const uint16 yPos) //------------------------------------------- svi2_printTable
{
    // these hardcoded positions depend on where the static labels are printed in zenmon-box.c

    // temperatures can only go as high as 95, but they are displayed as 3-digit numbers for better printf alignment

    statusType status = NOK;

    uint16 yIndex;

    if(INIT == num_svi2_state)
    {
        // xPos remains as is
        yIndex = yPos;

        // minimum values; these are the only ones without warning colours
        xPos += 14u;
        PRINTL(xPos, yIndex++, "%3d", (*mDB).vcore.min / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%3d", (*mDB).acore.min);
        PRINTL(xPos, yIndex++, "%3d", (*mDB).wcore.min);

        PRINTL(xPos, yIndex++, "%3d", (*mDB).vsoc.min / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%3d", (*mDB).asoc.min);
        PRINTL(xPos, yIndex++, "%3d", (*mDB).wsoc.min);

        yIndex++; // jump over the separation line
        PRINTL(xPos, yIndex++, "%3d", (*mDB).cdie.min);
        PRINTL(xPos, yIndex++, "%3d", (*mDB).cctl.min);
        PRINTL(xPos, yIndex++, "%3d", (*mDB).cccd0.min);
        PRINTL(xPos, yIndex++, "%3d", (*mDB).cccd1.min);

        // current values
        xPos   += 9u;
        yIndex  = yPos;
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vcore.now, LIM_V, F_RED), (*mDB).vcore.now / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).acore.now, LIM_A, F_RED), (*mDB).acore.now);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wcore.now, LIM_W, F_RED), (*mDB).wcore.now);

        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vsoc.now , LIM_V, F_RED), (*mDB).vsoc.now / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).asoc.now , LIM_A, F_RED), (*mDB).asoc.now);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wsoc.now , LIM_W, F_RED), (*mDB).wsoc.now);

        yIndex++; // jump over the separation line
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cdie.now , LIM_C, F_RED), (*mDB).cdie.now);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cctl.now , LIM_C, F_RED), (*mDB).cctl.now);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd0.now, LIM_C, F_RED), (*mDB).cccd0.now);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd1.now, LIM_C, F_RED), (*mDB).cccd1.now);

        // maximum values
        xPos   += 9u;
        yIndex  = yPos;
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vcore.max, LIM_V, F_YEL), (*mDB).vcore.max / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).acore.max, LIM_A, F_YEL), (*mDB).acore.max);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wcore.max, LIM_W, F_YEL), (*mDB).wcore.max);

        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vsoc.max , LIM_V, F_YEL), (*mDB).vsoc.max / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).asoc.max , LIM_A, F_YEL), (*mDB).asoc.max);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wsoc.max , LIM_W, F_YEL), (*mDB).wsoc.max);

        yIndex++; // jump over the separation line
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cdie.max , LIM_C, F_YEL), (*mDB).cdie.max);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cctl.max , LIM_C, F_YEL), (*mDB).cctl.max);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd0.max, LIM_C, F_YEL), (*mDB).cccd0.max);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd1.max, LIM_C, F_YEL), (*mDB).cccd1.max);

        // average values
        xPos   += 9u;
        yIndex  = yPos;
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vcore.avg, LIM_V, F_RED), (*mDB).vcore.avg / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).acore.avg, LIM_A, F_RED), (*mDB).acore.avg);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wcore.avg, LIM_W, F_RED), (*mDB).wcore.avg);

        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).vsoc.avg , LIM_V, F_RED), (*mDB).vsoc.avg / 10u); // mV to cV
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).asoc.avg , LIM_A, F_RED), (*mDB).asoc.avg);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).wsoc.avg , LIM_W, F_RED), (*mDB).wsoc.avg);

        yIndex++; // jump over the separation line
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cdie.avg , LIM_C, F_RED), (*mDB).cdie.avg);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cctl.avg , LIM_C, F_RED), (*mDB).cctl.avg);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd0.avg, LIM_C, F_RED), (*mDB).cccd0.avg);
        PRINTL(xPos, yIndex++, "%s%3d", CHK_LIM((*mDB).cccd1.avg, LIM_C, F_RED), (*mDB).cccd1.avg);

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

//======================================================================================================================
// FUNCTION DEFINITIONS
//======================================================================================================================
static sint32 svi2_getSingleStatus(FILE* const file) //-------------------------------------------- svi2_getSingleStatus
{
    sint8  fileString[10] = {0};
    uint32 length;

    fseek(file, 0, SEEK_END);
    length = ftell (file);
    fseek(file, 0, SEEK_SET);
    fread(fileString, 1, length, file);

    return atoi(fileString);
}

static void svi2_setSingleMinMax(metricType* const type) //---------------------------------------- svi2_setSingleMinMax
{
    (*type).min = GETMIN((*type).min, (*type).now);
    (*type).max = GETMAX((*type).max, (*type).now);
}

static void svi2_setSingleAvg(metricType* const metric) //-------------------------------------------- svi2_setSingleAvg
{
    uint8 index;

    (*metric).avg = 0u;

    for(index = LEN_PLOT_D_X - AVG_CYCLES; index < LEN_PLOT_D_X; index++)
    {
        (*metric).avg += (*metric).hst[index];
    }

    (*metric).avg /= AVG_CYCLES;
}

//======================================================================================================================
// END OF FILE
//======================================================================================================================
