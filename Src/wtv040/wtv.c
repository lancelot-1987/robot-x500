#include "wtv.h"

void WTV040_Cmd(uint32_t data) {
    //TODO: separate audio chip to the structure, change signature
    HAL_GPIO_WritePin(AUDIO_RESET_GPIO_Port, AUDIO_RESET_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(AUDIO_RESET_GPIO_Port, AUDIO_RESET_Pin, GPIO_PIN_SET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(AUDIO_DATA_GPIO_Port, AUDIO_DATA_Pin, GPIO_PIN_RESET);
    HAL_Delay(5);
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(AUDIO_DATA_GPIO_Port, AUDIO_DATA_Pin, GPIO_PIN_SET);
        if (data & 1) {
            HAL_Delay(3);
            HAL_GPIO_WritePin(AUDIO_DATA_GPIO_Port, AUDIO_DATA_Pin, GPIO_PIN_RESET);
            HAL_Delay(1);
        } else {
            HAL_Delay(1);
            HAL_GPIO_WritePin(AUDIO_DATA_GPIO_Port, AUDIO_DATA_Pin, GPIO_PIN_RESET);
            HAL_Delay(3);
        }
        data >>= 1;
    }
    HAL_GPIO_WritePin(AUDIO_DATA_GPIO_Port, AUDIO_DATA_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
}

void WTV040_OpenAmp() {
    WTV040_Cmd(CMD_OPEN);
}

void WTV040_ShutdownAmp() {
    WTV040_Cmd(CMD_SHUTDOWN);
}

void WTV040_Cycle() {
    WTV040_Cmd(CMD_PLAY_CYCLE);
}

void WTV040_Stop() {
    WTV040_Cmd(CMD_STOP);
}

void WTV040_Volume(uint32_t level) {
    uint32_t addr = CMD_VOLUME_MIN + level;
    if (addr < CMD_VOLUME_MIN) {
        addr = CMD_VOLUME_MIN;
    }
    if (addr > CMD_VOLUME_MAX) {
        addr = CMD_VOLUME_MAX;
    }
    WTV040_Cmd(addr);
}



