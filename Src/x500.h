
#ifndef PANDAX500_X500_H
#define PANDAX500_X500_H

#include "helpers.h"
#include "stm32f0xx_hal.h"

void X500_Bell_Inc(TM16XX *display);

void X500_Bell_All(TM16XX *display);

void X500_Charge(bool on);

bool X500_Bell_Excluded(GPIO_TypeDef *port, uint32_t pin);

void X500_Right_Brush(bool on);

void X500_Left_Brush(bool on);

void X500_Main_Bus(bool on);

void X500_Right_Wheel(bool fwd);


//Testing

void X500_BatteryMon_Test(TM16XX *display, ADC_HandleTypeDef *adc);


#endif //PANDAX500_X500_H
