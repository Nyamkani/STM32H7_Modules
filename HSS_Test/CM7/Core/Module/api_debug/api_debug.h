/*
 * api_debug.h
 *
 *  Created on: Mar 28, 2023
 *      Author: studio3s
 */

#ifndef MODULE_API_DEBUG_API_DEBUG_H_
#define MODULE_API_DEBUG_API_DEBUG_H_

#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>

//use this below functions
void Debug_Uart_Init();
void Dprintf(const char *fmt, ...); // custom printf() function
void DebugDrive();

#ifdef __cplusplus
extern "C" {
#endif

#include <fatfs_h7/include/fatfs_h7/fatfs_h7.h>

#include "api_debug/api_debug.h"

#ifdef __cplusplus
}
#endif


#endif /* MODULE_API_DEBUG_API_DEBUG_H_ */
