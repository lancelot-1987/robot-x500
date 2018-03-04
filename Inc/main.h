/**
  ******************************************************************************
  * File Name          : main.hpp
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define AUDIO_RESET_Pin GPIO_PIN_3
#define AUDIO_RESET_GPIO_Port GPIOE
#define RIGHT_BORDER_SENSOR_Pin GPIO_PIN_2
#define RIGHT_BORDER_SENSOR_GPIO_Port GPIOA
#define LEFT_BORDER_SENSOR_Pin GPIO_PIN_5
#define LEFT_BORDER_SENSOR_GPIO_Port GPIOA
#define MAIN_BUS_Pin GPIO_PIN_6
#define MAIN_BUS_GPIO_Port GPIOA
#define DISPLAY_CLK_Pin GPIO_PIN_8
#define DISPLAY_CLK_GPIO_Port GPIOE
#define DISPLAY_DIO_Pin GPIO_PIN_10
#define DISPLAY_DIO_GPIO_Port GPIOE
#define RIGHT_BRUSH_Pin GPIO_PIN_14
#define RIGHT_BRUSH_GPIO_Port GPIOB
#define DISPLAY_STB_Pin GPIO_PIN_11
#define DISPLAY_STB_GPIO_Port GPIOD
#define IR_3_Pin GPIO_PIN_12
#define IR_3_GPIO_Port GPIOD
#define IR_2_Pin GPIO_PIN_13
#define IR_2_GPIO_Port GPIOD
#define IR_1_Pin GPIO_PIN_14
#define IR_1_GPIO_Port GPIOD
#define RIGHT_WHEEL_START_Pin GPIO_PIN_6
#define RIGHT_WHEEL_START_GPIO_Port GPIOC
#define CHARGE_ON_Pin GPIO_PIN_7
#define CHARGE_ON_GPIO_Port GPIOC
#define LEFT_BRUSH_Pin GPIO_PIN_8
#define LEFT_BRUSH_GPIO_Port GPIOA
#define DISPLAY_PLAN_Pin GPIO_PIN_10
#define DISPLAY_PLAN_GPIO_Port GPIOC
#define DISPLAY_SPOT_Pin GPIO_PIN_11
#define DISPLAY_SPOT_GPIO_Port GPIOC
#define AUDIO_DATA_Pin GPIO_PIN_4
#define AUDIO_DATA_GPIO_Port GPIOB
#define DISPLAY_HOME_Pin GPIO_PIN_0
#define DISPLAY_HOME_GPIO_Port GPIOE
#define DISPLAY_CLEAN_Pin GPIO_PIN_1
#define DISPLAY_CLEAN_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
