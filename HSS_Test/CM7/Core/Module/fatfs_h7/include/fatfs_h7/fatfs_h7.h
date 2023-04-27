/*
 * fatfs.h
 *
 *  Created on: Mar 16, 2023
 *      Author: studio3s
 */

#ifndef MODULE_FATFS_H7_INCLUDE_FATFS_H7_FATFS_H7_H_
#define MODULE_FATFS_H7_INCLUDE_FATFS_H7_FATFS_H7_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ff.h"
#include "bsp_driver_sd.h"
#include "ff_gen_drv.h"
#include "sd_diskio.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static void BSPInit();

void FatFsInit();

void FatFsTest(const char *filename);


int SDCard_Read(const char *filename);
int SDCard_Write(const char *filename, const char *msg, int msg_leng_);

#ifdef __cplusplus
}
#endif


#endif /* MODULE_FATFS_H7_INCLUDE_FATFS_H7_FATFS_H7_H_ */
