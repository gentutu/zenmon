// Copyright (C) 2020 Denis Isai

#ifndef ZENMON_CFG_SVI2_H
#define ZENMON_CFG_SVI2_H

//======================================================================================================================
// DEFINES
//======================================================================================================================
// file paths; these are checked at runtime and if any are missing the program will notify and exit
#define FILE_VCORE   "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/in1_input"   // core voltage
#define FILE_ACORE   "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/curr1_input" // core current
#define FILE_VSOC    "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/in2_input"   // soc  voltage
#define FILE_ASOC    "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/curr2_input" // soc  current
#define FILE_CDIE    "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/temp1_input" // core temperature
#define FILE_CCTL    "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/temp2_input" // ctl  temperature
#define FILE_CCCD0   "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/temp3_input" // ccd0 temperature
#define FILE_CCCD1   "/sys/devices/pci0000:00/0000:00:18.3/hwmon/hwmon1/temp4_input" // ccd1 temperature

// svi2 window size
#define LEN_SVI2_W_X    47u // X size in characters
#define LEN_SVI2_W_Y    14u // Y size in characters

// static config
#define AVG_CYCLES      10u // measurements until average is displayed

// graph scales and alarm thresholds; these numbers depend of the definitions of graph sizes from zenmon-cfg.h
#define C_D_VALUE        5u // each Braille dot represents 5 °C; 0 - 100 scale
#define LIM_C           60u // °C; multiple of (C_D_VALUE * LEN_PLOT_D_Y); see zenmon-cfg.h

#define V_D_VALUE       75u // each Braille dot represents 75 millivolts; 0 - 1500 scale
#define LIM_V         1200u // millivolts; multiple of (V_D_VALUE * LEN_PLOT_D_Y); see zenmon-cfg.h

#define A_D_VALUE        8u // each Braille dot represents 8 amperes; 0 - 160 scale
#define LIM_A          128u // amperes; multiple of (A_D_VALUE * LEN_PLOT_D_Y); see zenmon-cfg.h

#define W_D_VALUE       10u // each Braille dot represents 10 watts; 0 - 200 scale
#define LIM_W          160u // watts; multiple of (W_D_VALUE * LEN_PLOT_D_Y); see zenmon-cfg.h

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
