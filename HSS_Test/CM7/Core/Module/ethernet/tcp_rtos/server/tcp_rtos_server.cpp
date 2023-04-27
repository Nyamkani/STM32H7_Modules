/*
 * tcprtosserver.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>
#include <string>
#include <main.h>
static struct netconn *conn, *newconn;
//static struct netbuf *buf;
//static char msg[1024];  //receiving msg buffer
//static char smsg[1100];	//to send temp buffer

//static ip_addr_t *addr;
//static unsigned short port;

/*Rtos thread handle*/
osThreadId TcpServerHandle;

/*netif*/
extern struct netif gnetif;

#define ServerPort (int) 10


std::string eth_data_;
extern osMessageQId myQueue01Handle;
extern osMessageQId TCPSendQueueHandle;

_Message* tcp_recv_msg_ = NULL;

//memory pool
extern osPoolId Pool_ID ;


/*------------------------------------Server-----------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/**** Send RESPONSE every time the client sends some data ******/
static void StartTCPServerTask(void const *arg)
{
	err_t err, accept_err;
	struct netbuf *buf;
	void* temp_data;
	uint16_t remain_leng = 0;

	uint16_t repeat_num = 0;
	uint16_t remain_data = 0;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	if (conn!=NULL)
	{
		/* Bind connection to the server port. */
		err = netconn_bind(conn, IP_ADDR_ANY, ServerPort);

		if (err == ERR_OK)
		{
			/* Tell connection to go into listening mode. */
			netconn_listen(conn);

			while (1)
			{
				/* Grab new connection. */
				accept_err = netconn_accept(conn, &newconn);

				/* Process the new connection. */
				if (accept_err == ERR_OK)
				{

					/* receive the data from the client */
					while (netconn_recv(newconn, &buf) == ERR_OK)
					{
						do
						{
							//netbuf_data(buf, &temp_data, &leng);
							remain_leng = buf->p->len;

							//1024 is magic number
							repeat_num = remain_leng / max_num_buf_;
							remain_data = remain_leng % max_num_buf_;

							for(int i =1; i<= repeat_num; i++ )
							{
								//Dynamic allocate memory
								tcp_recv_msg_ = (_Message *)osPoolAlloc(Pool_ID);

								//insert the data to msg_ID
								tcp_recv_msg_->id_ = 0x10;

								//insert the data to msg_DATA
								strncpy(tcp_recv_msg_->data_,
										(char* )((int)(buf->p->payload) + (i-1)*max_num_buf_),
										max_num_buf_);

								//insert the data to msg_DATA_length
								tcp_recv_msg_->leng_ = max_num_buf_;

								//send msg
								osMessagePut(myQueue01Handle, (uint32_t)tcp_recv_msg_, osWaitForever); //enqueue

								//free msg
								osPoolFree(Pool_ID, tcp_recv_msg_);
							}

							//Dynamic allocate memory
							tcp_recv_msg_ = (_Message *)osPoolAlloc(Pool_ID);

							//insert the data to msg
							tcp_recv_msg_->id_ = 0x10;

							strncpy(tcp_recv_msg_->data_,
									(char* )((int)buf->p->payload + (repeat_num)*max_num_buf_),
									remain_data);

							//tcp_recv_msg_->data_ = (char*)temp_data;
							tcp_recv_msg_->leng_ = remain_data;


							//send msg
							osMessagePut(myQueue01Handle, (uint32_t)tcp_recv_msg_, osWaitForever); //enqueue

							//free msg
							osPoolFree(Pool_ID, tcp_recv_msg_);

							repeat_num = 0;
							remain_data = 0;


						}
						while (netbuf_next(buf) >=0);

						repeat_num = 0;
						remain_data = 0;

						netbuf_delete(buf);
					}
					/* Close connection and discard connection identifier. */
					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}
	}
	else
	{
		netconn_delete(conn);
		//vTaskDelete(NULL);
	}
}



void TcpServerDelete()
{
	  if((netif_is_link_up(&gnetif))) return;

	  if(newconn == NULL && conn == NULL) return;

	  if(netconn_close(newconn) != ERR_OK) return;

	  if(netconn_delete(newconn) != ERR_OK) return;

	  if(netconn_delete(conn) != ERR_OK) return;

	  vTaskDelete(TcpServerHandle);

	  return;
}

void TcpServerRecvBuffer(const char *data)
{
	std::string string_buf_(data);

	eth_data_ = string_buf_;

	return;
}



void TcpServerSend(const char *data)
{
	//if(newconn != NULL)
	//{


		// send the data to the connected connection
		netconn_write(newconn, data, strlen(data), NETCONN_COPY);
		// relaese the semaphore
		//sys_sem_signal(&tcpsem);
	//}
	return;
}


void TcpServerInit(void)
{
	if(newconn == NULL)
	{
		/* definition and creation of TCPServerTask */
		osThreadDef(TCPServerTask, StartTCPServerTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *8);
		TcpServerHandle = osThreadCreate(osThread(TCPServerTask), NULL);
	}
}


