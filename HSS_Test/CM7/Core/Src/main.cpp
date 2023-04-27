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
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <main.h>
#include "cmsis_os.h"
#include "fatfs.h"
#include "lwip.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>
#include <fatfs_h7/include/fatfs_h7/fatfs_h7.h>
#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>
#include "api_debug/api_debug.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern _Message* tcp_recv_msg_;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SD_HandleTypeDef hsd1;

MDMA_HandleTypeDef MDMA_SDMMC_Handle;
//task handle
osThreadId InitTaskHandle;
osThreadId Task1Handle;
osThreadId Task2Handle;

//msg q handle
osMessageQId myQueue01Handle;
osMessageQId TCPSendQueueHandle;

//memory pool
osPoolId Pool_ID ;


//eventflag
//EventGroupHandle_t evtGrpHandle;
//uint32_t evtFlag = 0x11;
//uint32_t evtFlag2 = 0x02;

/* USER CODE BEGIN PV */

uint32_t timeout;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_MDMA_Init(void);
static void MX_SDMMC1_SD_Init(void);
void StartInitTask(void const * argument);
void StartTask1(void const * argument);
void StartTask2(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#ifdef __cplusplus
extern "C"{
#endif


int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
	  ITM_SendChar(*ptr++);
  }
  return len;
}

#ifdef __cplusplus
}
#endif

/* USER CODE END 0 */






/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
 // int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/

  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
	 Error_Handler();
  }

/* USER CODE END Boot_Mode_Sequence_1 */
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
  MX_MDMA_Init();
  MX_SDMMC1_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of InitTask */
  osThreadDef(InitTask, StartInitTask, osPriorityNormal, 0, 512);
  InitTaskHandle = osThreadCreate(osThread(InitTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
  * @brief SDMMC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDMMC1_SD_Init(void)
{

  /* USER CODE BEGIN SDMMC1_Init 0 */

  /* USER CODE END SDMMC1_Init 0 */

  /* USER CODE BEGIN SDMMC1_Init 1 */

  /* USER CODE END SDMMC1_Init 1 */
  hsd1.Instance = SDMMC1;
  hsd1.Init.ClockEdge = SDMMC_CLOCK_EDGE_RISING;
  hsd1.Init.ClockPowerSave = SDMMC_CLOCK_POWER_SAVE_DISABLE;
  hsd1.Init.BusWide = SDMMC_BUS_WIDE_4B;
  hsd1.Init.HardwareFlowControl = SDMMC_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd1.Init.ClockDiv = 0;
  if (HAL_SD_Init(&hsd1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SDMMC1_Init 2 */

  /* USER CODE END SDMMC1_Init 2 */

}


/**
  * Enable MDMA controller clock
  * Configure MDMA for global transfers
  *   hmdma_mdma_channel40_sdmmc1_end_data_0
  */
static void MX_MDMA_Init(void)
{

  /*##-1- Enable the MDMA clock ###############################################*/
  __HAL_RCC_MDMA_CLK_ENABLE();
  /* Local variables */

  /* Configure MDMA channel MDMA_Channel0 */
  /* Configure MDMA request MDMA_SDMMC_Handle */

  /*##-2- Select the MDMA instance to be used for the transfer : MDMA_Channel0 #*/
  MDMA_SDMMC_Handle.Instance = MDMA_Channel0;

  HAL_MDMA_DeInit(&MDMA_SDMMC_Handle);

  /*##-3- Initialize the MDMA channel (with liked list node 0 parameters) ####*/
  MDMA_SDMMC_Handle.Init.Request = MDMA_REQUEST_SDMMC1_END_DATA;
  MDMA_SDMMC_Handle.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
  MDMA_SDMMC_Handle.Init.Priority = MDMA_PRIORITY_LOW;
  MDMA_SDMMC_Handle.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;

  MDMA_SDMMC_Handle.Init.SourceInc = MDMA_SRC_INC_BYTE;
  MDMA_SDMMC_Handle.Init.DestinationInc = MDMA_DEST_INC_BYTE;

  MDMA_SDMMC_Handle.Init.SourceDataSize = MDMA_SRC_DATASIZE_BYTE;
  MDMA_SDMMC_Handle.Init.DestDataSize = MDMA_DEST_DATASIZE_BYTE;
  MDMA_SDMMC_Handle.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
  MDMA_SDMMC_Handle.Init.BufferTransferLength = 1;
  MDMA_SDMMC_Handle.Init.SourceBurst = MDMA_SOURCE_BURST_SINGLE;
  MDMA_SDMMC_Handle.Init.DestBurst = MDMA_DEST_BURST_SINGLE;


  MDMA_SDMMC_Handle.Init.SourceBlockAddressOffset = 0;
  MDMA_SDMMC_Handle.Init.DestBlockAddressOffset = 0;

  if (HAL_MDMA_Init(&MDMA_SDMMC_Handle) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure post request address and data masks */
  if (HAL_MDMA_ConfigPostRequestMask(&MDMA_SDMMC_Handle, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }

  /* MDMA interrupt initialization */
  /* MDMA_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MDMA_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(MDMA_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  GPIO_InitStruct.Pin = uSD_Detect_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(uSD_Detect_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CEC_CK_MCO1_Pin */
  GPIO_InitStruct.Pin = CEC_CK_MCO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(CEC_CK_MCO1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartInitTask */
/**
  * @brief  Function implementing the InitTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartInitTask */
void StartInitTask(void const * argument)
{
	/* init code for LWIP */
	MX_LWIP_Init();
	/* USER CODE BEGIN 5 */

	//0. check printf alive
	printf("Hello World!\n");

	//1. TCP server initialize
	TcpServerInit();

	//2. FATfs Initialize
	FatFsInit();
	//FatFsTest("test.txt");

	//3. openAMP_h7 initialize
	OpenAMPInit_M7();

	//message pool
	 osPoolDef (Pool_ID_, sizeof(*tcp_recv_msg_), &tcp_recv_msg_);
	 Pool_ID = osPoolCreate(osPool(Pool_ID_));

	//send data from tcp data to main queue
	osMessageQDef(myQueue01, sizeof(*tcp_recv_msg_), &tcp_recv_msg_);
	myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

	//main to tcp sender
	//osMessageQDef(tcpsendq, 16, _Message);
	//TCPSendQueueHandle = osMessageCreate(osMessageQ(tcpsendq), NULL);

	/* definition and creation of Task1 */
	osThreadDef(Task1, StartTask1, osPriorityLow, 0, configMINIMAL_STACK_SIZE *2);
	Task1Handle = osThreadCreate(osThread(Task1), NULL);

	/* definition and creation of Task2 */
	osThreadDef(Task2, StartTask2, osPriorityHigh, 0, configMINIMAL_STACK_SIZE *6);
	Task2Handle = osThreadCreate(osThread(Task2), NULL);

	/*Delete Itself*/
    vTaskDelete(NULL);

  /* USER CODE END 5 */
}

/* USER CODE BEGIN StartTask1 */
/**
* @brief Function implementing the Task1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Task1 */
void StartTask1(void const *argument)
{
  /* USER CODE BEGIN StartCommonSensorTask */

	const TickType_t xTime = pdMS_TO_TICKS(5);

	TickType_t xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */

  for(;;)
  {
	 osDelay(1);
	//vTaskDelayUntil(&xLastWakeTime, xTime);
  }
  /* USER CODE END StartTask1 */
}

/* USER CODE BEGIN StartTask2 */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END StartTask2 */

void StartTask2(void const *argument)
{
  /* USER CODE BEGIN Task2 */

	//const TickType_t xTime = pdMS_TO_TICKS(2);

	//TickType_t xLastWakeTime = xTaskGetTickCount();

	_Message* recv_msg = NULL;
	_Message send_msg;
	char* send_buf = NULL;
	//char char_temp_buf[1024*3] = {0,};
	osEvent retVal;


  /* Infinite loop */
  for(;;)
  {
	  retVal = osMessageGet(myQueue01Handle, osWaitForever); //dequeue

	  if(retVal.status == osEventMessage)
	  {

		  	//message allocation
			recv_msg  = new _Message;

			//get data
			memcpy(recv_msg, (_Message*)retVal.value.p, sizeof(*tcp_recv_msg_));

			//get element
			send_buf = new char[recv_msg->leng_+1];
			//char send_buf[recv_msg->leng_ + 1];

			send_buf[recv_msg->leng_] = '\0';

			strncpy (send_buf, recv_msg->data_, recv_msg->leng_);   // get the message from the client

			//length check



			//check data length

			DebugDrive(recv_msg);
			//xEventGroupSetBits(evtGrpHandle, evtFlag);

			//send_msg.id_ = 0x11;
			//send_msg.data_ = (char*)recv_msg->data_;
			//send_msg.leng_ = recv_msg->leng_;

			//osMessagePut(TCPSendQueueHandle, (uint32_t)(&send_msg), 10); //enqueue


			if(recv_msg->leng_ != 1000)
			{
				printf("the message length has been currupted %d bytes. \r\n", recv_msg->leng_);
			}

			TcpServerSend(send_buf);

			delete send_buf;
			send_buf = NULL;
			delete recv_msg;
			recv_msg = NULL;
			//delete msg
			//delete tcp_recv_msg_->data_;

			//tcp_recv_msg_->data_ = NULL;

			//free msg
			//osPoolFree(Pool_ID, tcp_recv_msg_);

	  }

	//osDelay(1);

	//vTaskDelayUntil(&xLastWakeTime, xTime);

	//vTaskDelay(pdMS_TO_TICKS(80));
	}
  /* USER CODE END StartTask2 */
}













/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  /*Disable Speculative access*/
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*Set LwIP Heap */
  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x30020000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*RX & Tx Descriptors*/
  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.BaseAddress = 0x30040000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512B;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);


  /*openAMP Memory*/
  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.BaseAddress = 0x38000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*rtos memory protection*/
  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER4;
  MPU_InitStruct.BaseAddress = 0x24000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);




  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
