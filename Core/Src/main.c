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
#include "tmc2130_step_generator.h"
#include "tmc2130_interface_api.h"

#include "main.h"
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

TMC2130TypeDef Motor_X;
TMC2130_Controller_t Motor_X_Controller = {.Motor = &Motor_X};

TMC2130TypeDef Motor_Y;
TMC2130_Controller_t Motor_Y_Controller = {.Motor = &Motor_Y};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */




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


void Motor_X_config()
    {

    int32_t sts = 0;

    Motor_X.CS_Port = SPI_CS_X_GPIO_Port;
    Motor_X.CS_Pin  = SPI_CS_X_Pin;

    Motor_X.Step_Port = STEP_X_GPIO_Port;
    Motor_X.Step_Pin  = STEP_X_Pin;

    Motor_X.DIR_Port = DIR_X_GPIO_Port;
    Motor_X.DIR_Pin = DIR_X_Pin;

    Motor_X.Enable_Port = EN_X_GPIO_Port;
    Motor_X.Enable_Pin = EN_X_Pin;

    Motor_X.DIAG1_Port = DIAG0_X_GPIO_Port;
    Motor_X.DIAG1_Pin = DIAG0_X_Pin;

    TMC_Add(&Motor_X_Controller);

    // set step generator parameters
    TMC_Set_Acceleration(&Motor_X_Controller, 100000);
    TMC_Set_MAX_velocity(&Motor_X_Controller, 100000);

    // enable stall and set minimum velocity for stall activation
    TMC_Enable_Stall(&Motor_X_Controller, 100000);



    // set tmc2130 parameters
    TMC2130_Set_Chopper_Off_Time(&Motor_X, 4);
    TMC2130_Set_Chopper_Blank_Time(&Motor_X, 0b10);
    TMC2130_Set_Max_Current(&Motor_X, 5);
    TMC2130_Set_Standby_Current(&Motor_X, 5);
    TMC2130_Set_Microstep(&Motor_X, 256);
    TMC2130_Set_TCOOLTHRS(&Motor_X, 0xFFFFF);
    TMC2130_Set_THIGH(&Motor_X, 0);
    TMC2130_Set_SEMIN_I(&Motor_X, 5);
    TMC2130_Set_SEMAX(&Motor_X, 2);
    TMC2130_Set_SEDN_I(&Motor_X, 0b01);



    TMC2130_Set_Stall_Threshold(&Motor_X, 12);


    // config diag1 for stall
    TMC2130_Set_DIAG0_Attribute(&Motor_X, DIAG_STALL, 1);


    sts = TMC2130_Get_Microstep(&Motor_X);
    sts = TMC2130_Get_Max_Current(&Motor_X);
    sts = TMC2130_Get_Standby_Current(&Motor_X);
    }


void Motor_Y_config()
    {

    int32_t sts = 0;

    Motor_Y.CS_Port = SPI_CS_Y_GPIO_Port;
    Motor_Y.CS_Pin  = SPI_CS_Y_Pin;

    Motor_Y.Step_Port = STEP_Y_GPIO_Port;
    Motor_Y.Step_Pin  = STEP_Y_Pin;

    Motor_Y.DIR_Port = DIR_Y_GPIO_Port;
    Motor_Y.DIR_Pin = DIR_Y_Pin;

    Motor_Y.Enable_Port = EN_Y_GPIO_Port;
    Motor_Y.Enable_Pin = EN_Y_Pin;

    Motor_Y.DIAG1_Port = DIAG0_Y_GPIO_Port;
    Motor_Y.DIAG1_Pin = DIAG0_Y_Pin;

    TMC_Add(&Motor_Y_Controller);

    // set step generator parameters
    TMC_Set_Acceleration(&Motor_Y_Controller, 130000);
    TMC_Set_MAX_velocity(&Motor_Y_Controller, 130000);

    // enable stall and set minimum velocity for stall activation
    TMC_Enable_Stall(&Motor_Y_Controller, 100000);



    // set tmc2130 parameters
    TMC2130_Set_Chopper_Off_Time(&Motor_Y, 4);
    TMC2130_Set_Chopper_Blank_Time(&Motor_Y, 0b10);
    TMC2130_Set_Max_Current(&Motor_Y, 5);
    TMC2130_Set_Standby_Current(&Motor_Y, 5);
    TMC2130_Set_Microstep(&Motor_Y, 256);
    TMC2130_Set_TCOOLTHRS(&Motor_Y, 0xFFFFF);
    TMC2130_Set_THIGH(&Motor_Y, 0);
    TMC2130_Set_SEMIN_I(&Motor_Y, 5);
    TMC2130_Set_SEMAX(&Motor_Y, 2);
    TMC2130_Set_SEDN_I(&Motor_Y, 0b01);



    TMC2130_Set_Stall_Threshold(&Motor_Y, 12);


    // config diag1 for stall
    TMC2130_Set_DIAG0_Attribute(&Motor_Y, DIAG_STALL, 1);


    sts = TMC2130_Get_Microstep(&Motor_Y);
    sts = TMC2130_Get_Max_Current(&Motor_Y);
    sts = TMC2130_Get_Standby_Current(&Motor_Y);
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
  MX_TIM10_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */

  Motor_X_config();
  Motor_Y_config();


  TMC_Enable_Driver(&Motor_X_Controller, 1);
  TMC_Enable_Driver(&Motor_Y_Controller, 1);

  TMC_TIM_Enable(1);


  //rotate at fix velocity rpm = (100000*60)/(200*256)
  TMC_Rotate(&Motor_X_Controller, 100000);

  // wait for stall, sensorless homing
  while(!(TMC_Get_Status(&Motor_X_Controller) & STATUS_STALLED));

  // reset postion
  TMC_Set_Actual_Position(&Motor_X_Controller, 0);



  //rotate at fix velocity rpm = (50000*60)/(200*256)
  //TMC_Rotate(&Motor_Y_Controller, 50000);

  // wait for stall, sensorless homing
  //while(!(TMC_Get_Status(&Motor_Y_Controller) & STATUS_STALLED));

  // reset postion
  //TMC_Set_Actual_Position(&Motor_Y_Controller, 0);

  HAL_Delay(2000);

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {

  TMC_Move(&Motor_X_Controller, -256*200*1);  // move xx revolution
  TMC_Move(&Motor_Y_Controller, -256*200*2); // move xx revolution

  while(!(TMC_Get_Status(&Motor_X_Controller) & STATUS_TARGET_REACHED) &&
	  !(TMC_Get_Status(&Motor_X_Controller) & STATUS_STALLED));

  while(!(TMC_Get_Status(&Motor_Y_Controller) & STATUS_TARGET_REACHED) &&
	  !(TMC_Get_Status(&Motor_Y_Controller) & STATUS_STALLED));
  HAL_Delay(10);

  TMC_Move(&Motor_X_Controller, 256*200*1); // move xx revolution
  TMC_Move(&Motor_Y_Controller, 256*200*2); // move xx revolution

  while(!(TMC_Get_Status(&Motor_X_Controller) & STATUS_TARGET_REACHED) &&
	  !(TMC_Get_Status(&Motor_X_Controller) & STATUS_STALLED));

  while(!(TMC_Get_Status(&Motor_Y_Controller) & STATUS_TARGET_REACHED) &&
	  !(TMC_Get_Status(&Motor_Y_Controller) & STATUS_STALLED));

  HAL_Delay(10);

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
