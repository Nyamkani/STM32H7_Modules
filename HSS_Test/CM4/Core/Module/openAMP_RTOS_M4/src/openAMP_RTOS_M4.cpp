/*
 * openAMP_RTOS_M4.c
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */



#include "openAMP_RTOS_M4/include/openAMP_RTOS_M4/openAMP_RTOS_M4.h"



/* Private variables ---------------------------------------------------------*/
static  char* message = 0;
static  char* message_recv = 0;

static volatile int message_received;
static volatile char* received_data;

static struct rpmsg_endpoint rp_endpoint;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
               size_t len, uint32_t src, void *priv)
{
	  received_data = ((char *) data);

	  message_received=1;

  return 0;
}

volatile char* receive_message(void)
{
 //while (message_received == 0)
  //{
   // OPENAMP_check_for_message();
  //}

  return received_data;
}

int OpenAMPInit()
{
	int32_t status = 0;

	/* Inilitize the mailbox use notify the other core on new message */
	MAILBOX_Init();

	/* Inilitize OpenAmp and libmetal libraries */
	status = MX_OPENAMP_Init(RPMSG_REMOTE, NULL);

	if (status < 0) return status;
//	Error_Handler();

	/* create a endpoint for rmpsg communication */
	status = OPENAMP_create_endpoint(&rp_endpoint, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY,
									rpmsg_recv_callback, NULL);

	return status;
}

void OpenAMPDrive()
{

	OPENAMP_check_for_message();


	if(message_received)
	{
		message_recv = (char*)receive_message();

		int msg_leng = strlen(message_recv);

		char send_buf[msg_leng + 1];

		strncpy (send_buf, message_recv, sizeof(send_buf));   // get the message from the client

		send_buf[msg_leng] = '\0';

		printf("m4 got msg from m7: %s \r\n", send_buf);

		int32_t status = OPENAMP_send(&rp_endpoint, &send_buf, (msg_leng+1));
		if (status < 0)
		{
		//  Error_Handler();
		}
		message_received = 0;
	}

	return;
}



