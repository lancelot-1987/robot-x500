
#ifndef PANDAX500_WTV_H
#define PANDAX500_WTV_H

#include "stm32f0xx_hal.h"

#define CMD_SHUTDOWN 0xF0
#define CMD_OPEN 0xF1
#define CMD_PLAY_CYCLE 0xF2
#define CMD_STOP 0xFE
#define CMD_VOLUME_MIN 0xE0
#define CMD_VOLUME_MAX 0xEF

#define CMD_PLS_SELECT_MODE 0
#define CMD_CLEAN_DUST 2
#define CMD_CHECK_DRIVING_WHEEL 3
#define CMD_CHECK_SIDEBRUSH 4
#define CMD_CHARGING_START 5
#define CMD_CHARGING_FINSIHED 6
#define CMD_BELL_SHORT 10
#define CMD_BELL1 11
#define CMD_BELL2 12
#define CMD_BELL2_REVERSE 13
#define CMD_BELL3_REVERSE 14
#define CMD_TICK 15




void WTV040_Cmd(uint32_t data);
void WTV040_OpenAmp();
void WTV040_ShutdownAmp();
void WTV040_Cycle();
void WTV040_Stop();
void WTV040_Volume(uint32_t level);

#endif //PANDAX500_WTV_H
