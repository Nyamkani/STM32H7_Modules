/*
 * tcprtosserver.h
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */

#ifndef MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_
#define MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_

#include <string>


#ifdef __cplusplus
extern "C" {
#endif

#include "lwip.h"
#include "lwip/init.h"
#include "lwip/netif.h"
#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"

#include "netif.h"
#include "ethernetif.h"

#include "string.h"

#ifdef __cplusplus
}
#endif


//defines
#define STX 0x02

enum RecvDataLength
{
	LWIP_MAX_LENGTH = 1460,
	MAX_BUFFER_LENGTH = 4000,
};

enum RecvDataPointer
{
	DATA_STX_START_POINTER = 0,
	DATA_LENGTH_START_POINTER = 1,
	DATA_LENGTH_END_POINTER = 4,
	DATA_START_POINTER = 5,
};









void TcpServerSend(const char *data);
void TcpServerDelete();
void TcpServerRecvBuffer(const char *data);

//-----------------------------------------------------------------------class

class TcpRtos
{
	private:
		/*main data structure*/
		data_structure* Dst_ = nullptr;

		/*network interface values*/
		struct netif gnetif;
		ip4_addr_t ipaddr, netmask, gateway;
		uint8_t ip_address[4], netmask_address[4] ,gateway_address[4];
		uint16_t ip_port_ = 0;

		/*netconn values*/
		struct netconn* conn_ = nullptr;
		struct netconn* accept_conn_ = nullptr;

		err_t err;
		err_t accept_err;

		/*status values*/
		bool is_init_ = false;
		bool is_run_ = false;
		bool is_error_ = false;

		/*RTOS task(handle)values*/
		osThreadId TcpAcceptConnHandle = nullptr;
		osThreadId TcpServerRecvHandle = nullptr;
		osThreadId TcpServerSendHandle = nullptr;



	public:



	private:
		void LWIPInitialize();

		static void TCPAcceptConnTask(void const* argument);
		static void TCPServerRecvTask(void const* argument);
		static void TCPServerSendTask(void const* argument);

	public:
		TcpRtos();
		TcpRtos(data_structure* Dst);
		virtual ~TcpRtos();


		void Initialize();
		TcpRtos& SetData(data_structure* Dst);
};






#endif /* MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_ */
