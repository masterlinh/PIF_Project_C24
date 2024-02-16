/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* The program belong to Nhan , Quoc, Huy Le, Huy Nguyen*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "lcd_i2c.h"
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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
LCD_I2C_HandleTypeDef p_LCD;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config (void);
static void MX_GPIO_Init (void);
static void MX_DMA_Init (void);
static void MX_I2C1_Init (void);
static void MX_USART2_UART_Init (void);
static void MX_ADC1_Init (void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//Phần dưới là khai báo + viết hàm xuất trên solenoid
uint8_t UART1_rxBuffer[1024] = {0};

//char data[1024]
uint8_t input;

int * output;

int dot[63][6] =
		{{0,0,0,0,0,0},{0,1,1,0,1,1},{0,0,0,1,0,0},{0,1,0,1,1,1},{1,1,1,0,0,1},{1,1,0,0,0,1},{1,1,1,0,1,1},{1,0,1,1,1,1},{0,1,1,1,1,1},{1,0,0,0,0,1},{0,1,0,0,1,1} ,{0,0,0,0,0,1} ,{0,0,0,0,1,1},{0,1,0,0,0,1},{0,1,0,0,1,0},
        {0,0,0,1,1,1},{0,0,1,0,0,0},{0,0,1,0,1,0},{0,0,1,1,0,0},{0,0,1,1,0,1},{0,0,1,0,0,1},{0,0,1,1,1,0},{0,0,1,1,1,1},{0,0,1,0,1,1},{0,0,0,1,1,0},{1,0,0,1,0,1},{0,0,0,1,0,1},{1,0,1,0,0,1},{1,1,1,1,1,1},{0,1,0,1,1,0},{1,1,0,1,0,1},
        {0,1,0,0,0,0},{1,0,0,0,0,0},{1,0,1,0,0,0},{1,1,0,0,0,0},{1,1,0,1,0,0},{1,0,0,1,0,0},{1,1,1,0,0,0},{1,1,1,1,0,0},{1,0,1,1,0,0},{0,1,1,0,0,0},{0,1,1,1,0,0},{1,0,0,0,1,0},{1,0,1,0,1,0},{1,1,0,0,1,0},{1,1,0,1,1,0},{1,0,0,1,1,0},{1,1,1,0,1,0},{1,1,1,1,1,0},{1,0,1,1,1,0},{0,1,1,0,1,0},{0,1,1,1,1,0},{1,0,0,0,1,1},{1,0,1,0,1,1},{0,1,1,1,0,1},{1,1,0,0,1,1},{1,1,0,1,1,1},{1,0,0,1,1,1},
        {0,1,1,0,0,1},{1,0,1,1,0,1},{1,1,1,1,0,1},{0,1,0,1,0,0},{0,1,0,1,0,1}};

char ascii[63] = {' ', '!', '"', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/',
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
		'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '[', '\\', ']', '^', '_'};

void
Display_by_Solenoid (int* output)
{
	if (output[0] == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	}

	if (output[1] == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
	}

	if (output[2] == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
	}

	if (output[3] == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, 1);
	}

	if (output[4] == 0)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11,1);
	}

	if (output[5] == 0)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, 1);
	}

}


void
Capital_Letter ()
{
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_12, 1);
	//HAL_Delay(1000);
}

void
number ()
{
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1,1);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_10,1);
	//HAL_Delay(1000);
}

void
chuyen ()
{
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_1,0);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_5,0);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_10,0);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_4,0);
	HAL_GPIO_WritePin (GPIOB, GPIO_PIN_11,0);
	HAL_GPIO_WritePin (GPIOA, GPIO_PIN_12,0);
	//HAL_Delay(50);
}

//Phần code dưới là xử lý thông tin bluetooth
uint8_t state_send = 0;
uint8_t state_pause = 0;
uint8_t j = 0;

//Khai báo biến chống rung nút nhấn
uint8_t is_debounced1 = 1;
uint32_t debounce_timer1 = 0;

uint8_t is_debounced2 = 1;
uint32_t debounce_timer2 = 0;

void
HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin)
{
	//saving data
	if(GPIO_Pin == GPIO_PIN_5)
	{
		//if(state_send == 2) state_send = 0;
		//else state_send +=1;
		is_debounced2 = 0;
		debounce_timer2 = HAL_GetTick();
	}

	//pausing data
	else if(GPIO_Pin == GPIO_PIN_0)
	{
		//if(state_pause == 2) state_pause = 0;
		//else state_pause +=1;
		is_debounced1 = 0;
		debounce_timer1 = HAL_GetTick();
	}
}

void
HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_DMA (&huart2, UART1_rxBuffer, 12);
		  /*if(huart->Instance==huart2.Instance)
		  {
			data = Rx_Buf;
			if(Rx_Buf == 46){
				//Kiểm tra xem có ký tự kết thúc văn bản ./. chưa. Nếu đã kết thúc thì status2 = 1;
				if(status1 == 93){
					if(status == 46){
						status2 = 1;
						status = 0;
						status1 = 0;
					}
				}
			}
			else{
				status1 +=Rx_Buf;
				status +=Rx_Buf;
			}
			HAL_UART_Receive_IT(&huart1,&Rx_Buf,1);
		  }*/
}

void
Saving ()
{
	//try to include a message like: char message[300] "Book mark index is 2024"
	char pData[5] = "Saved";
	HAL_UART_Transmit(&huart2, (uint8_t *)pData, 5 , 1000);

	 	 /*lcd_clear(&p_LCD);
	 	 lcd_i2c_init(&p_LCD, &hi2c1, 16, 2, 0x27<<1);
	 	 lcd_set_cursor(&p_LCD, 0, 0);
	 	 lcd_send_string(&p_LCD, "Saved");*/
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int
main (void)
{
  /* USER CODE BEGIN 1 */

//B1: 1; B8: 2; B10: 3; B4: 4; B11: 5; B3: 6

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
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  //HAL_UART_Receive_IT(&huart1,&Rx_Buf,1);
  uint32_t timing = HAL_GetTick();
  uint8_t capital_letter = 0;
  uint8_t number_state = 0;
  int t = 0;

  HAL_UART_Receive_DMA (&huart2, UART1_rxBuffer, 12);
  lcd_i2c_init (&p_LCD, &hi2c1, 16, 2, 0x27<<1);
  lcd_set_cursor (&p_LCD, 0, 0);
  lcd_send_string (&p_LCD, "Started reading");
  HAL_Delay (2000);
  lcd_clear (&p_LCD);

  //Tốc độ
  //float rate=HAL_ADC_GetValue(&hadc1);
  int speed = 2000;
  /*if(rate <= 1000) speed = 2000;
  	 else if(rate <= 1000) speed = 1000;
	 else if(rate <= 2000) speed = 500;
	 else speed = 200;
	*/
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//Chong rung ngat
	if ((is_debounced1 == 0) && ((HAL_GetTick() - debounce_timer1) >= 100))
	{
	  	is_debounced1 = 1;
	  	HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_13);
	  	if(state_pause == 2)
	  	{
	  		state_pause = 0;
	  	}

	  	else
	  	{
	  		state_pause += 1;
	  	}
	}

	//In du lieu
	if (state_pause == 0)
	{
		lcd_set_cursor (&p_LCD,0,0);
		lcd_clear (&p_LCD);
	  	for (int i = 0; i < strlen ((const char *) UART1_rxBuffer); i++)
	  	{
	  		input = UART1_rxBuffer[t];
				//printing in LCD
			lcd_i2c_init(&p_LCD, &hi2c1, 16, 2, 0x27<<1);
			if (i > 31)
			{
				lcd_set_cursor(&p_LCD,0,0);
				lcd_clear(&p_LCD);
				i = -1;
				continue;
			}

			else if (i>15)
			{
				lcd_set_cursor(&p_LCD, i-16, 1);
				lcd_send_data(&p_LCD, UART1_rxBuffer[t]);
			}

			else
			{
				lcd_set_cursor(&p_LCD, i, 0);
				lcd_send_data(&p_LCD, UART1_rxBuffer[t]);
			}

			//printing by solenoid
			if ((input >= 65) && (input <= 90))
			{
				input += 32;
				capital_letter = 1;
			}

			else if ((input >= '0') && (input <= '9'))
			{
				number_state = 1;
				input += 49;
			}

			for (int j=0; j < sizeof(ascii);j++)
			{
				if (input == ascii[j])
				{
					output = dot[j];
					if (capital_letter == 1)
					{
						while ((HAL_GetTick() - timing) <= speed / 2) Capital_Letter();
						timing = HAL_GetTick();
					}

					else if (number_state == 1)
					{
						while ((HAL_GetTick() - timing) <= speed / 2) number();
						timing = HAL_GetTick();
					}

					while ((HAL_GetTick() - timing) <= speed)
					{
						Display_by_Solenoid(output);
					}

					timing = HAL_GetTick();

							//transition
					while ((HAL_GetTick() - timing) <= 50) chuyen();

					timing = HAL_GetTick();
					break;
					}
				}
	  	//move to next character
	  		t++;

	  		if ((is_debounced1 == 0) && ((HAL_GetTick() - debounce_timer1) >= 100))
	  		{
	  			is_debounced1 = 1;
	  			HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_13);
	  			if(state_pause == 2)
	  			{
	  				state_pause = 0;
	  			}

	  			else
	  			{
	  				state_pause += 1;
	  			}
	  		}

	  		if (state_pause == 1)
	  		{
	     	  	lcd_set_cursor(&p_LCD,0,0);
	     	  	lcd_clear(&p_LCD);
	     	  	lcd_send_string(&p_LCD, "Pausing");
	     	  	break;
	  		}


	  		if ((is_debounced2 == 0) && ((HAL_GetTick() - debounce_timer2) >= 100))
	  		{
	  			is_debounced2 = 1;
	  			HAL_GPIO_TogglePin (GPIOC, GPIO_PIN_13);
	  			if(state_send == 2) state_send = 0;
	  			else state_send += 1;
	  		}

	  		if (state_send == 1)
	  		{
	  			Saving();
	  		}

	  		if (t == strlen((const char *) UART1_rxBuffer))
	  		{
				t = 0;
				lcd_set_cursor (&p_LCD, 0, 0);
				lcd_clear (&p_LCD);
				lcd_send_string (&p_LCD, "Finish reading");
				break;
	  		}
	  	}

	  	while (state_pause == 1){
	  		lcd_set_cursor(&p_LCD,0,0);
	  		lcd_clear(&p_LCD);
	  		lcd_send_string(&p_LCD, "Pausing");

	  		if (state_send == 1)
	  		{
	  			Saving();
	  		}

	  		if ((is_debounced1 == 0) && ((HAL_GetTick() - debounce_timer1) >= 100))
	  		{
	  			is_debounced1 = 1;
	  			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  			if(state_pause == 2)
	  			{
	  				state_pause = 0;
	  			}

	  			else
	  			{
	  				state_pause +=1;
	  			}
	  		}

	  		if (state_pause == 0)
	  		{
	  			continue;
	  		}
	  	}
	}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB10 PB11 PB12
                           PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
/* Coding convention sucks <(") */
