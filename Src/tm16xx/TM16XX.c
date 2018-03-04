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

static const int MAX_INTENSITY = 7;

void TM_Init(TM16XX *display, bool activateDisplay, uint32_t intensity) {
  HAL_GPIO_Set(display->Stb);
  HAL_GPIO_Set(display->Clk);
  TM_sendCommand(display, 0x40);
  TM_sendCommand(display, 0x80 | (activateDisplay ? 8 : 0) | (intensity <= MAX_INTENSITY ? intensity : MAX_INTENSITY));
  HAL_GPIO_Reset(display->Stb);
  TM_send(display, 0xC0);
  TM_Clear(display);
  HAL_GPIO_Set(display->Stb);
}

void TM_Clear(TM16XX *display) {
  int i = 0;
  for (i = 0; i < 16; i++) {
    TM_send(display, 0x00);
  }
}

void TM_Brightness(TM16XX *display, bool active, uint32_t intensity) {
  TM_sendCommand(display, 0x80 | (active ? 8 : 0) | (intensity <= MAX_INTENSITY ? intensity : MAX_INTENSITY));
  // necessary for the TM1640
  HAL_GPIO_Reset(display->Stb);
  HAL_GPIO_Reset(display->Clk);
  HAL_GPIO_Set(display->Clk);
  HAL_GPIO_Set(display->Stb);
}

void TM_sendCommand(TM16XX *display, uint32_t cmd) {
  HAL_GPIO_Reset(display->Stb);
  TM_send(display, cmd);
  HAL_GPIO_Set(display->Stb);
}

void TM_sendData(TM16XX *display, uint32_t address, uint32_t data) {
  TM_sendCommand(display, 0x44);
  HAL_GPIO_Reset(display->Stb);
  TM_send(display, 0xC0 | address);
  TM_send(display, data);
  HAL_GPIO_Set(display->Stb);
}

void TM_send(TM16XX *display, uint32_t data) {
  int i;
  for (i = 0; i < 8; i++) {
    HAL_GPIO_Reset(display->Clk);
    if (data & 1) {
      HAL_GPIO_Set(display->Dio);
    } else {
      HAL_GPIO_Reset(display->Dio);
    }
    data >>= 1;
    HAL_GPIO_Set(display->Clk);
  }
}

void TM_Delay(long ms) {
  HAL_Delay(ms);
}


