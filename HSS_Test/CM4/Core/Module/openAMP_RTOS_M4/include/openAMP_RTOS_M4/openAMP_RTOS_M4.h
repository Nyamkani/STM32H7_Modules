/*
 * openAMP_RTOS_M4.h
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */

#ifndef MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_
#define MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_

#ifdef __cplusplus
 extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "openamp.h"
#include <string.h>


/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define RPMSG_SERVICE_NAME              "openamp_pingpong"



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

unsigned int receive_message(void);

void OpenAMPInit_M4();

#ifdef __cplusplus
}
#endif

#endif /* MODULE_OPENAMP_RTOS_M4_INCLUDE_OPENAMP_RTOS_M4_OPENAMP_RTOS_M4_H_ */
