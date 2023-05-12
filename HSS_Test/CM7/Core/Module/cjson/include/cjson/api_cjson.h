/*
 * api_cjson.h
 *
 *  Created on: Apr 28, 2023
 *      Author: studio3s
 */

#ifndef MODULE_CJSON_INCLUDE_CJSON_API_CJSON_H_
#define MODULE_CJSON_INCLUDE_CJSON_API_CJSON_H_

#include "cjson/include/cjson/cJSON.h"
#include "cjson/include/cjson/cJSON_Utils.h"

#include <cstring>
#include <cstdio>

int ethernet_data_parser(const char * const msg, int msg_leng);


int supports_full_hd(const char * const msg, int msg_leng);
const char* create_monitor();

#endif /* MODULE_CJSON_INCLUDE_CJSON_API_CJSON_H_ */
