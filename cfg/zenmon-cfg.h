// Copyright (C) 2020 Denis Isai

#ifndef ZENMON_CFG_H
#define ZENMON_CFG_H

//======================================================================================================================
// INCLUDES
//======================================================================================================================
// module includes
#include "zenmon-cfg-svi2.h"
#include "zenmon-cfg-load.h"

//======================================================================================================================
// DEFINES
//======================================================================================================================
// graph sizes in dots and characters
#define LEN_GR_D_X       120u                        // graph X size in Braille dots; multiple of 2
#define LEN_GR_D_Y       20u                         // graph Y size in Braille dots; multiple of 4
#define LEN_GR_C_X       (LEN_GR_D_X / 2u)           // graph X size in characters
#define LEN_GR_C_Y       (LEN_GR_D_Y / 4u)           // graph Y size in characters
#define LEN_GR_BUF       (LEN_GR_C_X * LEN_GR_C_Y)

// svi2 window size
#define LEN_SVI2_W_X     47u                         // X size in characters
#define LEN_SVI2_W_Y     14u                         // Y size in characters

// load window size
#define LEN_LOAD_W_X     47u                         // X size in characters
#define LEN_LOAD_W_Y     25u                         // Y size in characters

// electrical graphs window size; 3 stacked graphs: core mV, A and W
#define LEN_EG_W_X       (LEN_GR_D_X / 2u     ) + 4u // X size in characters
#define LEN_EG_W_Y       (LEN_GR_D_Y / 4u * 3u) + 2u // Y size in characters

// temperature graphs windows size; 4 stacked graphs: die, ctl, ccd0 and ccd1 temperatures
#define LEN_CG_W_X       (LEN_GR_D_X / 2u     ) + 4u // X size in characters
#define LEN_CG_W_Y       (LEN_GR_D_Y / 4u * 4u) + 2u // Y size in characters

// these are based on the current layout and is used to center the content to the terminal window
#define LEN_TOTAL_W_X    (LEN_SVI2_W_X + LEN_CG_W_X)
#define LEN_TOTAL_W_Y    (LEN_SVI2_W_Y + LEN_CG_W_Y)

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
