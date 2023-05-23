/*
 * api_cjson.h
 *
 *  Created on: Apr 28, 2023
 *      Author: studio3s
 */

#ifndef MODULE_API_DATA_STRUCTURE_INCLUDE_API_DATA_STRUCTURE_API_DATA_STRUCTURE_H_
#define MODULE_API_DATA_STRUCTURE_INCLUDE_API_DATA_STRUCTURE_API_DATA_STRUCTURE_H_

#include <api_data_structure/include/api_data_structure/cJSON.h>
#include <api_data_structure/include/api_data_structure/cJSON_Utils.h>
#include <fatfs_h7/include/fatfs_h7/fatfs_h7.h>

#include <cstring>
#include <cstdio>
#include <vector>
#include <map>


typedef struct
{
	uint16_t robot_name_ = 1;
	uint16_t fw_version_ = 100;

}robot_info;

typedef struct
{
	uint16_t configIP_ADDR0 = 192;
	uint16_t configIP_ADDR1 = 168;
	uint16_t configIP_ADDR2 = 17;
	uint16_t configIP_ADDR3 = 11;

	uint16_t configNET_MASK0 = 255;
	uint16_t configNET_MASK1 = 255;
	uint16_t configNET_MASK2 = 255;
	uint16_t configNET_MASK3 = 0;

	uint16_t configGW_ADDR0 = 192;
	uint16_t configGW_ADDR1 = 168;
	uint16_t configGW_ADDR2 = 17;
	uint16_t configGW_ADDR3 = 1;

}ipaddress_info;

typedef struct
{
	unsigned long timestamp1_ = 0;
	unsigned long timestamp2_ = 0;

}timestamp_info;



typedef struct
{
	uint16_t mode_ = 0;
	uint16_t status_ = 0;
	uint16_t position_ = 0;
	uint16_t destination_ = 0;

	uint16_t speed_ = 0;
	uint16_t fork_stroke_ = 0;
	uint16_t fork_width_ = 0;
	uint16_t fork_on_load_ = 0;

	uint16_t alarm_code_ = 0;
	uint16_t error_code_ = 0;

}status_page_1;

typedef struct
{
	uint32_t sensor_input_ = 0;

}status_page_2;

typedef struct
{
	uint16_t task_type_ = 0;
	uint16_t job_id_ = 0;
	uint16_t task_id_ = 0;
	uint16_t task_status_ = 0;
	uint16_t pending_task_no_ = 0;
	uint16_t callback_msg_ = 0;

}status_page_3;

typedef struct
{
	uint32_t move_limit_min_ = 0;
	uint32_t move_limit_max_ = 0;
	uint32_t elevator_entry_pos_ = 0;
	uint32_t elevator_board_pos_ = 0;
	uint32_t elevator_exit_pos_ = 0;
	int16_t fwd_stop_calibration_ = 0;
	int16_t bwd_stop_calibration_ = 0;
	int16_t position_correction_constant_ = 0;

}vehicle_config_page_1;

typedef struct
{
	uint16_t move_speed1_ = 0;
	uint16_t move_acc1_ = 0;
	uint16_t move_speed2_ = 0;
	uint16_t move_acc2_ = 0;

}vehicle_config_page_2;


typedef struct
{
	uint16_t stroke_speed1_ = 0;
	uint16_t stroke_acc1_ = 0;
	uint16_t stroke_speed2_ = 0;
	uint16_t stroke_acc2_ = 0;
	uint16_t width_speed1_ = 0;
	uint16_t width_acc1_ = 0;
	uint16_t width_speed2_ = 0;
	uint16_t width_acc2_ = 0;

}attach_config;



typedef struct
{
	robot_info robot_info_;
	ipaddress_info ipaddress_info_;
	timestamp_info timestamp_info_;

	status_page_1 status_page_1_;
	status_page_2 status_page_2_;
	status_page_3 status_page_3_;

	vehicle_config_page_1 vehicle_config_page_1_;
	vehicle_config_page_2 vehicle_config_page_2_;
	attach_config attach_config_;

}main_data;







typedef struct
{

	std::map <int, int> main_data_; 	//main data structure

	std::vector<int> transactionid;
	std::vector<int> eth_send_queue_;
	std::vector<int> openamp_send_queue_;
	std::vector<int> sdcard_write_queue_;

	//netconn(socket) data
	struct netconn *conn;

	//FATFS data
	FATFS SDFatFs;  /* File system object for SD card logical drive */
	FIL SDFile;
	char SDPath[4]; /* SD card logical drive path */



}data_structure;






enum
{
	//robot_info
	robot_name_ = 1,
	fw_version_ = 2,

	//timestamp

	//ipaddress_info
	configIP_ADDR0 = 11,
	configIP_ADDR1 = 12,
	configIP_ADDR2 = 13,
	configIP_ADDR3 = 14,

	configNET_MASK0 = 15,
	configNET_MASK1 = 16,
	configNET_MASK2 = 17,
	configNET_MASK3 = 18,

	configGW_ADDR0 = 19,
	configGW_ADDR1 = 20,
	configGW_ADDR2 = 21,
	configGW_ADDR3 = 21,

	//status_page_1
	mode_ = 10001,
	status_ = 10002,
	position_ = 10003,
	destination_ = 10004,

	speed_ = 10005,
	fork_stroke_ = 10006,
	fork_width_ = 10007,
	fork_on_load_ = 10008,

	alarm_code_ = 10009,
	error_code_ = 10010,

	//status_page_2
	sensor_input_ = 10011,

	//status_page_3
	task_type_ = 10025,
	job_id_ = 10026,
	task_id_ = 10027,
	task_status_ = 10028,
	pending_task_no_ = 10029,
	callback_msg_ = 10030,

	//vehicle_config_page_1
	move_limit_min_ = 20001,
	move_limit_max_ = 20002,
	elevator_entry_pos_ = 20003,
	elevator_board_pos_ = 20004,
	elevator_exit_pos_ = 20005,
	fwd_stop_calibration_ = 20006,
	bwd_stop_calibration_ = 20007,
	position_correction_constant_ = 20008,

	//vehicle_config_page_2
	move_speed1_ = 21001,
	move_acc1_ = 21002,
	move_speed2_ = 21003,
	move_acc2_ = 21004,


	//attach_config
	stroke_speed1_ = 31001,
	stroke_acc1_ = 31002,
	stroke_speed2_ = 31003,
	stroke_acc2_ = 31004,
	width_speed1_ = 31005,
	width_acc1_ = 31006,
	width_speed2_ = 31007,
	width_acc2_ = 31008,


}define_main_data_;

//tcp messages
typedef struct
{
	int id_;
	char data_[10] = {0,};
	int leng_;
	int cmd_;

}_Message;




int InitializeDataStructure(data_structure* st);

int GetDataFromEthernet(const char * const msg, int msg_leng);
int ethernet_data_parser(const char * const msg, int msg_leng);
const char* ethernet_create_message(void);

int supports_full_hd(const char * const msg, int msg_leng);
const char* create_monitor();








#endif /* MODULE_API_DATA_STRUCTURE_INCLUDE_API_DATA_STRUCTURE_API_DATA_STRUCTURE_H_ */