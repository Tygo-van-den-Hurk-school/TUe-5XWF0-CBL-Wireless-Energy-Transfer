/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D8_OCP_Pin GPIO_PIN_0
#define D8_OCP_GPIO_Port GPIOF
#define A0_COIL_CURR_Pin GPIO_PIN_0
#define A0_COIL_CURR_GPIO_Port GPIOA
#define A3_CAP_NEG_Pin GPIO_PIN_4
#define A3_CAP_NEG_GPIO_Port GPIOA
#define A6_CAP_POS_Pin GPIO_PIN_7
#define A6_CAP_POS_GPIO_Port GPIOA
#define D3_TX2_Pin GPIO_PIN_0
#define D3_TX2_GPIO_Port GPIOB
#define D6_RX2_Pin GPIO_PIN_1
#define D6_RX2_GPIO_Port GPIOB
#define D9_PWM_DCAC_1_Pin GPIO_PIN_8
#define D9_PWM_DCAC_1_GPIO_Port GPIOA
#define D10_PWM_DCAC_2_Pin GPIO_PIN_11
#define D10_PWM_DCAC_2_GPIO_Port GPIOA
#define D5_TX1_Pin GPIO_PIN_6
#define D5_TX1_GPIO_Port GPIOB
#define D4_RX1_Pin GPIO_PIN_7
#define D4_RX1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
