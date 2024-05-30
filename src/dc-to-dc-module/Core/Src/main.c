/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body for the DC-AC circuit
  * @author         : Tygo van den Hurk
  * @author         : Gabriël Nusselder
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 Group 1 for DBL Wireless Energy Transfer a course at TU/e
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this repository. If no LICENSE file comes with
  * this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdarg.h>
#include <float.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EVER                 		true
#define MILISECONDS_IN_A_SECOND 	1000

#define INITIAL_DUTY_CYCLE   		0.5f
#define DUTY_CYCLE_STEP_SIZE 		0.01f

#define HAL_ERROR			 		1
#define OVERCURRENT_ERROR 	 	    2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/** @brief Represents the current duty cycle that boost converter is running on. */
float currentDutyCycle = INITIAL_DUTY_CYCLE;

/** @brief Represents the step size of the duty cycle that boost converter is changing with. */
float stepSize = DUTY_CYCLE_STEP_SIZE;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/**
 * @brief blinks of the span of 1 second.
 */
void blink() {

	const int halfSecond = ( MILISECONDS_IN_A_SECOND / 2);

	/* Blink with half a second in between */ {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(halfSecond);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(halfSecond);
	}
}

/**
 * @brief shows an error code by blinking. Blinks x times, and then pauses. The amount of blinks define the error code. Warning does not exit.
 * @param errorCode: the error code to display.
 */
void showErrorCodeOnLED(const int errorCode){
	const int amountOfMilisecondsInSecond = (1000);
	const int threeSeconds = (3 * amountOfMilisecondsInSecond);

	for (;EVER;) { // blink:
		for (int blinks = 0; blinks < errorCode; blinks++ ) blink();
		HAL_Delay(threeSeconds);
	}
}

/**
 * @brief sets the duty cycle to a certain percentage.
 * @param dutyCycle: the current dutyCycle.
 */
void setDutyCycle(const float dutyCycle) {
	// TODO : make this.
}

/**
 * @brief Gets the current voltage.
 * @retval The current current with the current duty cycle.
 */
float readVoltage() {
    return 0; // TODO : make this.
}

/**
 * @brief Gets the current current.
 * @retval The current voltage with the current duty cycle.
 */
float readVoltage() {
    return 0; // TODO : make this.
}

/**
 * @brief Gets the current power draw based on a certain duty cycle.
 * @param dutyCycle: the current dutyCycle.
 * @retval The power output using that duty cycle.
 */
float getPowerUsing(const float dutyCycle) {

    setDutyCycle(dutyCycle);

    const float voltage = readVoltage();
    const float current = readCurrent();
    const float power   = ( voltage * current );

    return power;
}

/**
 * @brief Updates the MPPT to the better duty cycle.
 */
void maintain_MPPT() {

    const float oldDutyCycle = (currentDutyCycle);
    const float newDutyCycle = (oldDutyCycle + stepSize);

    const float powerWithOldDutyCycle = getPowerUsing(oldDutyCycle);
    const float powerWithNewDutyCycle = getPowerUsing(newDutyCycle);

    const bool powerBugetIncreased = (powerWithNewDutyCycle > powerWithOldDutyCycle);
    const bool powerBugetDecreased = (powerWithNewDutyCycle < powerWithOldDutyCycle);

    const float optimumDutyCycle;
    /* Determine the optimum Duty Cycle. */ {
        if (powerBugetIncreased) { optimumDutyCycle = (newDutyCycle); } else
        if (powerBugetDecreased) { optimumDutyCycle = (oldDutyCycle); }
		else { optimumDutyCycle = (currentDutyCycle); }
    }

    currentDutyCycle = (optimumDutyCycle);
    setDutyCycle(optimumDutyCycle);

    /* Changing direction if we were getting further away. */ {
        if (powerBugetDecreased) stepSize = -stepSize;
    }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */
	/* USER CODE BEGIN 3 */
    blink();
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  showErrorCodeOnLED(HAL_ERROR);
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
