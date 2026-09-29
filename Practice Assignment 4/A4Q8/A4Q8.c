/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include<stdio.h>
#include<string.h>
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
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
#define addr_write 0x70<<1
#define addr_read (0x70<<1) | 0x01

	char printBuffer[64]={0};
	uint8_t regTemp[2];
	uint8_t regHum[2];
	uint8_t rxBuffT[2];
	uint8_t rxBuffH[2];
	uint16_t rawTemp=0;
	uint16_t rawHumd=0;
	char option;
	float temp;
	float humd;
	void Start_temperature_conversion();
	void Display_temperature_value();
	void Start_Humidity_conversion();
	void Display_humidity_value();
	void Stop_Conversion();
	void reset_sensor();

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
  	  	  	  printf("-------------------------------------------------\n\r");
  			  printf("--------Select your choice-----------------------\n\r");
  			  printf("Press 1 : Start temperature conversion\n\r");
  			  printf("Press 2 : Display temperature value\n\r");
  			  printf("Press 3 : Start Humidity conversion\n\r");
  			  printf("Press 4 : Display humidity value\n\r");
  			  printf("Press 5 : Stop Conversion\n\r");
  			  printf("-------------------------------------------------\n\r");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(HAL_UART_Receive(&huart1, (uint8_t *)&option, 1, 100)==HAL_OK){
	  	  	  switch(option){
	  	  	  case '1':Start_temperature_conversion();
	  	  	  	  	  	  break;
	  	  	  case '2':Display_temperature_value();
	  	  	  	  	  	  break;
	  	  	  case '3': Start_Humidity_conversion();
	  	  	  	  	  	  break;
	  	  	  case '4': Display_humidity_value();
	  	  	  	  	  	  break;
	  	  	  case '5': Stop_Conversion();
	  	  	  	  	  	  break;
	  	  	  default: printf("Select from Given Options\n\r");
	  	  	  	  	  break;
	  	  	  }
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
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

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
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00503D58;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : button_Pin */
  GPIO_InitStruct.Pin = button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(button_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void reset_sensor(){
	  if(HAL_I2C_IsDeviceReady(&hi2c2, addr_write, 1, 100)==HAL_OK){
	    		HAL_UART_Transmit(&huart1,(uint8_t *) "Device Ready\n\r", sizeof("Device Ready\n\r"),1000);
	    	}
	    	else{
	    		HAL_UART_Transmit(&huart1,(uint8_t *) "Device Not Ready\n\r", sizeof("Device Not Ready\n\r"),1000);
	    		while(1){}
	    	}
	    	//device wakeup
	    	regTemp[0]=0x35;
	        regTemp[1]=0x17;
	    	if(HAL_I2C_Master_Transmit(&hi2c2, addr_write, regTemp, sizeof(regTemp), 100)==HAL_OK){
	    				  HAL_UART_Transmit(&huart1, (uint8_t *)"Device Wake up\n\r", sizeof("Device Wake up\n\r"),1000);
	    	}
	    	//device soft reset
	    	regTemp[0]=0x80;     //Reset
	        regTemp[1]=0x5D;
	        if(HAL_I2C_Master_Transmit(&hi2c2, addr_read, regTemp, sizeof(regTemp), 100)==HAL_OK){
	    		  HAL_UART_Transmit(&huart1, (uint8_t *)"Soft RESET\n\r", sizeof("Soft RESET\n\r"),1000);
	    	}
  	  }

void Start_temperature_conversion(){
	reset_sensor();
	rxBuffT[0]=0x00;
		  	  	  rxBuffT[1]=0x00;

		  	  	  //Temperature
		  	  	  regTemp[0]=0x7C;
		  	  	  regTemp[1]=0xA2;

		  	  	  HAL_I2C_Master_Transmit(&hi2c2, addr_read, regTemp, sizeof(regTemp), 100);
		  	  	  HAL_Delay(100);
		  	  	  HAL_I2C_Master_Receive(&hi2c2, addr_read, rxBuffT, sizeof(rxBuffT), 100);
		  	  	  printf("Temperature Conversion started\n\r");
		  	  	  rawTemp = (rxBuffT[0]<<8) + rxBuffT[1];

}
void Display_temperature_value(){
	if(rawTemp<=0){
		printf("Press 1 to Start the temperature Conversion\n\r");
		return;
	}
	temp = 175*(float)rawTemp/65536.0f -45.0f;
		  	  	  sprintf(printBuffer,"Temperature: %.1f C\n\r", temp);
		  	  	  HAL_UART_Transmit(&huart1, (uint8_t *)printBuffer, strlen(printBuffer),1000);
		  	  	  HAL_Delay(1000);
}
void Start_Humidity_conversion(){
	reset_sensor();
	rxBuffH[0]=0x00;
		  		  rxBuffH[1]=0x00;

		  		  //Relative Humidity
		  	  	  regHum[0]=0x5C;
		  		  regHum[1]=0x24;

		  		  HAL_I2C_Master_Transmit(&hi2c2, addr_read, regHum, sizeof(regHum), 100);
		  		  HAL_Delay(100);
		  		  HAL_I2C_Master_Receive(&hi2c2, addr_read, rxBuffH, sizeof(rxBuffH), 100);
		  		  printf("Humidity Conversion started\n\r");
		  		  rawHumd = (rxBuffH[0]<<8) + rxBuffH[1];
}
void Display_humidity_value(){
	if(rawHumd<=0){
			printf("Press 3 to Start the Humidity Conversion\n\r");
			return;
	}
	humd = 100*(float)rawHumd/65536.0f;
		  		  sprintf(printBuffer,"Relative Humidity: %.1f %%\n\r", humd);
		  		  HAL_UART_Transmit(&huart1, (uint8_t *)printBuffer, strlen(printBuffer),1000);
		  		  HAL_Delay(1000);
}
void Stop_Conversion(){
	//device Sleep
	regTemp[0]=0xB0;
	regTemp[1]=0x98;
	if(HAL_I2C_Master_Transmit(&hi2c2, addr_write, regTemp, sizeof(regTemp), 100)==HAL_OK){
				  HAL_UART_Transmit(&huart1, (uint8_t *)"Device in Sleep Mode\n\r", sizeof("Device in Sleep Mode\n\r"),1000);
	}
}

int __io_putchar(int ch){
	HAL_UART_Transmit(&huart1, (uint8_t *) &ch, 1, HAL_MAX_DELAY);
	return ch;
}
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
#ifdef USE_FULL_ASSERT
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
