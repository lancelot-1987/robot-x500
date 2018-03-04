
#ifndef PANDAX500_TYPES_H
#define PANDAX500_TYPES_H

#include "stm32f0xx_hal.h"

typedef struct {
    GPIO_TypeDef *Port;
    uint16_t Pin;
} PortPinTuple;

void HAL_GPIO_Set(PortPinTuple tuple);
void HAL_GPIO_Reset(PortPinTuple tuple);

#endif //PANDAX500_TYPES_H
