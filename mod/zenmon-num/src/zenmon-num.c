// Copyright (C) 2020 Denis Isai

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// system includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// generic includes
#include "logging.h"

// local includes
#include "zenmon-cfg.h"
#include "zenmon-num-svi2.h"
#include "zenmon-num-load.h"
#include "zenmon-num.h"

//======================================================================================================================
// VARIABLES
//======================================================================================================================
static stateType num_state = DEINIT;

static metricsType mDB; // svi2 metrics database
static sysLoadType sDB; // system usage database

//======================================================================================================================
// FUNCTION DECLARATIONS
//======================================================================================================================
static bool num_openFile(FILE** FD, const sint8* const name);

//======================================================================================================================
// API DEFINITIONS
//======================================================================================================================
void num_init(void) //----------------------------------------------------------------------------------------- num_init
{
    bool failure = FALSE;

    // open file descriptors
    failure |= num_openFile(&(mDB.vcore.FD), FILE_VCORE);
    failure |= num_openFile(&(mDB.acore.FD), FILE_ACORE);

    failure |= num_openFile(&(mDB.vsoc.FD) , FILE_VSOC);
    failure |= num_openFile(&(mDB.asoc.FD) , FILE_ASOC);

    failure |= num_openFile(&(mDB.cdie.FD) , FILE_CDIE);
    failure |= num_openFile(&(mDB.cctl.FD) , FILE_CCTL);
    failure |= num_openFile(&(mDB.cccd0.FD), FILE_CCCD0);
    failure |= num_openFile(&(mDB.cccd1.FD), FILE_CCCD1);

    failure |= num_openFile(&(sDB.mhzFD)   , FILE_MHZ);
    failure |= num_openFile(&(sDB.usgFD)   , FILE_USG);
    failure |= num_openFile(&(sDB.ramFD)   , FILE_RAM);

    if(FALSE != failure) // if any files don't exist then exit program
    {
        num_deinit();
        CURSOR_SHOW;
        PRINT_FAIL("Required files not found; exiting...");
        exit(EXIT_FAILURE);
    }

    // reset min value
    mDB.vcore.min = UINT32_MAX;
    mDB.acore.min = UINT32_MAX;
    mDB.wcore.min = UINT32_MAX;

    mDB.vsoc.min  = UINT32_MAX;
    mDB.asoc.min  = UINT32_MAX;
    mDB.wsoc.min  = UINT32_MAX;

    mDB.cdie.min  = UINT32_MAX;
    mDB.cctl.min  = UINT32_MAX;
    mDB.cccd0.min = UINT32_MAX;
    mDB.cccd1.min = UINT32_MAX;

    // point the sub-modules to the databases
    svi2_init(&mDB);
    load_init(&sDB);

    num_state = INIT;
}

void num_deinit(void) //------------------------------------------------------------------------------------- num_deinit
{
    // close file descriptors; technically the OS does this by itself, but it doesn't hurt doing it here
    if(NULL != mDB.vcore.FD) fclose(mDB.vcore.FD);
    if(NULL != mDB.acore.FD) fclose(mDB.acore.FD);

    if(NULL != mDB.vsoc.FD ) fclose(mDB.vsoc.FD);
    if(NULL != mDB.asoc.FD ) fclose(mDB.asoc.FD);

    if(NULL != mDB.cdie.FD ) fclose(mDB.cdie.FD);
    if(NULL != mDB.cctl.FD ) fclose(mDB.cctl.FD);
    if(NULL != mDB.cccd0.FD) fclose(mDB.cccd0.FD);
    if(NULL != mDB.cccd1.FD) fclose(mDB.cccd1.FD);

    if(NULL != sDB.mhzFD)    fclose(sDB.mhzFD);
    if(NULL != sDB.usgFD)    fclose(sDB.usgFD);
    if(NULL != sDB.ramFD)    fclose(sDB.ramFD);

    num_state = DEINIT;
}

statusType num_exportDB(metricsType** const outDB) //------------------------------------------------------ num_exportDB
{
    statusType status = NOK;

    if(INIT == num_state)
    {
        *outDB = &mDB; // let the dot drawing functions access the metrics database

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType num_getSvi2(void) //----------------------------------------------------------------------------- num_getSvi2
{
    statusType status = NOK;

    if(INIT == num_state)
    {
        (void)svi2_getStatus();
        (void)svi2_setMinMax();
        (void)svi2_setAvg();

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType num_getLoad(void) //----------------------------------------------------------------------------- num_getLoad
{
    statusType status = NOK;

    if(INIT == num_state)
    {
        (void)load_getCpuBar();

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType num_printSvi2(uint16 xPos, const uint16 yPos) //----------------------------------------------- num_printSvi2
{
    // these hardcoded positions depend on where the static labels are printed in zenmon-box.c

    statusType status = NOK;

    if(INIT == num_state)
    {
        (void)svi2_printTable(xPos, yPos + 2u);

        status = OK;
    }
    else
    {
        status = FEATURE_DISABLED;
    }

    return status;
}

statusType num_printLoad(const uint16 xPos, const uint16 yPos) //----------------------------------------- num_printLoad
{
    // these hardcoded positions depend on where the static labels are printed in zenmon-box.c

    statusType status = NOK;

    if(INIT == num_state)
    {
        (void)load_printSysInfo(xPos + 2u, yPos +  1u);
        (void)load_printRamBar( xPos + 2u, yPos +  7u);
        (void)load_printCpuBar( xPos + 2u, yPos + 11u);

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
static bool num_openFile(FILE** FD, const sint8* const name) //-------------------------------------------- num_openFile
{
    bool failure;

    if(-1 != access(name, F_OK))
    {
        *FD = fopen(name, "rb");
        failure = FALSE;
    }
    else
    {
        PRINT_FAIL("File %s%s%s not found", F_RED, name, F_RST);
        failure = TRUE;
    }

    return failure;
}

//======================================================================================================================
// END OF FILE
//======================================================================================================================
