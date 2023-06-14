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
			osThreadDef(TCPServerSendTask_, TCPServerSendTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE *8);
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

	while(1)
	{
		/*wait for recv*/
		/*notice : When socket is alive, Didnt get recv in 5 seconds, break socket*/

		if(netconn_recv(Dst_->netconn_data_.accept_conn_, &buf) != ERR_OK)
			continue;

		do
		{
			char temp_data[LWIP_MAX_LENGTH] = {0,};

			memcpy((char*)(temp_data), (char*)((buf->p->payload)), buf->p->len);

			if(recv_buffer.length() >= MAX_BUFFER_LENGTH)
				recv_buffer.clear();

			recv_buffer.append(temp_data);

			//if(recv_buffer.front() != 0x32)
			if(recv_buffer.front() != 0x02)
			{
				recv_buffer.clear();

				recv_buffer.shrink_to_fit();

				continue;
			}

			int buf_leng = std::stoi(recv_buffer.substr(LENGTH_DATA_START_POINTER, LENGTH_DATA_END_POINTER));

			if(recv_buffer.length() < buf_leng)
				continue;

			if(GetDataFromEthernet(Dst_
					, recv_buffer.substr(DATA_START_POINTER, buf_leng + DATA_START_POINTER).c_str()
					, buf_leng) < 0)
				continue; //error

			recv_buffer.erase(0, buf_leng + DATA_START_POINTER);

			recv_buffer.shrink_to_fit();

			//if(recv_buffer.front() != 0x32)
			if(recv_buffer.front() != 0x02)
				recv_buffer.clear();

		}
		while (netbuf_next(buf) > 0);

		netbuf_delete(buf);
	}
	vTaskDelete(NULL);
}


static void TCPServerSendTask(void const* argument)
{
	data_structure* Dst_ = (data_structure*)argument;

	//1. check the msg
	while(1)
	{
		//0. Get all messages from eth (be notified type)
		if(!(Dst_->tcp_send_queue_.empty()))
		{
			std::string send_buffer;

			cmd_queue_data cmd_queue_data_ = Dst_->tcp_send_queue_.front();

			char json_data_[LWIP_MAX_LENGTH] = {0,};



			if(GetStringFromMainData(Dst_, cmd_queue_data_, json_data_) < 0)
			{
				//error occur
			}

			send_buffer.insert(0, 1, 0x02);

			std::string data_length_ = std::to_string(strlen(json_data_));

			if (data_length_.length() < 4)
			{
				int itr = 4 - data_length_.length();

				for(int i = 0; i < itr; i++)
					send_buffer.append("0");
			}

			send_buffer.append(data_length_);

			data_length_.clear();

			data_length_.shrink_to_fit();			

			send_buffer.append(json_data_);

			netconn_write(Dst_->netconn_data_.accept_conn_
					, send_buffer.c_str()
					, send_buffer.length()
					, NETCONN_COPY);

			Dst_->tcp_send_queue_.erase(Dst_->tcp_send_queue_.begin());
		}

		osDelay(10);
	}

	return;
}

void TcpServerInit(void const* argument)
{
	data_structure* Dst_ = (data_structure*)argument;

	//must add the ip params
	//MX_LWIP_Init();

	/* Create a new connection identifier. */
	Dst_->netconn_data_.conn_  = netconn_new(NETCONN_TCP);

	/*failed init error check */
	if (!(Dst_->netconn_data_.conn_))
		Dst_->netconn_data_.err = -20; //error occur

	/* Bind connection to the server port. */
	Dst_->netconn_data_.err  = netconn_bind(Dst_->netconn_data_.conn_, IP_ADDR_ANY, ServerPort);

	/*bind failed error check*/
	if (Dst_->netconn_data_.err != ERR_OK)
		printf("error\r\n");

	/* definition and creation of TCPServerTask */
	osThreadDef(TCPAcceptConnTask_, TCPAcceptConnTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	TcpAcceptConnHandle = osThreadCreate(osThread(TCPAcceptConnTask_), (void*)Dst_);
}


//-----------------------------------------------------------------------class

TcpRtos::TcpRtos()
{

}

TcpRtos::TcpRtos(data_structure* Dst)
{
	this->Dst_ = Dst;
}

TcpRtos::~TcpRtos()
{


}

TcpRtos& TcpRtos::SetData(data_structure* Dst)
{

}


void TcpRtos::LWIPInitialize()
{

	struct netif gnetif;
	ip4_addr_t ipaddr;
	ip4_addr_t netmask;
	ip4_addr_t gw;
	uint8_t IP_ADDRESS[4];
	uint8_t NETMASK_ADDRESS[4];
	uint8_t GATEWAY_ADDRESS[4];

	/* IP addresses initialization */
	IP_ADDRESS[0] = 192;
	IP_ADDRESS[1] = 168;
	IP_ADDRESS[2] = 1;
	IP_ADDRESS[3] = 30;
	NETMASK_ADDRESS[0] = 255;
	NETMASK_ADDRESS[1] = 255;
	NETMASK_ADDRESS[2] = 255;
	NETMASK_ADDRESS[3] = 0;
	GATEWAY_ADDRESS[0] = 0;
	GATEWAY_ADDRESS[1] = 0;
	GATEWAY_ADDRESS[2] = 0;
	GATEWAY_ADDRESS[3] = 0;

	/* Initilialize the LwIP stack with RTOS */
	tcpip_init( NULL, NULL );

	/* IP addresses initialization without DHCP (IPv4) */
	IP4_ADDR(&ipaddr, IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);
	IP4_ADDR(&netmask, NETMASK_ADDRESS[0], NETMASK_ADDRESS[1] , NETMASK_ADDRESS[2], NETMASK_ADDRESS[3]);
	IP4_ADDR(&gw, GATEWAY_ADDRESS[0], GATEWAY_ADDRESS[1], GATEWAY_ADDRESS[2], GATEWAY_ADDRESS[3]);

	/* add the network interface (IPv4/IPv6) with RTOS */
	netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);

	/* Registers the default network interface */
	netif_set_default(&gnetif);

	netif_set_down(&gnetif);

	/* Set the link callback function, this function is called on change of link status*/
	//netif_set_link_callback(&gnetif, ethernet_link_status_updated);

}





void TcpRtos::Initialize()
{
	//must add the ip params
	LWIPInitialize();

	MX_LWIP_Init();

	/* Create a new connection identifier. */
	this->Dst_->netconn_data_.conn_  = netconn_new(NETCONN_TCP);

	/*failed init error check */
	if (!(this->Dst_->netconn_data_.conn_))
		this->Dst_->netconn_data_.err = -20; //error occur

	/* Bind connection to the server port. */
	this->Dst_->netconn_data_.err  = netconn_bind(Dst_->netconn_data_.conn_, IP_ADDR_ANY, ServerPort);

	/*bind failed error check*/
	if (this->Dst_->netconn_data_.err != ERR_OK)
		printf("error\r\n");

	/* definition and creation of TCPServerTask */
	osThreadDef(TCPAcceptConnTask_, TCPAcceptConnTask, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	TcpAcceptConnHandle = osThreadCreate(osThread(TCPAcceptConnTask_), (void*)Dst_);

}






