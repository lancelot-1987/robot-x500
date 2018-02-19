/*
TM16XX.h - Library for TM1638.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TM16XX_h
#define TM16XX_h


#include <stdint.h>
#include <stdbool.h>
#include "stm32f0xx_hal.h"

#define PORT_TYPE GPIO_TypeDef*

struct TM16XX {

    uint32_t dio;
    PORT_TYPE dioPort;
    uint32_t clk;
    PORT_TYPE clkPort;
    uint32_t stb;
    PORT_TYPE stbPort;
    const char *buffer;
    int bufferPosition;

};

extern void TM_Brightness(struct TM16XX *display, bool active, uint32_t intensity);

extern void TM_sendCommand(struct TM16XX* display, uint32_t led);

extern void TM_sendData(struct TM16XX* display, uint32_t add, uint32_t data);

extern void TM_send(struct TM16XX* display, uint32_t data);

extern void TM_clear(struct TM16XX* display);

extern void TM_Init(struct TM16XX* display, bool activateDisplay, uint32_t intensity);

extern void TM_Delay(long ms);

extern void TM_WritePin(PORT_TYPE port, uint32_t pin, uint32_t value);
#endif
