/*
 * openAMP_RTOS_M7.c
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */


#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>


/* Private variables ---------------------------------------------------------*/
static  uint32_t message = 0;
static volatile int message_received;
static volatile int service_created;
static volatile unsigned int received_data;
static struct rpmsg_endpoint rp_endpoint;

/* Extern variables ---------------------------------------------------------*/
osSemaphoreId osSemaphore_ChannelCreation;
osSemaphoreId osSemaphore_MessageReception;

/* Private function prototypes -----------------------------------------------*/
static void StartOpenAMP_Thread(void const *argument);
/* Private functions ---------------------------------------------------------*/

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
                size_t len, uint32_t src, void *priv)
{
  received_data = *((unsigned int *) data);

  osSemaphoreRelease (osSemaphore_MessageReception);

  return 0;
}

unsigned int receive_message(void)
{
  received_data = -1U;
  uint32_t status = 0;

  while (received_data == -1U)
  {
    status = osSemaphoreWait(osSemaphore_MessageReception , 0xffff);

    if (status != osOK)
      break;

    OPENAMP_check_for_message();
  }

  return received_data;
}

  void service_destroy_cb(struct rpmsg_endpoint *ept)
{
  /* this function is called while remote endpoint as been destroyed, the
   * service is no more available
   */
}

void new_service_cb(struct rpmsg_device *rdev, const char *name, uint32_t dest)
{
  /* create a endpoint for rmpsg communication */
  OPENAMP_create_endpoint(&rp_endpoint, name, dest, rpmsg_recv_callback,
                          service_destroy_cb);
  osSemaphoreRelease (osSemaphore_ChannelCreation);
}


/**
  * @brief  Semaphore Test.
  * @param  argument: Not used
  * @retval None
  */
static void StartOpenAMP_Thread(void const *argument)
{
  int32_t status;
  //int32_t timeout;

  	/* Define used semaphore */
  	osSemaphoreDef(CHN_CREAT);
  	osSemaphoreDef(MSG_RECPT);

  	/* Create the semaphore */
  	osSemaphore_ChannelCreation  = osSemaphoreCreate(osSemaphore(CHN_CREAT) , 1);
  	osSemaphore_MessageReception = osSemaphoreCreate(osSemaphore(MSG_RECPT) , 1);

  /* Initialize the mailbox use notify the other core on new message */
  MAILBOX_Init();

  /* After starting the FreeRTOS kernel, Cortex-M7 will release Cortex-M4  by means of
     HSEM notification */

  /*HW semaphore Clock enable*/
  //__HAL_RCC_HSEM_CLK_ENABLE();

  /*Take HSEM */
  //HAL_HSEM_FastTake(HSEM_ID_0);

  /*Release HSEM in order to notify the CPU2(CM4)*/
  //HAL_HSEM_Release(HSEM_ID_0,0);

  /* wait until CPU2 wakes up from stop mode */
 // timeout = 0xFFFF;
  //while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
  //if ( timeout < 0 )
  //{
  //  Error_Handler();
  //}

  /* Initialize the rpmsg endpoint to set default addresses to RPMSG_ADDR_ANY */
  rpmsg_init_ept(&rp_endpoint, RPMSG_CHAN_NAME, RPMSG_ADDR_ANY, RPMSG_ADDR_ANY,
                 NULL, NULL);

  /* Initialize OpenAmp and libmetal libraries */
  if (MX_OPENAMP_Init(RPMSG_MASTER, new_service_cb)!= HAL_OK)
    Error_Handler();

  /*
   * The rpmsg service is initiate by the remote processor, on A7 new_service_cb
   * callback is received on service creation. Wait for the callback
   */
  OPENAMP_Wait_EndPointready(&rp_endpoint);

  /* Send the massage to the remote CPU */
  status = OPENAMP_send(&rp_endpoint, &message, sizeof(message));
  osDelay(1);

  if (status < 0)
  {
    Error_Handler();
  }

  while (message < 100)
  {
   /* Receive the massage from the remote CPU */
    message = receive_message();
    message++;

   /* Send the massage to the remote CPU */
    status = OPENAMP_send(&rp_endpoint, &message, sizeof(message));
    osDelay(1);

    if (status < 0)
    {
      Error_Handler();
    }
  }

  /* wait that service is destroyed on remote side */
  while(service_created)
  {
    OPENAMP_check_for_message();
  }

  /* Deinitialize OpenAMP */
  OPENAMP_DeInit();

  while(1)
  {
    //BSP_LED_Toggle(LED_GREEN);
    osDelay(400);
  }
}



void OpenAMPInit_M7()
{
	/* Create the Thread */
	osThreadDef(OpenAMP_Thread, StartOpenAMP_Thread, osPriorityNormal, 0, appliSTACK_SIZE);
	osThreadCreate(osThread(OpenAMP_Thread), NULL);

	return;
}
