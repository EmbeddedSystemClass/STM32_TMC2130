/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "delay_us.h"

#include "TMC2130_Register.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

extern UART_HandleTypeDef huart2;
UART_HandleTypeDef* CLI_UART = &huart2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t TMC2130_Write_Register(uint8_t reg, uint32_t data)
    {

    uint8_t s;
    uint8_t temp;

    uint8_t cmd_w = 0x80 | reg;

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi1, &cmd_w, &s, 1, 100);

    temp = ((data >> 24UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((data >> 16UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((data >> 8UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    temp = ((data >> 0UL) & 0xFF);
    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return s;
    }


uint8_t TMC2130_Set_Read_Register(uint8_t reg)
    {

    uint8_t temp = 0x00;
    uint8_t s;

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi1, &reg, &s, 1, 100);

    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_SPI_Transmit(&hspi1, &temp, 1, 100);

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return s;

    }

uint8_t TMC2130_Read_Register(uint8_t reg, uint32_t *data)
    {

    uint8_t s;
    uint8_t temp;
    uint32_t val = 0;

    TMC2130_Set_Read_Register(reg);

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&hspi1, &reg, &s, 1, 100);

    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val = temp << 24;

    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 16;

    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 8;

    HAL_SPI_Receive(&hspi1, &temp, 1, 100);
    val |= temp << 0;

    *data = val;

    HAL_GPIO_WritePin(SPI_CS_GPIO_Port, SPI_CS_Pin, GPIO_PIN_SET);

    return s;
    }


void CLI_UART_Send_Char(char data)
    {
    CLI_UART->Instance->DR = (data);
    while (__HAL_UART_GET_FLAG(CLI_UART,UART_FLAG_TC) == 0);
    }

void CLI_UART_Send_String(char *data)
    {
    while (*data)
	{
	CLI_UART_Send_Char(*data++);
	}
    }

void CLI_UART_Send_Int(int32_t num)
    {
    char int_to_str[10] = {0};
    itoa(num, int_to_str, 10);
    CLI_UART_Send_String(int_to_str);
    }

void CLI_UART_Send_Int_Hex(int32_t num)
    {
    char int_to_str[32] = {0};
    itoa(num, int_to_str, 16);
    CLI_UART_Send_String(int_to_str);
    }

void TMC2130_Step_TIM_ISR()
    {
    static uint32_t pulse_count = 0;
    HAL_GPIO_TogglePin(STEP_GPIO_Port, STEP_Pin);
    pulse_count++;
    if(pulse_count > 400000)
	{
	pulse_count = 0;
	HAL_GPIO_TogglePin(DIR_GPIO_Port, DIR_Pin);
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
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */


  //set TMC2130 config
  TMC2130_Write_Register(TMC2130_GCONF,      0x00000001UL);  //voltage on AIN is current reference
  TMC2130_Write_Register(TMC2130_IHOLD_IRUN, 0x00001010UL);  //IHOLD=0x10, IRUN=0x10
  TMC2130_Write_Register(TMC2130_CHOPCONF,   0x00008008UL);  //native 256 microsteps, MRES=0, TBL=1=24, TOFF=8


  //outputs on (LOW active)
  HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);

  HAL_TIM_Base_Start_IT(&htim11);

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	static uint32_t time_elapsed = 0;
	uint32_t data;
	uint8_t s;

	if (HAL_GetTick() - time_elapsed > 1000)
	    {

	    time_elapsed = HAL_GetTick();

	    HAL_TIM_Base_Stop_IT(&htim11);

	    s = TMC2130_Read_Register(TMC2130_IOIN, &data);

	    CLI_UART_Send_String("TMC2130_IOIN:0x0");
	    CLI_UART_Send_Int_Hex(data);
	    CLI_UART_Send_String("\t");
	    CLI_UART_Send_String("Status:0x");
	    CLI_UART_Send_Int_Hex(s);

	    if (s & 0x01)
		{
		CLI_UART_Send_String(" reset");
		}
	    else if (s & 0x02)
		{
		CLI_UART_Send_String(" error");
		}
	    else if (s & 0x04)
		{
		CLI_UART_Send_String(" sg2");
		}
	    else if (s & 0x08)
		{
		CLI_UART_Send_String(" standstill");
		}
	    CLI_UART_Send_String("\n");

	    HAL_TIM_Base_Start_IT(&htim11);

	    }


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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
