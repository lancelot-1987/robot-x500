/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */

#include "tm1628/Display.h"

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* Private variables ---------------------------------------------------------*/



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* Private function prototypes -----------------------------------------------*/



/* USER CODE END PFP */

/* USER CODE BEGIN 0 */



void bell(struct TM16XX *display);

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */



  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */



  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */



  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC_Init();

  /* USER CODE BEGIN 2 */

    setPWM(htim16, TIM_CHANNEL_ALL, 255, 10);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */



    struct TM16XX display;

    display.dioPort = DISPLAY_DIO_GPIO_Port;
    display.dio = DISPLAY_DIO_Pin;
    display.clkPort = DISPLAY_CLK_GPIO_Port;
    display.clk = DISPLAY_CLK_Pin;
    display.stbPort = DISPLAY_STB_GPIO_Port;
    display.stb = DISPLAY_STB_Pin;


    TM_Init(&display, true, 8);
    TM_Brightness(&display, true, 7);
    TM_clear(&display);


    __HAL_RCC_SYSCFG_CLK_ENABLE();


    bell(&display);



    /* USER CODE END 3 */



}

void bell(struct TM16XX *display) {
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
    //PA13, PA14 to exclude
    GPIO_InitTypeDef GPIO_InitStruct;

//    for (int i = 0; i < PORTS_SIZE; ++i) {
//        for (int j = 0; j < PINS_SIZE; ++j) {
//            if ((ports[i] == GPIOA && pins[j] == GPIO_PIN_13) || (ports[i] == GPIOA && pins[j] == GPIO_PIN_14)) {
//                continue;
//            }
//            GPIO_InitStruct.Pin = pins[j];
//            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//            GPIO_InitStruct.Pull = GPIO_NOPULL;
//            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//            HAL_GPIO_Init(ports[i], &GPIO_InitStruct);
//
//        }
//    }


    GPIO_InitStruct.Pin = DISPLAY_PLAN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DISPLAY_PLAN_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DISPLAY_CLEAN_Pin;
    HAL_GPIO_Init(DISPLAY_CLEAN_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DISPLAY_SPOT_Pin;
    HAL_GPIO_Init(DISPLAY_SPOT_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DISPLAY_HOME_Pin;
    HAL_GPIO_Init(DISPLAY_HOME_GPIO_Port, &GPIO_InitStruct);

    TM_Ext_ClearText(display);
    TM_Ext_Line(display, "JORA");

    //brushes
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
//
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
//
//    //1-4, 4-3,
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    int i = 0;
    int j = 0;

//    while (1) {
//        const GPIO_PinState pinup = HAL_GPIO_ReadPin(DISPLAY_PLAN_GPIO_Port, DISPLAY_PLAN_Pin);
//        const GPIO_PinState pindown = HAL_GPIO_ReadPin(DISPLAY_SPOT_GPIO_Port, DISPLAY_SPOT_Pin);
//        const GPIO_PinState portup = HAL_GPIO_ReadPin(DISPLAY_CLEAN_GPIO_Port, DISPLAY_CLEAN_Pin);
//        const GPIO_PinState portdown = HAL_GPIO_ReadPin(DISPLAY_HOME_GPIO_Port, DISPLAY_HOME_Pin);
//
//        if (pindown == GPIO_PIN_SET) {
//            j++;
//        }
//        if (pinup == GPIO_PIN_SET) {
//            j--;
//        }
//        if (portup == GPIO_PIN_SET) {
//            i--;
//        }
//        if (portdown == GPIO_PIN_SET) {
//            i++;
//        }
//
//        if (i > PORTS_SIZE - 1) {
//            i = PORTS_SIZE - 1;
//        }
//        if (i < 0) {
//            i = 0;
//        }
//        if (j < 0) {
//            j = 0;
//        }
//
//        if (j > PINS_SIZE - 1) {
//            j = PINS_SIZE - 1;
//        }
//
//
//        if ((ports[i] == GPIOA && pins[j] == GPIO_PIN_13) || (ports[i] == GPIOA && pins[j] == GPIO_PIN_14)
//
//                ) {
//            continue;
//        }
//        TM_Ext_ClearText(display);
//        TM_Ext_Hours(display, i, true);
//        TM_Ext_Minutes(display, j, true);
//
//        HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_SET);
//        HAL_Delay(50);
//        HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_RESET);
//        HAL_Delay(50);
//
//
//    }

//    while (1) {
//        for (int i = 0; i < PORTS_SIZE; ++i) {
//            for (int j = 0; j < PINS_SIZE; ++j) {
//                if ((ports[i] == GPIOA && pins[j] == GPIO_PIN_13) || (ports[i] == GPIOA && pins[j] == GPIO_PIN_14)
//
//
//                        ) {
//                    continue;
//                }
//                TM_Ext_ClearText(display);
//                TM_Ext_Hours(display, i, true);
//                TM_Ext_Minutes(display, j, true);
//
//                for (int k = 0; k < 10; ++k) {
//                    HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_SET);
//                    HAL_Delay(50);
//                    HAL_GPIO_WritePin(ports[i], pins[j], GPIO_PIN_RESET);
//                    HAL_Delay(50);
//
//                }
//
//
//
//            }
//        }
//    }

// Turn on charging
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
//    VBAR

//    while (1) {
//
//
//        int max = 100;
//        uint32_t value = 0;
//        float voltage = 0;
//        for (int i = 0; i < max; ++i) {
//            HAL_ADC_Start(&hadc);
//            if (HAL_ADC_PollForConversion(&hadc, 1000) == HAL_OK) {
//                value = HAL_ADC_GetValue(&hadc);
//            }
//            HAL_ADC_Stop(&hadc);
//        }
//
//        value = (uint32_t)(value * 2) * 3300 / 0xfff;
//        voltage =  (float)(value / 10.0);
//
//
//        TM_Ext_ClearText(display);
//        TM_Ext_Hours(display, voltage / 100, true);
//        TM_Ext_Minutes(display, (int)voltage % 100, true);
//
//        HAL_Delay(1000);
//
//    }



  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,
            uint16_t pulse)
{
    HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
    TIM_OC_InitTypeDef sConfigOC;
    timer.Init.Period = period; // set the period duration
    HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse; // set the pulse duration
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
    HAL_TIM_PWM_Start(&timer, channel); // start pwm generation
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */

    /* User can add his own implementation to report the HAL error return state */

    while (1) {

    }

  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */

    /* User can add his own implementation to report the file name and line number,

      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
