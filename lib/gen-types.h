// Copyright (C) 2020 Denis Isai

#ifndef GEN_TYPES_H
#define GEN_TYPES_H

//======================================================================================================================
// DEFINES
//======================================================================================================================
// logic defines
#ifndef TRUE
#define TRUE     1
#endif
#ifndef FALSE
#define FALSE    0
#endif
#ifndef YES
#define YES      1
#endif
#ifndef NO
#define NO       0
#endif
#ifndef ON
#define ON       1
#endif
#ifndef OFF
#define OFF      0
#endif
#ifndef ENABLED
#define ENABLED  1
#endif
#ifndef DISABLED
#define DISABLED 0
#endif

// text format
#define F_UND "\033[4m"
#define F_BLD "\033[1m"
#define F_RST "\033[0m"

#define F_BLK "\e[0;30m"
#define F_RED "\e[0;31m"
#define F_GRN "\e[0;32m"
#define F_YEL "\e[0;33m"
#define F_BLU "\e[0;34m"
#define F_MAG "\e[0;35m"
#define F_CYN "\e[0;36m"
#define F_WHT "\e[0;37m"

// terminal management
#define CURSOR_HIDE             printf("\e[?25l")
#define CURSOR_SHOW             printf("\e[?25h")
#define CURSOR_JUMP(yPos, xPos) printf("\033[%d;%dH", yPos, xPos)
#define CLEAR_SCREEN            printf("\e[1;1H\e[2J")
#define TERM_NAME(name)         printf("\033]0;%s\007", name)

// jump cursor and print
#define PRINTL(xPos, yPos, ...) do { CURSOR_JUMP(yPos, xPos); printf(__VA_ARGS__); printf("%s", F_RST); } while(0)

// bit manipulation
#define GETBIT(num, pos)             (((num) & (  0x01 << (pos))) ? 1 : 0)
#define SETBIT(num, pos)              ((num) | (  0x01 << (pos)))
#define CLRBIT(num, pos)              ((num) & (~(0x01 << (pos))))
#define TGLBIT(num, pos)              ((num) ^ (  0x01 << (pos)))

#define GETNIBBLE(num, pos)         ((((num) & (  0x0F << ((pos) * 4))))              >> ((pos) * 4))
#define SETNIBBLE(num, pos, nibble) ((((num) & (~(0x0F << ((pos) * 4))))) | ((nibble) << ((pos) * 4)))
#define CLRNIBBLE(num, pos)          (((num) & (~(0x0F << ((pos) * 4)))))
#define TGLNIBBLE(num, pos)         ((((num) ^ (  0x0F << ((pos) * 4)))))

#define GETBYTE(num, pos)           ((((num) & (  0xFF << ((pos) * 8)))            >> ((pos) * 8)))
#define SETBYTE(num, pos, byte)      (((num) & (~(0xFF << ((pos) * 8)))) | ((byte) << ((pos) * 8)))
#define CLRBYTE(num, pos)            (((num) & (~(0xFF << ((pos) * 8)))))
#define TGLBYTE(num, pos)           ((((num) ^ (  0xFF << ((pos) * 8)))))

// others
#define GETMAX(num1, num2)           (((num1) > (num2)) ? (num1) : (num2))
#define GETMIN(num1, num2)           (((num1) < (num2)) ? (num1) : (num2))

//======================================================================================================================
// TYPES
//======================================================================================================================
#define  UINT8_MIN                    0u
#define UINT16_MIN                    0u
#define UINT32_MIN                    0u
#define UINT64_MIN                    0u

#define  UINT8_MAX                  255u
#define UINT16_MAX                65535u
#define UINT32_MAX           4294967295u
#define UINT64_MAX 18446744073709551615u

#define  SINT8_MIN                 -128
#define SINT16_MIN               -32768
#define SINT32_MIN          -2147483648
#define SINT64_MIN -9223372036854775808

#define  SINT8_MAX                  127
#define SINT16_MAX                32767
#define SINT32_MAX           2147483647
#define SINT64_MAX  9223372036854775807

// these are platform-dependant
typedef unsigned         char   uint8; //                          0 ...                        255
typedef unsigned short    int  uint16; //                          0 ...                     65.535
typedef unsigned          int  uint32; //                          0 ...              4.294.967.295
typedef unsigned  long    int  uint64; //                          0 ... 18.446.744.073.709.551.615

typedef   signed         char   sint8; //                       -128 ...                       +127
typedef   signed short    int  sint16; //                    -32.768 ...                    +32.767
typedef   signed          int  sint32; //             -2.147.483.648 ...             +2.147.483.647
typedef   signed  long    int  sint64; // -9.223.372.036.854.775.808 ... +9.223.372.036.854.775.807

typedef                 float float32; //                   1.2E-38  ... 3.4E+38       (6 decimals)
typedef                double float64; //                   2.3E-308 ... 1.7E+308     (15 decimals)

typedef unsigned         char    bool; //                          0 ...                        255

typedef enum statusTypeTag
{
    OK,
    NOK
} statusType;

//======================================================================================================================
// END OF FILE
//======================================================================================================================

#endif
