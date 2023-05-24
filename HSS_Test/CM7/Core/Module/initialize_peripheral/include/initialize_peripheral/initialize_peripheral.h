/*
 * initialize_peripheral.h
 *
 *  Created on: May 24, 2023
 *      Author: studio3s
 */

#ifndef MODULE_INITIALIZE_PERIPHERAL_INCLUDE_INITIALIZE_PERIPHERAL_H_
#define MODULE_INITIALIZE_PERIPHERAL_INCLUDE_INITIALIZE_PERIPHERAL_H_


#include <main.h>
#include "fatfs.h"


void SystemClock_Config(void);


int MPU_setting();
int initialize_peripheral();


#endif /* MODULE_INITIALIZE_PERIPHERAL_INCLUDE_INITIALIZE_PERIPHERAL_H_ */
