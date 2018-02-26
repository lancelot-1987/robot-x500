/*
pp - Library implementation for
Copyright (C) 2011 Ricardo Batista (rjbatista <at> gmail <dot> com)

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

#include "TM16XX.h"


#define HIGH GPIO_PIN_SET
#define LOW GPIO_PIN_RESET

static const int MAX_INTENSITY = 7;

void TM_Init(struct TM16XX *display, bool activateDisplay, uint32_t intensity) {
    TM_WritePin(display->stbPort, display->stb, HIGH);;
    TM_WritePin(display->clkPort, display->clk, HIGH);

    TM_sendCommand(display, 0x40);
    TM_sendCommand(display, 0x80 | (activateDisplay ? 8 : 0) | (intensity <= MAX_INTENSITY ? intensity : MAX_INTENSITY));

    TM_WritePin(display->stbPort, display->stb, LOW);;
    TM_send(display, 0xC0);
    TM_Clear(display);
    TM_WritePin(display->stbPort, display->stb, HIGH);;
}

void TM_Clear(struct TM16XX *display) {
    int i = 0;
    for (i = 0; i < 16; i++) {
        TM_send(display, 0x00);
    }
}

void TM_Brightness(struct TM16XX *display, bool active, uint32_t intensity) {
    TM_sendCommand(display, 0x80 | (active ? 8 : 0) | (intensity <= MAX_INTENSITY ? intensity : MAX_INTENSITY));

    // necessary for the TM1640
    TM_WritePin(display->stbPort, display->stb, LOW);
    TM_WritePin(display->clkPort, display->clk, LOW);
    TM_WritePin(display->clkPort, display->clk, HIGH);
    TM_WritePin(display->stbPort, display->stb, HIGH);
}

void TM_sendCommand(struct TM16XX *display, uint32_t cmd) {
    TM_WritePin(display->stbPort, display->stb, LOW);
    TM_send(display, cmd);
    TM_WritePin(display->stbPort, display->stb, HIGH);
}

void TM_sendData(struct TM16XX *display, uint32_t address, uint32_t data) {
    TM_sendCommand(display, 0x44);
    TM_WritePin(display->stbPort, display->stb, LOW);
    TM_send(display, 0xC0 | address);
    TM_send(display, data);
    TM_WritePin(display->stbPort, display->stb, HIGH);
}

void TM_send(struct TM16XX *display, uint32_t data) {
    int i;
    for (i = 0; i < 8; i++) {
        TM_WritePin(display->clkPort, display->clk, LOW);
        TM_WritePin(display->dioPort, display->dio, data & 1 ? HIGH : LOW);
        data >>= 1;
        TM_WritePin(display->clkPort, display->clk, HIGH);
    }
}

void TM_WritePin(PORT_TYPE port, uint32_t pin, uint32_t value) {
    HAL_GPIO_WritePin(port, pin, value);
}

void TM_Delay(long ms) {
    HAL_Delay(ms);
}


