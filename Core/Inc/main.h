/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct 
{
  float Uin;
  float Iin;
  float Um;
  float Uout;
  float Iout;
  uint8_t enable;
}Power_type;

extern Power_type g_power_set;
extern Power_type g_power_atcual;
extern Input_type g_input;
extern uint32_t g_adc_buff[5];
extern uint8_t g_err_code;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define sys_time_ms uwTick

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CV_Pin GPIO_PIN_0
#define CV_GPIO_Port GPIOB
#define CC_Pin GPIO_PIN_1
#define CC_GPIO_Port GPIOB
#define ON_OFF_Pin GPIO_PIN_2
#define ON_OFF_GPIO_Port GPIOB
#define OLED_D1_Pin GPIO_PIN_10
#define OLED_D1_GPIO_Port GPIOB
#define OLED_D0_Pin GPIO_PIN_11
#define OLED_D0_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_12
#define OLED_DC_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_13
#define OLED_RES_GPIO_Port GPIOB
#define S1_A_Pin GPIO_PIN_14
#define S1_A_GPIO_Port GPIOB
#define S1_B_Pin GPIO_PIN_15
#define S1_B_GPIO_Port GPIOB
#define S1_M_Pin GPIO_PIN_6
#define S1_M_GPIO_Port GPIOC
#define S2_M_Pin GPIO_PIN_8
#define S2_M_GPIO_Port GPIOA
#define S2_A_Pin GPIO_PIN_11
#define S2_A_GPIO_Port GPIOA
#define S2_B_Pin GPIO_PIN_12
#define S2_B_GPIO_Port GPIOA
#define POWER_ON_Pin GPIO_PIN_10
#define POWER_ON_GPIO_Port GPIOC
#define SHUTDOWN_Pin GPIO_PIN_11
#define SHUTDOWN_GPIO_Port GPIOC
#define LED_HEART_Pin GPIO_PIN_5
#define LED_HEART_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
