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


/*Rtos thread handle*/
osThreadId TcpAcceptConnHandle;
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

static void TCPServerRecvTask(void const *argument);
static void TCPServerSendTask(void const* argument);

/*------------------------------------accept connection -----------------------------------------*/
/*-----------------------------------------------------------------------------------*/



static void TCPAcceptConnTask(void const *argument)
{
	data_structure* Dst_ = (data_structure*)argument;

	std::vector<netconn* > buf_conn_list_;

	bool test_flag1_ = false;
	bool test_flag2_ = false;

	while (1)
	{

		struct netconn* buf_conn_ = nullptr;

		netconn_listen(Dst_->netconn_data_.conn_);

		/* Grab new connection. */
		while (netconn_accept(Dst_->netconn_data_.conn_, &(buf_conn_)) != ERR_OK );

		/*When the zombie socket available, delete them*/
		if(!(buf_conn_list_.empty()))
		{
			for(auto range : buf_conn_list_)
			{
				netconn_close(range);
				netconn_delete(range);
			}
			buf_conn_list_.clear();

		}

		/*When the conn is not nullptr, delete ptr*/
		if(Dst_->netconn_data_.accept_conn_)
			Dst_->netconn_data_.accept_conn_= nullptr;

		/*matching new ptr*/
		Dst_->netconn_data_.accept_conn_ = buf_conn_;

		/*enqueue the ptr*/
		buf_conn_list_.push_back(buf_conn_);


		/*make thread only once*/
		if(!test_flag1_)
		{
			/* definition and creation of TCPServerTask */
			osThreadDef(TCPServerRecvTask_, TCPServerRecvTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *8);
			TcpServerRecvHandle = osThreadCreate(osThread(TCPServerRecvTask_), (void*)Dst_);

			test_flag1_ = true;
		}

		if(!test_flag2_)
		{
			/* definition and creation of TCPServerTask */
			osThreadDef(TCPServerSendTask_, TCPServerSendTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *4);
					TcpServerSendHandle = osThreadCreate(osThread(TCPServerSendTask_), (void*)Dst_);

			test_flag2_ = true;
		}

	}

	vTaskDelete(NULL);
}



/*------------------------------------Server-----------------------------------------*/
/*-----------------------------------------------------------------------------------*/


/**** Send RESPONSE every time the client sends some data ******/
static void TCPServerRecvTask(void const *argument)
{
	data_structure* Dst_ = (data_structure*)argument;

	struct netbuf *buf;

	std::string recv_buffer;

	//netconn_set_recvtimeout(Dst_->netconn_data_.accept_conn_, 2000UL);

	while(1)
	{
		/*wait for recv*/
		/*notice : When socket is alive, Didnt get recv in 5 seconds, break socket*/

		if(netconn_recv(Dst_->netconn_data_.accept_conn_, &buf) == ERR_OK)
		{
			while(1)
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
				break;

			}
		}
	}
	vTaskDelete(NULL);
}

typedef struct
{
	uint16_t type = 0; //report? response
	uint16_t recv_command_ = 0;
	uint16_t send_command_ = 0;
}eth_command_;

_Message* recv_msg = NULL;


static void TCPServerSendTask(void const* argument)
{
	data_structure* Dst_ = (data_structure*)argument;

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
					netconn_write(Dst_->netconn_data_.accept_conn_, ethernet_create_message(), strlen(ethernet_create_message()), NETCONN_COPY);
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
	data_structure* Dst_ = (data_structure*)argument;

	/* Create a new connection identifier. */
	Dst_->netconn_data_.conn_  = netconn_new(NETCONN_TCP);

	/*failed init error check */
	if (!(Dst_->netconn_data_.conn_))
		Dst_->netconn_data_.err = -20; //error occur

	/* Bind connection to the server port. */
	Dst_->netconn_data_.err  = netconn_bind(Dst_->netconn_data_.conn_, IP_ADDR_ANY, ServerPort);

	/*bind failed error check*/
	if (Dst_->netconn_data_.err != ERR_OK)
	{
		printf("error\r\n");
	}

	//must add the ip params
	//MX_LWIP_Init();

		/* definition and creation of TCPServerTask */
		osThreadDef(TCPAcceptConnTask_, TCPAcceptConnTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
		TcpAcceptConnHandle = osThreadCreate(osThread(TCPAcceptConnTask_), (void*)Dst_);

}
