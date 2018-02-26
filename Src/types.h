
#ifndef PANDAX500_TYPES_H
#define PANDAX500_TYPES_H
#include "stm32f0xx_hal.h"
struct PortPinTuple {
    GPIO_TypeDef *port;
    __uint32_t pin;
};
#endif //PANDAX500_TYPES_H
