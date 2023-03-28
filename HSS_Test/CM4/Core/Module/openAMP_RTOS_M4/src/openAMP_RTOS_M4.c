/*
 * openAMP_RTOS_M4.c
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */



#include "openAMP_RTOS_M4/include/openAMP_RTOS_M4/openAMP_RTOS_M4.h"



/* Private variables ---------------------------------------------------------*/
static  uint32_t message;
static volatile int message_received;
static volatile unsigned int received_data;

static struct rpmsg_endpoint rp_endpoint;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

HSEM_TypeDef * HSEM_DEBUG= HSEM;

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
               size_t len, uint32_t src, void *priv)
{
  received_data = *((unsigned int *) data);
  message_received=1;

  return 0;
}

unsigned int receive_message(void)
{
  while (message_received == 0)
  {
    OPENAMP_check_for_message();
  }
  message_received = 0;

  return received_data;
}

void OpenAMPInit_M4()
{
	int32_t status = 0;

	/*HW semaphore Clock enable*/
	//__HAL_RCC_HSEM_CLK_ENABLE();

	/*HW semaphore Notification enable*/
	//HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

	/* When system initialization is finished, Cortex-M7 will release Cortex-M4  by means of
	HSEM notification */
	//HAL_PWREx_ClearPendingEvent();
	//HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);

	/*Clear Flags generated during the wakeup notification */
	//HSEM_COMMON->ICR |= ((uint32_t)__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	//HAL_NVIC_ClearPendingIRQ(HSEM2_IRQn);

	/* Add Cortex-M4 user application code here */

	/* Inilitize the mailbox use notify the other core on new message */
	MAILBOX_Init();

	/* Inilitize OpenAmp and libmetal libraries */
	if (MX_OPENAMP_Init(RPMSG_REMOTE, NULL)!= HAL_OK)
	Error_Handler();

	/* create a endpoint for rmpsg communication */
	status = OPENAMP_create_endpoint(&rp_endpoint, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY,
									rpmsg_recv_callback, NULL);
	if (status < 0)
	{
		Error_Handler();
	}

	/* Pingpong application*/
	/* Reveice an integer from the master, incremennt it and send back the result to the master*/
	while (message < 100)
	{
		message = receive_message();
		message++;
		status = OPENAMP_send(&rp_endpoint, &message, sizeof(message));
		if (status < 0)
		{
		  Error_Handler();
		}
	}

	/* Deinitialize OpenAMP */
	OPENAMP_DeInit();

	while(1)
	{
	}


	return;
}
