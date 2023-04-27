/*
 * openAMP_RTOS_M7.h
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_
#define MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_


#include "stm32h7xx_hal.h"
#include "openamp.h"
#include "cmsis_os.h"

#include <iostream>
#include <string>
/* Private macro -------------------------------------------------------------*/
#define RPMSG_CHAN_NAME               "openamp"

/* Exported constants --------------------------------------------------------*/
#define appliSTACK_SIZE configMINIMAL_STACK_SIZE *2

void OpenAMPInit();
void OpenAMPReadTask(void const *argument);
void OpenAMPSend(const char* msg, int msg_leng);
void OpenAMPInit_M7();

#ifdef __cplusplus
 extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_ */
