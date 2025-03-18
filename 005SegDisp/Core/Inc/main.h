/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define F_Pin GPIO_PIN_13
#define F_GPIO_Port GPIOC
#define DP_Pin GPIO_PIN_0
#define DP_GPIO_Port GPIOC
#define G_Pin GPIO_PIN_1
#define G_GPIO_Port GPIOC
#define D1_Pin GPIO_PIN_0
#define D1_GPIO_Port GPIOA
#define D2_Pin GPIO_PIN_1
#define D2_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_4
#define D3_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_0
#define D4_GPIO_Port GPIOB
#define D_Pin GPIO_PIN_15
#define D_GPIO_Port GPIOA
#define A_Pin GPIO_PIN_11
#define A_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_12
#define C_GPIO_Port GPIOC
#define B_Pin GPIO_PIN_2
#define B_GPIO_Port GPIOD
#define E_Pin GPIO_PIN_7
#define E_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
