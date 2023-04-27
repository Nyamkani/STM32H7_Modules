/*
 * openAMP_RTOS_M4.h
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */

#ifndef MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_
#define MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "openamp.h"

#include <string>

 /* Private macro -------------------------------------------------------------*/
 #define RPMSG_SERVICE_NAME              "openamp"

void OpenAMPDrive();
int OpenAMPInit();
volatile char*  receive_message(void);

void OpenAMPInit_M4();



#ifdef __cplusplus
 extern "C" {
#endif

#include <string.h>


/* Private typedef -----------------------------------------------------------*/



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */





#ifdef __cplusplus
}
#endif

#endif /* MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_ */
