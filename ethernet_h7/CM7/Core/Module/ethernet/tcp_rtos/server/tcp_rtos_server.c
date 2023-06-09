/*
 * tcprtosserver.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>

static struct netconn *conn, *newconn;
static struct netbuf *buf;
static char msg[100];  //receiving msg buffer
static char smsg[200];	//to send temp buffer

static ip_addr_t *addr;
static unsigned short port;

/*Rtos thread handle*/
osThreadId TcpServerHandle;

/*netif*/
extern struct netif gnetif;

#define ServerPort (int) 10

/*------------------------------------Server-----------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/**** Send RESPONSE every time the client sends some data ******/
static void StartTCPServerTask(void const *arg)
{
	err_t err, accept_err;

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
						/* Extrct the address and port in case they are required */
						addr = netbuf_fromaddr(buf);  // get the address of the client
						port = netbuf_fromport(buf);  // get the Port of the client

						/* If there is some data remaining to be sent, the following process will continue */
						do
						{
							strncpy (msg, (char* )buf->p->payload, buf->p->len);   // get the message from the client

							//for test debug
							//strncpy (char_ethernet, (char* )buf->p->payload, buf->p->len);   // get the message from the client

							//enter Queue and parsing
							/*

							TcpServerParsingSeq();

							*/
							// Or modify the message received, so that we can send it back to the client
							//response
							int len = sprintf (smsg, "\"%s\" was sent by the Client\n", msg);

							netconn_write(newconn, smsg, len, NETCONN_COPY);  // send the message back to the client

							memset (msg, '\0', sizeof(msg));  // clear the buffer
						}
						while (netbuf_next(buf) >0);

						netbuf_delete(buf);
					}

					/* Close connection and discard connection identifier. */
					netconn_close(newconn);
					netconn_delete(newconn);
				}
			}
		}
		else
		{
			netconn_delete(conn);
		}
	}
	vTaskDelete(NULL);
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


void TcpServerSend(const char *data)
{
	if(newconn != NULL)
	{
		// send the data to the connected connection
		netconn_write(conn, data, strlen(data), NETCONN_COPY);
		// relaese the semaphore
		//sys_sem_signal(&tcpsem);
	}
	return;
}


void TcpServerInit(void)
{
	if(newconn == NULL)
	{
		/* definition and creation of TCPServerTask */
		osThreadDef(TCPServerTask, StartTCPServerTask, osPriorityNormal, 0, DEFAULT_THREAD_STACKSIZE);
		TcpServerHandle = osThreadCreate(osThread(TCPServerTask), NULL);
	}
}


