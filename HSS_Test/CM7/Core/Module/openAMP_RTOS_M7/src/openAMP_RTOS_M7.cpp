/*
 * openAMP_RTOS_M7.c
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */


#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>


/* Private variables ---------------------------------------------------------*/
static openamp_type message_recv = {0,};

static volatile int message_received = 0;
static volatile int service_created;
static openamp_type received_data;
static struct rpmsg_endpoint rp_endpoint;


/* Extern variables ---------------------------------------------------------*/
osSemaphoreId osSemaphore_ChannelCreation;
osSemaphoreId osSemaphore_MessageReception;

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
                size_t len, uint32_t src, void *priv)
{
  received_data = *((openamp_type*) data);

  osSemaphoreRelease(osSemaphore_MessageReception);

  message_received = 1;

  return 0;
}

openamp_type receive_message(void)
{
	  received_data.command_= 0xff;
	  uint32_t status = 0;

	  while (received_data.command_ == 0xff)
	  {
	    status = osSemaphoreWait(osSemaphore_MessageReception , 0xffff);

	   if (status != osOK) break;

	    //OPENAMP_check_for_message();
	  }
	  return received_data;
}

  void service_destroy_cb(struct rpmsg_endpoint *ept)
{
  /* this function is called while remote endpoint as been destroyed, the
   * service is no more available
   */
	  service_created = 0 ;
}

void new_service_cb(struct rpmsg_device *rdev, const char *name, uint32_t dest)
{
  /* create a endpoint for rmpsg communication */
  OPENAMP_create_endpoint(&rp_endpoint, name, dest, rpmsg_recv_callback,
                          service_destroy_cb);

  osSemaphoreRelease (osSemaphore_ChannelCreation);

  service_created = 1;
}


void OpenAMPInit()
{
	//int32_t timeout;
	/* USER CODE BEGIN Boot_Mode_Sequence_2 */
	/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
	HSEM notification */
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/*Take HSEM */
	HAL_HSEM_FastTake(HSEM_ID_0);
	/*Release HSEM in order to notify the CPU2(CM4)*/
	HAL_HSEM_Release(HSEM_ID_0,0);
	/* wait until CPU2 wakes up from stop mode */

	uint32_t timeout = 0xFFFF;
	while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
	if ( timeout < 0 )
	{
		Error_Handler();
	}

	/* Define used semaphore */
	osSemaphoreDef(CHN_CREAT);
	osSemaphoreDef(MSG_RECPT);

	/* Create the semaphore */
	osSemaphore_ChannelCreation  = osSemaphoreCreate(osSemaphore(CHN_CREAT) , 1);
	osSemaphore_MessageReception = osSemaphoreCreate(osSemaphore(MSG_RECPT) , 1);

	/* Initialize the mailbox use notify the other core on new message */
	MAILBOX_Init();

	/* Initialize the rpmsg endpoint to set default addresses to RPMSG_ADDR_ANY */
	rpmsg_init_ept(&rp_endpoint, RPMSG_CHAN_NAME, RPMSG_ADDR_ANY, RPMSG_ADDR_ANY,
				 NULL, NULL);

	/* Initialize OpenAmp and libmetal libraries */
	if (MX_OPENAMP_Init(RPMSG_MASTER, new_service_cb)!= HAL_OK) Error_Handler();

	/*
	* The rpmsg service is initiate by the remote processor, on A7 new_service_cb
	* callback is received on service creation. Wait for the callback
	*/
	OPENAMP_Wait_EndPointready(&rp_endpoint);

	return;
}

void OpenAMPReadTask(void const *argument)
{
	openamp_type test;
	//osDelay(1);
	//while(message_received == 0)
	//{

	while(1)
	{
		OPENAMP_check_for_message();

		/* Receive the massage from the remote CPU */
		message_recv = receive_message();

		if(message_recv.command_ != 0xff)
		{
			//int msg_leng = message_recv.data17_length_;

			//char send_buf[msg_leng + 1];

			//strncpy(send_buf, message_recv.data17_, (msg_leng+1));   // get the message from the client

			//send_buf[msg_leng] = '\0';

			//printf("m7 got msg from m4 %s\r\n", send_buf);

			//*send_buf = '\0';
		}
		else
		{
			printf("m7 got no msg from m4  %d\r\n", &message_recv.command_);
		}


	}
		//}

	return;
}




void OpenAMPSend(const char* msg, int msg_leng)
{

	openamp_type test;

	test.data1_ = 1;
	test.data2_ = 2;
	test.data3_ = 3;
	test.data4_ = 4;
	test.data5_ = 5;
	test.data6_ = 6;
	test.data7_ = 7;
	test.data8_ = 8;
//	test.data9_ = 9;

	//strncpy (test.data17_, msg, msg_leng);
	//memcpy(test.data17_, msg, msg_leng);

	//test.data17_length_ = msg_leng;

	size_t size = sizeof(test);

	/* Send the massage to the remote CPU */
	int status = OPENAMP_send(&rp_endpoint, &test, size);

	if (status < 0) Error_Handler();

	return;
}


void OpenAMPChkMsgtask(void const *argument)
{
	while(1)
	{
		OPENAMP_check_for_message();

		osDelay(1);
	}
	return;
}





void OpenAMPInit_M7()
{

	OpenAMPInit();

	/* Create the Thread */
	osThreadDef(OpenAMP_ReadTask, OpenAMPReadTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *2);
	osThreadCreate(osThread(OpenAMP_ReadTask), NULL);

	osThreadDef(OpenAMP_ChkTask, OpenAMPChkMsgtask, osPriorityNormal, 0, 128);
	osThreadCreate(osThread(OpenAMP_ChkTask), NULL);

	return;
}