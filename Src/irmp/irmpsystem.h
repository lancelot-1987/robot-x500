/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmpsystem.h - system specific includes and defines
 *
 * Copyright (c) 2009-2016 Frank Meyer - frank(at)fli4l.de
 *
 * $Id: irmpsystem.h,v 1.26 2017/08/25 12:24:18 fm Exp $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */

#ifndef _IRMPSYSTEM_H_
#define _IRMPSYSTEM_H_
#define STM32F0 1
#if !defined(_IRMP_H_) && !defined(_IRSND_H_)
#  error please include only irmp.h or irsnd.h, not irmpsystem.h
#endif

#include <stm32f0xx.h>

#  define ARM_STM32
#  define ARM_STM32F0XX
#  define F_CPU (HAL_RCC_GetSysClockFreq())
#  define PROGMEM
#  define memcpy_P                      memcpy

#include <string.h>


#ifndef TRUE
#  define TRUE                          1
#  define FALSE                         0
#endif

#define IRMP_PACKED_STRUCT              __attribute__ ((__packed__))

typedef struct {
    uint_fast8_t protocol;                                                // ir protocol
    uint_fast8_t pulse_1_len_min;                                         // minimum length of pulse with bit value 1
    uint_fast8_t pulse_1_len_max;                                         // maximum length of pulse with bit value 1
    uint_fast8_t pause_1_len_min;                                         // minimum length of pause with bit value 1
    uint_fast8_t pause_1_len_max;                                         // maximum length of pause with bit value 1
    uint_fast8_t pulse_0_len_min;                                         // minimum length of pulse with bit value 0
    uint_fast8_t pulse_0_len_max;                                         // maximum length of pulse with bit value 0
    uint_fast8_t pause_0_len_min;                                         // minimum length of pause with bit value 0
    uint_fast8_t pause_0_len_max;                                         // maximum length of pause with bit value 0
    uint_fast8_t address_offset;                                          // address offset
    uint_fast8_t address_end;                                             // end of address
    uint_fast8_t command_offset;                                          // command offset
    uint_fast8_t command_end;                                             // end of command
    uint_fast8_t complete_len;                                            // complete length of frame
    uint_fast8_t stop_bit;                                                // flag: frame has stop bit
    uint_fast8_t lsb_first;                                               // flag: LSB first
    uint_fast8_t flags;                                                   // some flags
} IRMP_PARAMETER;


typedef struct IRMP_PACKED_STRUCT {
    uint8_t protocol;                                   // protocol, e.g. NEC_PROTOCOL
    uint16_t address;                                    // address
    uint16_t command;                                    // command
    uint8_t flags;                                      // flags, e.g. repetition
} IRMP_DATA;


typedef struct {
    uint_fast8_t irmp_bit;                   // current bit position
    IRMP_PARAMETER irmp_param;

    IRMP_PARAMETER irmp_param2;

    uint_fast8_t irmp_ir_detected;
    uint_fast8_t irmp_protocol;
    uint_fast16_t irmp_address;
    uint_fast16_t irmp_command;
    uint_fast16_t irmp_id;                // only used for SAMSUNG protocol
    uint_fast8_t irmp_flags;

     uint_fast16_t irmp_tmp_address;                                      // ir address
     uint_fast16_t irmp_tmp_command;                                      // ir command

     uint_fast16_t irmp_tmp_address2;                                     // ir address
     uint_fast16_t irmp_tmp_command2;                                     // ir command

     uint_fast16_t irmp_lgair_address;                                    // ir address
     uint_fast16_t irmp_lgair_command;                                    // ir command

     uint_fast16_t irmp_tmp_id;                                           // ir id (only SAMSUNG)
     uint8_t xor_check[6];                                           // check kaseikyo "parity" bits
     uint_fast8_t genre2;                                                 // save genre2 bits here, later copied to MSB in flags
     uint_fast8_t parity;                                                // number of '1' of the first 14 bits, check if even.

     uint_fast8_t check;                                                 // number of '1' of the first 14 bits, check if even.
     uint_fast8_t mitsu_parity;                                          // number of '1' of the first 14 bits, check if even.
} IRMP_STATE;


#endif // _IRMPSYSTEM_H_
