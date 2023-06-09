/*
 * tcprtosserver.cpp
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */
#include <ethernet/tcp_rtos/client/tcp_rtos_client.h>


static struct netconn *conn;
static struct netbuf *buf;
static char msg[100];  //receiving msg buffer
static char smsg[200];	//to send temp buffer

static ip_addr_t *addr, dest_addr;
static unsigned short port, dest_port;

#define ClientPort (int) 11
#define ServerPort (int) 10

/*------------------------------------Client-----------------------------------------*/
/*-----------------------------------------------------------------------------------*/

// tcpsem is the binary semaphore to prevent the access to tcpsend
//sys_sem_t tcpsem;

void TcpClientSend(const char *data)
{
	// send the data to the connected connection
	netconn_write(conn, data, strlen(data), NETCONN_COPY);
	// relaese the semaphore
	//sys_sem_signal(&tcpsem);
}

static void TcpClientThread(void *arg)
{
	err_t err, connect_error;

	while(1)
	{
		/* Create a new connection identifier. */
		conn = netconn_new(NETCONN_TCP);

		if (conn != NULL)
		{
			/* Bind connection to the port number 11(port of the Client). */
			err = netconn_bind(conn, IP_ADDR_ANY, ClientPort);

			if (err == ERR_OK)
			{
				/* The destination IP address of the computer */
				IP_ADDR4(&dest_addr, 192, 168, 1, 25);
				dest_port = ServerPort;  // this. 11, server port 10

				/* Connect to the TCP Server */
				connect_error = netconn_connect(conn, &dest_addr, dest_port);

				// If the connection to the server is established, the following will continue, else delete the connection
				if (connect_error == ERR_OK)
				{

					while (1)
					{
						/* wait until the data is sent by the server */
						if (netconn_recv(conn, &buf) == ERR_OK)
						{
							/* Extract the address and port in case they are required */
							addr = netbuf_fromaddr(buf);  // get the address of the client
							port = netbuf_fromport(buf);  // get the Port of the client

							/* If there is some data remaining to be sent, the following process will continue */
							do
							{

								strncpy (msg, (char*)buf->p->payload, buf->p->len);   // get the message from the server

								// Or modify the message received, so that we can send it back to the server
								sprintf (smsg, "\"%s\" was sent by the Server\n", msg);

								// send the data to the TCP Server
								//tcpsend(smsg);

								memset (msg, '\0', 100);  // clear the buffer
							}
							while (netbuf_next(buf) >0);

							netbuf_delete(buf);
						}
						else { break;}
					}
				}

				else
				{
					/* Close connection and discard connection identifier. */
					netconn_close(conn);
					netconn_delete(conn);
				}
			}
			else
			{
				// if the binding wasn't successful, delete the netconn connection
				netconn_delete(conn);
			}
		}
		/* Close connection and discard connection identifier. */
		netconn_close(conn);
		netconn_delete(conn);

	}

	vTaskDelete(NULL);
}


/*
static void tcpsend_thread (void *arg)
{
	for (;;)
	{
		sprintf (smsg, "index value = %d\n", indx++);
		// semaphore must be taken before accessing the tcpsend function
		//sys_arch_sem_wait(&tcpsem, 500);
		// send the data to the server
		tcpsend(smsg);
		osDelay(500);
	}
}
*/

void TcpClientInit(void)
{
	//sys_sem_new(&tcpsem, 0);  // the semaphore would prevent simultaneous access to tcpsend
	sys_thread_new("TcpClientThread", TcpClientThread, NULL, DEFAULT_THREAD_STACKSIZE, osPriorityNormal);
	//sys_thread_new("tcpsend_thread", tcpsend_thread, NULL, DEFAULT_THREAD_STACKSIZE,osPriorityNormal);
}

