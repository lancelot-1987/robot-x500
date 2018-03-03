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
#include "tim.h"
#include "gpio.h"
#include "irmp/irmp.h"

/* USER CODE BEGIN Includes */

#include "tm1628/Display.h"
#include "x500.h"
#include "wtv040/wtv.h"
#include "irmp/irmpsystem.h"
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

IRMP_DATA irmp_data1;
IRMP_DATA irmp_data2;
IRMP_DATA irmp_data3;
IRMP_STATE irmp_state1;
IRMP_STATE irmp_state2;
IRMP_STATE irmp_state3;

void TIM16_IRQHandler(void) {
    /* USER CODE BEGIN TIM16_IRQn 0 */
    irmp_ISR(IR_1_GPIO_Port, IR_1_Pin,
             &irmp_state1);                                                        // call irmp ISR
//    irmp_ISR(IR_2_GPIO_Port, IR_2_Pin,
//             &irmp_state2);                                                        // call irmp ISR
//    irmp_ISR(IR_3_GPIO_Port, IR_3_Pin,
//             &irmp_state3);                                                        // call irmp ISR

    /* USER CODE END TIM16_IRQn 0 */
    HAL_TIM_IRQHandler(&htim16);
    /* USER CODE BEGIN TIM16_IRQn 1 */

    /* USER CODE END TIM16_IRQn 1 */
}


/* USER CODE END 0 */

int main(void) {

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
    MX_TIM16_Init();

    /* USER CODE BEGIN 2 */



    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    struct TM16XX display;

    display.dioPort = DISPLAY_DIO_GPIO_Port;
    display.dio = DISPLAY_DIO_Pin;
    display.clkPort = DISPLAY_CLK_GPIO_Port;
    display.clk = DISPLAY_CLK_Pin;
    display.stbPort = DISPLAY_STB_GPIO_Port;
    display.stb = DISPLAY_STB_Pin;


    TM_Init(&display, true, 8);
    TM_Brightness(&display, true, 7);
    TM_Clear(&display);
    TM_Ext_Text(&display, "1111");

    __HAL_RCC_SYSCFG_CLK_ENABLE();

    X500_Charge(true);
//    X500_Right_Wheel(true);
//    X500_BatteryMon_Test(&display, &hadc);


//    X500_Bell_All(&display);
    X500_Main_Bus(true);
//    X500_Bell_Inc(&display);

    uint32_t data = 239;
//    WTV040_Cmd(data);
//    WTV040_Cmd(239);
//    WTV040_Cmd(241);

//    WTV040_OpenAmp();
//    WTV040_Volume(0);
//    for (int i = 0; i < 250; ++i) {
//        WTV040_Cmd(i);
//        HAL_Delay(100);
//}

    char buf[4] = {0};

    HAL_TIM_Base_Start_IT(&htim16);
    const int SIZE = 1024;
    IRMP_DATA all[SIZE];
    for (int j = 0; j < SIZE; ++j) {
        all[j].command = 0;
        all[j].address = 0;
        all[j].flags = 0;
        all[j].protocol = 0;
    }
    int current = 0;
    for (;;) {
        if (irmp_get_data(&irmp_data1, &irmp_state1)) {
            sprintf(buf, "%d", current);
            TM_Ext_Text(&display, buf);
            bool found = false;
            for (int i = 0; i < SIZE; i++) {
                IRMP_DATA toCompare = all[i];
                if (/*toCompare.address == irmp_data1.address &&*/ toCompare.command == irmp_data1.command) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                all[current] = irmp_data1;
                current++;
            }
        }
//        if (irmp_get_data(&irmp_data2, &irmp_state2)) {
//            sprintf(buf, "%d", irmp_data2.address);
//            TM_Ext_Text(&display, buf);
//        }
//        if (irmp_get_data(&irmp_data3, &irmp_state3)) {
//            sprintf(buf, "%d", irmp_data3.address);
//            TM_Ext_Text(&display, buf);
//        }



    }


    /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void) {

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSI14;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.HSI14CalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        _Error_Handler(__FILE__, __LINE__);
    }

    /**Configure the Systick interrupt time 
    */
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    /**Configure the Systick 
    */
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char *file, int line) {
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
