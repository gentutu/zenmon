// Copyright (C) 2020 Denis Isai

#ifndef ZENMON_NUM_H
#define ZENMON_NUM_H

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// generic includes
#include "gen-types.h"

// local includes
#include "zenmon-types.h"

//======================================================================================================================
// API DECLARATIONS
//======================================================================================================================
// management
void       num_init(void);
void       num_deinit(void);
statusType num_exportDB(metricsType** const outDB);

// getters
statusType num_getSvi2(void);
statusType num_getLoad(void);

// printers
statusType num_printSvi2(      uint16 xPos, const uint16 yPos);
statusType num_printLoad(const uint16 xPos, const uint16 yPos);

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
