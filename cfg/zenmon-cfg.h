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
#define LEN_PLOT_D_X    120u                          // graph X size in Braille dots; multiple of 2
#define LEN_PLOT_D_Y     20u                          // graph Y size in Braille dots; multiple of 4
#define LEN_PLOT_C_X   (LEN_PLOT_D_X / 2u)            // graph X size in characters
#define LEN_PLOT_C_Y   (LEN_PLOT_D_Y / 4u)            // graph Y size in characters
#define LEN_PLOT_BUF   (LEN_PLOT_C_X * LEN_PLOT_C_Y)

// electrical graphs window size; 3 stacked graphs: core mV, A and W
#define LEN_ELEC_W_X  ((LEN_PLOT_D_X / 2u     ) + 4u) // X size in characters
#define LEN_ELEC_W_Y  ((LEN_PLOT_D_Y / 4u * 3u) + 2u) // Y size in characters

// temperature graphs windows size; 4 stacked graphs: die, ctl, ccd0 and ccd1 temperatures
#define LEN_TEMP_W_X  ((LEN_PLOT_D_X / 2u     ) + 4u) // X size in characters
#define LEN_TEMP_W_Y  ((LEN_PLOT_D_Y / 4u * 4u) + 2u) // Y size in characters

// total display space used; based on the current layout and is used to center the content to the terminal window
#define LEN_TOTAL_W_X  (LEN_SVI2_W_X + LEN_TEMP_W_X)  // X size in characters
#define LEN_TOTAL_W_Y  (LEN_SVI2_W_Y + LEN_TEMP_W_Y)  // Y size in characters

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
