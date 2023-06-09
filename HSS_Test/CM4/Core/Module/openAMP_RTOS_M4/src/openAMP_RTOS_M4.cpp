/*
 * openAMP_RTOS_M4.c
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */



#include "openAMP_RTOS_M4/include/openAMP_RTOS_M4/openAMP_RTOS_M4.h"



/* Private variables ---------------------------------------------------------*/
static openamp_type message_recv = {0,};

static volatile int message_received;
static openamp_type received_data;

static struct rpmsg_endpoint rp_endpoint;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
               size_t len, uint32_t src, void *priv)
{
	  received_data = *((openamp_type*) data);

	  size_t len_=  len;

	  message_received=1;

  return 0;
}

openamp_type receive_message(void)
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
		message_recv = receive_message();

		//int msg_leng = message_recv.data17_length_;

		//char send_buf[msg_leng + 1];

		//strncpy (send_buf, message_recv.data17_, (msg_leng+1));   // get the message from the client

		//memcpy (send_buf, message_recv.data17_, (msg_leng+1));

		//send_buf[msg_leng] = '\0';

		//printf("m4 got msg from m7: %s \r\n", send_buf);

		int32_t status = OPENAMP_send(&rp_endpoint, &message_recv, sizeof(message_recv));
		if (status < 0)
		{
		//  Error_Handler();
		}
		message_received = 0;
	}

	return;
}



