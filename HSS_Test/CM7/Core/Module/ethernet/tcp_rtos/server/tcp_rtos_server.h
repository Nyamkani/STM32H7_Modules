/*
 * tcprtosserver.h
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */

#ifndef MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_
#define MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_

#include <string>

//Defines
#define max_num_buf_             1024


//tcp messages
typedef struct
{
	int id_;
	char data_[max_num_buf_] = {0,};
	int leng_;

}_Message;






#ifdef __cplusplus
extern "C" {
#endif

#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"

#include "string.h"

#include "netif.h"


void TcpServerInit(void);
void TcpServerSend(const char *data);
void TcpServerDelete();
void TcpServerRecvBuffer(const char *data);


#ifdef __cplusplus
}
#endif

#endif /* MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_ */
