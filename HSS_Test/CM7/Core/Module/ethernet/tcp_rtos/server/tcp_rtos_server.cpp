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

	char temp_data[LWIP_MAX_LENGTH] = {0,};

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
					//char temp_data[LWIP_MAX_LENGTH] = {0,};

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
					uint16_t buf_leng = std::stoi(recv_buffer.substr(LENGTH_DATA_START_POINTER
													, LENGTH_DATA_END_POINTER));

					if((recv_buffer.length()) < buf_leng)
					{
						continue;
					}

					if((recv_buffer.length()) != buf_leng)
					{
						recv_buffer.clear();

						continue;
					}

					//4. get into the json parser and get data
					// and enqueue the next command
					//this must do the data move to main data
					if(GetDataFromEthernet(Dst_
							, recv_buffer.substr(DATA_START_POINTER, buf_leng + DATA_START_POINTER).c_str()
							, buf_leng) < 0)
					{
						//error occur
						continue;
					}

					//7. buffer init
					recv_buffer.erase(0, buf_leng + DATA_START_POINTER);

					recv_buffer.shrink_to_fit();

					memset(temp_data, '\0', LWIP_MAX_LENGTH);

				}
				while (netbuf_next(buf) >=0);

				netbuf_delete(buf);
				break;

			}
		}
	}
	vTaskDelete(NULL);
}


static void TCPServerSendTask(void const* argument)
{
	data_structure* Dst_ = (data_structure*)argument;

	std::string send_buffer;

	char json_data_[LWIP_MAX_LENGTH] = {0,};

	//char* json_data_ = nullptr;

	//1. check the msg
	while(1)
	{
		//0. Get all messages from eth (be notified type)
		if(!(Dst_->tcp_send_queue_.empty()))
		{

			cmd_queue_data cmd_queue_data_ = Dst_->tcp_send_queue_.front();

			//check data for exception

			//1. get command to json format
//			strncpy((char*)(temp_data)
//					,(char*)(GetStringFromMainData(cmd_queue_data_))
//					,strlen(GetStringFromMainData(cmd_queue_data_)));

			GetStringFromMainData(cmd_queue_data_, json_data_);


			//3. make strings
			//append stx data
			send_buffer.append("2");

			//append string legnth data
			send_buffer.append(std::to_string(strlen(json_data_)));

			//append main json string
			send_buffer.append(json_data_);

			//4. send data to client
			netconn_write(Dst_->netconn_data_.accept_conn_
					, send_buffer.c_str()
					, strlen(send_buffer.c_str()) + 1
					, NETCONN_COPY);

			send_buffer.clear();

			memset(json_data_, '\0', LWIP_MAX_LENGTH);

			Dst_->tcp_send_queue_.erase(Dst_->tcp_send_queue_.begin());

		}

			//3. send msg
			//netconn_write(newconn, send_data_, strlen(send_data_), NETCONN_COPY);

			//4. Check msg type. when recved data first -> delete first queue immediately
			//						when send data first (this)-> wait until recved meg

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
