/*
 * api_debug.cpp
 *
 *  Created on: Mar 28, 2023
 *      Author: studio3s
 */




#include <api_data/include/api_data_structure/api_data.h>
#include "api_debug/api_debug.h"
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

extern std::string eth_data_;



static int str = 0;
//--------------------------------------------------------------test
/* USER CODE BEGIN PV */

/*NOTICE*/
/*We will use only USART1 for debugging*/

//for uart1 debug
//void DebugDrive(_Message* msg)
//{
//	_Message recv_msg_= *msg;
//
//	if(recv_msg_.id_ != 0x10) return;
//
//	char* data_ = recv_msg_.data_;
//	int length_ = recv_msg_.leng_;
//
//	int cmd = str;
//
//	switch(cmd)
//	{
//		case 1: FatFsInit(); break;
//
//		case 2: FatFsTest("test.txt"); break;
//
//		case 3: SDCard_Write("test.txt", data_, length_);
//
//				//eth_data_.clear();
//
//			break;
//
//		case 4: SDCard_Read("test.txt"); break;
//
//		//case 5: example_minimal_run(); break;
//
//		//case 6: supports_full_hd(data_, length_); break;
//
//		case 6: ethernet_data_parser(data_, length_); break;
//
//		case 7: TcpServerSend(create_monitor()); break;
//
//		//case 10: OpenAMPSend(data_, length_);
//
//				//eth_data_.clear();
//
//			break;
//
//		case 11: break;
//
//
//		case 100:
//			  printf("Firmware will be rebooted in 3 senconds.\r\n");
//
//			  HAL_Delay(3000);
//
//			  HAL_NVIC_SystemReset();
//
//			break;
//
//		default: break;
//	}
//	memset(&str, '\0', sizeof(str));
//
//	//memset(&str1_, '\0', sizeof(str1_));
//	//memset(&str3_, '\0', sizeof(str3_));
//	//memset(&char_ethernet, '\0', sizeof(char_ethernet));
//}
