/*
 * tcprtosserver.cpp
 *
 *  Created on: May 23, 2022
 *      Author: kss
 */
#include <api_data_structure/include/api_data_structure/api_data_structure.h>
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>
#include <cstring>
#include <vector>
#include <main.h>

//main socket
static struct netconn *conn, *newconn;

/*Rtos thread handle*/
osThreadId TcpServerRecvHandle;
osThreadId TcpServerSendHandle;

/*netif*/
extern struct netif gnetif;

//port config
#define ServerPort (int) 10

//defines
#define LWIP_MAX_LENGTH 1460
#define MAX_BUFFER_LENGTH 4000

#define STX 0x02
#define STX_START_PONINTER 0
#define LENGTH_DATA_START_POINTER 1
#define LENGTH_DATA_END_POINTER 4
#define DATA_START_POINTER 5



/*------------------------------------Server-----------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/**** Send RESPONSE every time the client sends some data ******/
static void TCPServerRecvTask(void const *argument)
{
	data_structure* pData = (data_structure*)argument;
	struct netconn *conn = nullptr, *newconn = nullptr;

	struct netbuf *buf;
	err_t err = -20, accept_err = -20;
	std::string recv_buffer;

	/* Create a new connection identifier. */
	conn = netconn_new(NETCONN_TCP);

	if (!(conn))
		goto err;

	/* Bind connection to the server port. */
	err = netconn_bind(conn, IP_ADDR_ANY, ServerPort);

	if (err != ERR_OK)
		goto err;

	/* Tell connection to go into listening mode. */
	netconn_listen(conn);

	while (accept_err != ERR_OK)
	{
		/* Grab new connection. */
		accept_err = netconn_accept(conn, &newconn);

		//add timeout error
	}

	/* receive the data from the client */
	while (netconn_recv(newconn, &buf) == ERR_OK)
	{
		do
		{
			//0. maximum data occur error
			if(recv_buffer.length() >= MAX_BUFFER_LENGTH)
				recv_buffer.clear();

			//1. copy all data using data and length
			char temp_data[LWIP_MAX_LENGTH] = {0,};

			strncpy((char*)(temp_data),
						(char*)((buf->p->payload)), buf->p->len);

			recv_buffer.append(temp_data);


			//2. check front values is 0x02, 0x32 is '2' character value for test
			if(recv_buffer.front() != 0x32)
			{
				recv_buffer.clear();

				continue;
			}

			//3. get buf length
			uint16_t buf_leng =
					std::stoi(recv_buffer.substr(LENGTH_DATA_START_POINTER, LENGTH_DATA_END_POINTER));

			if((recv_buffer.length()) < buf_leng)
			{
				continue;
			}

			//4. get into the json parser and get data
			// and enqueue the next command
			//this must do the data move to main data
			if(GetDataFromEthernet(recv_buffer.substr(DATA_START_POINTER,
					buf_leng + DATA_START_POINTER).c_str(), buf_leng) < 0)
			{
				//error occur
				continue;
			}

			//7. buffer init
			recv_buffer.erase(0, buf_leng +5);

			recv_buffer.shrink_to_fit();

		}
		while (netbuf_next(buf) >=0);

		netbuf_delete(buf);
	}

	err:
		/* Close connection and discard connection identifier. */

	//for whatever case occur
	netconn_close(newconn);
	netconn_delete(newconn);
	netconn_delete(conn);

	vTaskDelete(NULL);
}



void TcpServerDelete()
{
	  if((netif_is_link_up(&gnetif))) return;

	  if(newconn == NULL && conn == NULL) return;

	  if(netconn_close(newconn) != ERR_OK) return;

	  if(netconn_delete(newconn) != ERR_OK) return;

	  if(netconn_delete(conn) != ERR_OK) return;

	  vTaskDelete(TcpServerRecvHandle);

	  vTaskDelete(TcpServerSendHandle);

	  return;
}

void TcpServerSend(const char *data)
{

	netconn_write(newconn, data, strlen(data), NETCONN_COPY);
}


typedef struct
{
	uint16_t type = 0; //report? response
	uint16_t recv_command_ = 0;
	uint16_t send_command_ = 0;
}eth_command_;

_Message* recv_msg = NULL;


static void TCPServerSendTask(void const *arg)
{
	osEvent retVal;

	//1. check the msg
	std::vector<eth_command_> send_command_data_;

	while(1)
	{
		//0. Get all messages from eth (be notified type)
		//retVal = osMessageGet(TCPSendQueueHandle, 500); //dequeue

		//1. if msg queue is available
//		if(retVal.status == osEventMessage)
//		{
//			recv_msg  = new _Message;
//
//			this must enqeue command data to vector queue
//			memcpy(recv_msg, (_Message*)retVal.value.p, sizeof(*recv_msg));
//			_Message* recv_msg = (_Message*)retVal.value.p;


//			eth_command_ cmd;
//			cmd.type = recv_msg->id_;
//			cmd.send_command_ = recv_msg->cmd_;
//
//			send_command_data_.push_back(cmd);
//
//			//printf("get data from main data\r\n");
//			//recv_msg.
//
//
//		}



		//if no msg, do empty the queue
		if(!(send_command_data_.empty()))
		{
			//0. copy the front data
			const eth_command_ send_json_data_ = send_command_data_.front();
			char send_data_[1024] = {0,};

			//1. get data from main data structure

			if(send_json_data_.type == 0x11)
			{
				if(send_json_data_.send_command_ == 2)
				{
					//2. then, move to the buffer
					//strncpy(send_data_ , ethernet_create_message(), strlen(ethernet_create_message()));
					netconn_write(newconn, ethernet_create_message(), strlen(ethernet_create_message()), NETCONN_COPY);
				}

			}





			//3. send msg
			//netconn_write(newconn, send_data_, strlen(send_data_), NETCONN_COPY);

			//4. Check msg type. when recved data first -> delete first queue immediately
			//						when send data first (this)-> wait until recved meg

			send_command_data_.erase(send_command_data_.begin());
		}

	}

	//if data is all set, dequeue the vector qeuue
	//if(send_command_data_.send_command_ == sre_command_data_.recv_command_ )
	//send_command_data_.erase(send_command_data_.begin())





	return;
}


void TcpServerInit(void const* argument)
{
	data_structure* st = (data_structure*)argument;

	//must add the ip params
	//MX_LWIP_Init();

	if(newconn == NULL)
	{
		/* definition and creation of TCPServerTask */
		osThreadDef(TCPServerRecvTask_, TCPServerRecvTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *8);
		TcpServerRecvHandle = osThreadCreate(osThread(TCPServerRecvTask_), (void*)st);

		/* definition and creation of TCPServerTask */
		osThreadDef(TCPServerSendTask_, TCPServerSendTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *4);
		TcpServerSendHandle = osThreadCreate(osThread(TCPServerSendTask_), (void*)st);
	}
}

