/*
 * api_debug.cpp
 *
 *  Created on: Mar 28, 2023
 *      Author: studio3s
 */




#include "api_debug/api_debug.h"


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
void DebugDrive()
{
	int cmd = 0;
	int cmd1 = str;

	if (cmd1 != 0) cmd = cmd1;

	switch(cmd)
	{
		case 1: FatFsInit(); break;

		case 2: FatFsTest("test.txt"); break;

		case 3: SDCard_Write("test.txt", eth_data_.c_str());

				eth_data_.clear();

			break;

		case 100:
			  printf("Firmware will be rebooted in 3 senconds.\r\n");

			  HAL_Delay(3000);

			  HAL_NVIC_SystemReset();

			break;

		default: break;
	}
	memset(&str, '\0', sizeof(str));

	//memset(&str1_, '\0', sizeof(str1_));
	//memset(&str3_, '\0', sizeof(str3_));
	//memset(&char_ethernet, '\0', sizeof(char_ethernet));
}