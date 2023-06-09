/*
 * tcprtosserver.h
 *
 *  Created on: Sep 6, 2022
 *      Author: kss
 */

#ifndef MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_
#define MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_

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

#ifdef __cplusplus
}
#endif


#endif /* MODULE_ETHERNET_TCP_RTOS_TCP_RTOS_H_ */
