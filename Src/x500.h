
#ifndef PANDAX500_X500_H
#define PANDAX500_X500_H

#include "types.h"
#include "stm32f0xx_hal.h"

void X500_Bell_Inc(struct TM16XX *display);

void X500_Bell_All(struct TM16XX *display);

void X500_Charge(bool on);

bool X500_Bell_Excluded(GPIO_TypeDef *port, uint32_t pin);

void X500_Right_Brush(bool on);

void X500_Left_Brush(bool on);

void X500_Main_Bus(bool on);

void X500_Right_Wheel(bool fwd);

void X500_Audio_Cmd(uint32_t data);


//Testing

void X500_BatteryMon_Test(struct TM16XX *display, ADC_HandleTypeDef *adc);


#endif //PANDAX500_X500_H
