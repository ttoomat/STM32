/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_ADDR (0x27 << 1)       // адрес дисплея, сдвинутый на 1 бит влево (HAL работает с I2C-адресами, сдвинутыми на 1 бит влево)

#define PIN_RS    (1 << 0)         // если на ножке 0, данные воспринимаются как команда, если 1 - как символы для вывода
#define PIN_EN    (1 << 2)         // бит, по изменению сост. которого считывается информация
#define BACKLIGHT (1 << 3)         // управление подсветкой

#define LCD_DELAY_MS 5             // пауза перед высвечиванием символа
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// функция для отправки данных, data - сами данные, flags - 1 (отправка данных) или 0 (отправка команд)
void I2C_send(uint8_t data, uint8_t flags)
{
	HAL_StatusTypeDef res;
	    for(;;) {                                                                     // бесконечный цикл
	        res = HAL_I2C_IsDeviceReady(&hi2c1, LCD_ADDR, 1, HAL_MAX_DELAY);          // проверяем, готово ли устройство по адресу lcd_addr для связи
	        if(res == HAL_OK) break;                                                  // если да, то выходим из бесконечного цикла
	    }

	uint8_t up = data & 0xF0;                 // операция И с 1111 0000, приводит к обнулению последних бит с 0 по 3, остаются биты с 4 по 7
	uint8_t lo = (data << 4) & 0xF0;          // тоже самое, но data сдвигается на 4 бита влево, т.е. в этой
	                                           // переменной остаются  биты с 0 по 3
	uint8_t data_arr[4];
	data_arr[0] = up|flags|BACKLIGHT|PIN_EN;  // 4-7 биты содержат информацию, биты 0-3 конфигурируют работу
	data_arr[1] = up|flags|BACKLIGHT;         // ублирование сигнала, на выводе Е в этот раз 0
	data_arr[2] = lo|flags|BACKLIGHT|PIN_EN;
	data_arr[3] = lo|flags|BACKLIGHT;

	HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
	HAL_Delay(LCD_DELAY_MS);
}

// функция передачи данных (RS=1)
void LCD_SendString(char *str)
{
    // *char по сути является строкой
	while(*str) {                                   // пока строчка не закончится
		I2C_send((uint8_t)(*str), PIN_RS);          // передача первого символа строки
        str++;                                      // сдвиг строки налево на 1 символ
    }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  // second parameter (0) selects command (RS_BIT would set a data interaction)
  I2C_send(0b00110000, 0);   // 8ми битный интерфейс
  HAL_Delay(100);
  I2C_send(0b00110000, 0);   // 8ми битный интерфейс
  I2C_send(0b00110000, 0);   // 8ми битный интерфейс
  I2C_send(0b00111000, 0);   // N=1 - two rows, F=0 - 5x7 font

  I2C_send(0b00000001, 0);   // очистка дисплея
  I2C_send(0b00000010, 0);   // по идее - установка курсора
  I2C_send(0b00000110, 0);   // I/D = 1 - increment cursor, S=0 - no display shift

  // initialization ends

  I2C_send(0b00001110, 0);   // нормальный режим работы display on + cursor on + blink on

  uint8_t customChar[] = {
		0b00000,
		0b01010,
		0b10101,
		0b10001,
		0b01010,
		0b00100,
		0b00000,
		0b00000
  };

  I2C_send(0b01000000, 0);   // set command GRAM AD SET
  // send the char
  for (uint8_t i = 0; i < 8; i++)
    I2C_send(customChar[i], 1);

  I2C_send(0b11000000, 0);   // переход на 2 строку
  I2C_send(0b00000000, 1); // GRAM 0 = heart custom symbol
  LCD_SendString("Tamara");
  HAL_Delay(10000);
  I2C_send(0b10000000, 0);   // переход на 1 строку
  I2C_send(0b00000000, 1); // GRAM 0 = heart custom symbol
  I2C_send(0b00000000, 1); // GRAM 0 = heart custom symbol
  I2C_send(0b00000000, 1); // GRAM 0 = heart custom symbol

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
