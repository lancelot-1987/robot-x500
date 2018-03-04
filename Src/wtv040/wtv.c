#include "wtv.h"

void WTV040_Cmd(uint32_t data, WTV040 *chip) {
  HAL_GPIO_Reset(chip->Reset);
  HAL_Delay(5);
  HAL_GPIO_Set(chip->Reset);
  HAL_Delay(5);
  HAL_GPIO_Reset(chip->Data);
  HAL_Delay(5);
  for (int i = 0; i < 8; i++) {
    HAL_GPIO_Set(chip->Data);
    if (data & 1) {
      HAL_Delay(3);
      HAL_GPIO_Reset(chip->Data);
      HAL_Delay(1);
    } else {
      HAL_Delay(1);
      HAL_GPIO_Reset(chip->Data);
      HAL_Delay(3);
    }
    data >>= 1;
  }
  HAL_GPIO_Set(chip->Data);
  HAL_Delay(1);
}

void WTV040_OpenAmp(WTV040 *chip) {
  WTV040_Cmd(CMD_OPEN, chip);
}

void WTV040_ShutdownAmp(WTV040 *chip) {
  WTV040_Cmd(CMD_SHUTDOWN, chip);
}

void WTV040_Cycle(WTV040 *chip) {
  WTV040_Cmd(CMD_PLAY_CYCLE, chip);
}

void WTV040_Stop(WTV040 *chip) {
  WTV040_Cmd(CMD_STOP, chip);
}

void WTV040_Volume(uint32_t level, WTV040 *chip) {
  uint32_t addr = CMD_VOLUME_MIN + level;
  if (addr < CMD_VOLUME_MIN) {
    addr = CMD_VOLUME_MIN;
  }
  if (addr > CMD_VOLUME_MAX) {
    addr = CMD_VOLUME_MAX;
  }
  WTV040_Cmd(addr, chip);
}



