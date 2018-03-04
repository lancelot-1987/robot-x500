#include "helpers.h"

void HAL_GPIO_Set(PortPinTuple tuple) {
  HAL_GPIO_WritePin(tuple.Port, tuple.Pin, GPIO_PIN_SET);
}

void HAL_GPIO_Reset(PortPinTuple tuple) {
  HAL_GPIO_WritePin(tuple.Port, tuple.Pin, GPIO_PIN_RESET);
}


