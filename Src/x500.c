
#include "stm32f0xx_hal.h"
#include "tm1628/Display.h"
#include "x500.h"
GPIO_TypeDef *ports[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF};
int PORTS_SIZE = 6;
uint32_t pins[] = {
        GPIO_PIN_0,
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4,
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_7,
        GPIO_PIN_8,
        GPIO_PIN_9,
        GPIO_PIN_10,
        GPIO_PIN_11,
        GPIO_PIN_12,
        GPIO_PIN_13,
        GPIO_PIN_14,
        GPIO_PIN_15
};
int PINS_SIZE = 16;

bool X500_Bell_Excluded(GPIO_TypeDef *port, uint32_t pin) {
    const int SIZE = 11;
    //TODO: get rid of such size calculation
    struct PortPinTuple excluded[] = {
            {.port = GPIOA, .pin = GPIO_PIN_13}, //SWDIO
            {.port = GPIOA, .pin = GPIO_PIN_14}, //SWCLK
            {.port = GPIOA, .pin = GPIO_PIN_6},  //MAIN_BUS
            //Display
            {.port = DISPLAY_DIO_GPIO_Port, .pin = DISPLAY_DIO_Pin},
            {.port = DISPLAY_CLK_GPIO_Port, .pin = DISPLAY_CLK_Pin},
            {.port = DISPLAY_STB_GPIO_Port, .pin = DISPLAY_STB_Pin},
            //Display buttons
            {.port = DISPLAY_HOME_GPIO_Port, .pin = DISPLAY_HOME_Pin},
            {.port = DISPLAY_CLEAN_GPIO_Port, .pin = DISPLAY_CLEAN_Pin},
            {.port = DISPLAY_PLAN_GPIO_Port, .pin = DISPLAY_PLAN_Pin},
            {.port = DISPLAY_SPOT_GPIO_Port, .pin = DISPLAY_SPOT_Pin},
            //Charging
            {.port = CHARGE_ON_GPIO_Port, .pin = CHARGE_ON_Pin},
    };
    for (int i = 0; i < SIZE; i++) {
        if (port == excluded[i].port && pin == excluded[i].pin) {
            return true;
        }
    }
    return false;
}


void X500_Bell_Inc(struct TM16XX *display) {
    GPIO_InitTypeDef GPIO_InitStruct;
    for (int i = 0; i < PORTS_SIZE; ++i) {
        for (int j = 0; j < PINS_SIZE; ++j) {
            if (X500_Bell_Excluded(ports[i], pins[j])) {
                continue;
            }
            GPIO_InitStruct.Pin = pins[j];
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            HAL_GPIO_Init(ports[i], &GPIO_InitStruct);
        }
    }
    int i = 0;
    int j = 0;

    while (1) {
        const GPIO_PinState pinup = HAL_GPIO_ReadPin(DISPLAY_PLAN_GPIO_Port, DISPLAY_PLAN_Pin);
        const GPIO_PinState pindown = HAL_GPIO_ReadPin(DISPLAY_SPOT_GPIO_Port, DISPLAY_SPOT_Pin);
        const GPIO_PinState portup = HAL_GPIO_ReadPin(DISPLAY_CLEAN_GPIO_Port, DISPLAY_CLEAN_Pin);
        const GPIO_PinState portdown = HAL_GPIO_ReadPin(DISPLAY_HOME_GPIO_Port, DISPLAY_HOME_Pin);

        if (pindown == GPIO_PIN_SET) {
            j++;
        }
        if (pinup == GPIO_PIN_SET) {
            j--;
        }
        if (portup == GPIO_PIN_SET) {
            i--;
        }
        if (portdown == GPIO_PIN_SET) {
            i++;
        }

        if (i > PORTS_SIZE - 1) {
            i = PORTS_SIZE - 1;
        }
        if (i < 0) {
            i = 0;
        }
        if (j < 0) {
            j = 0;
        }

        if (j > PINS_SIZE - 1) {
            j = PINS_SIZE - 1;
        }

        if (X500_Bell_Excluded(ports[i], pins[j])) {
            continue;
        }
        TM_Ext_ClearText(display);
        TM_Ext_Hours(display, i, true);
        TM_Ext_Minutes(display, j, true);

        HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_RESET);
        HAL_Delay(100);
    }
}
void X500_Bell_All(struct TM16XX *display) {
    GPIO_InitTypeDef GPIO_InitStruct;
    for (int i = 0; i < PORTS_SIZE; ++i) {
        for (int j = 0; j < PINS_SIZE; ++j) {
            if (X500_Bell_Excluded(ports[i], pins[j])) {
                continue;
            }
            GPIO_InitStruct.Pin = pins[j];
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            HAL_GPIO_Init(ports[i], &GPIO_InitStruct);
        }
    }
    while (1) {
        for (int i = 0; i < PORTS_SIZE; ++i) {
            for (int j = 0; j < PINS_SIZE; ++j) {

                if (X500_Bell_Excluded(ports[i], pins[j])) {
                    continue;
                }
                TM_Ext_ClearText(display);
                TM_Ext_Hours(display, i, true);
                TM_Ext_Minutes(display, j, true);

                for (int k = 0; k < 30; ++k) {
                    HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_SET);
                    HAL_Delay(50);
                    HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_RESET);
                    HAL_Delay(50);
                }
            }
        }
    }
}

void X500_Charge(bool on) {
    HAL_GPIO_WritePin(CHARGE_ON_GPIO_Port, CHARGE_ON_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void X500_Main_Bus(bool on) { HAL_GPIO_WritePin(MAIN_BUS_GPIO_Port, MAIN_BUS_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET); }

void X500_Left_Brush(bool on) { HAL_GPIO_WritePin(LEFT_BRUSH_GPIO_Port, LEFT_BRUSH_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET); }

void X500_Right_Brush(bool on) { HAL_GPIO_WritePin(RIGHT_BRUSH_GPIO_Port, RIGHT_BRUSH_Pin, on ? GPIO_PIN_SET : GPIO_PIN_RESET); }

void X500_Right_Wheel(bool fwd) { HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, fwd ? GPIO_PIN_SET : GPIO_PIN_RESET); }

//Testing

void X500_BatteryMon_Test(struct TM16XX *display, ADC_HandleTypeDef *adc) {
    while (1) {
        int max = 100;
        uint32_t value = 0;
        float voltage = 0;
        for (int i = 0; i < max; ++i) {
            HAL_ADC_Start(adc);
            if (HAL_ADC_PollForConversion(adc, 1000) == HAL_OK) {
                value = HAL_ADC_GetValue(adc);
            }
            HAL_ADC_Stop(adc);
        }
        value = (uint32_t)(value * 2) * 3300 / 0xfff;
        voltage =  (float)(value / 10.0);
        TM_Ext_ClearText(display);
        TM_Ext_Hours(display, voltage / 100, true);
        TM_Ext_Minutes(display, (int)voltage % 100, true);
        HAL_Delay(1000);
    }
}
