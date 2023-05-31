/*
 * api_cjson.cpp
 *
 *  Created on: Apr 28, 2023
 *      Author: studio3s
 */




#include <api_data_structure/include/api_data_structure/api_data_structure.h>
#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>

#include <main.h>
#include <map>

osMessageQId TCPSendQueueHandle;

//-----------------------------------------------------------main data
int InitializeDataStructure(data_structure* Dst)
{
	data_structure* Dst_ = Dst;

	int status = -1;

	//0. insert the data to main data structure

	//robot_info
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ROBOT_NAME_, 1));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FW_VERSION, 1));

	//ipaddress_info
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGIP_ADDR0, 192));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGIP_ADDR1, 168));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGIP_ADDR2, 17));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGIP_ADDR3, 11));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGNET_MASK0, 255));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGNET_MASK1, 255));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGNET_MASK2, 255));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGNET_MASK3, 0));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGGW_ADDR0, 192));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGGW_ADDR1, 168));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGGW_ADDR2, 17));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CONFIGGW_ADDR3, 1));

	//status_page_1;
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MODE, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::STATUS, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::POSITION, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::DESTINATION, 0));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::SPEED, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_STROKE, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_WIDTH, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_ON_LOAD, 0));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ALARM_CODE, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ERROR_CODE, 0));

	//status_page_2
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::SENSOR_INPUT, 0));

	//status_page_3
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::TASK_TYPE, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::TASK_GROUP, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::JOB_ID, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::TASK_ID, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::TASK_STATUS, 0));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::PENDING_TASK_NO, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::INQUIRE_OPTION, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::CALLBACK_MSG, 0));

	//vehicle_config_page_1
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_LIMIT_MIN, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_LIMIT_MAX, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ELEVATOR_ENTRY_POS, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ELEVATOR_BOARD_POS, 0));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ELEVATOR_EXIT_POS, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FWD_STOP_CALIBRATION, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::BWD_STOP_CALIBRATION, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::POS_CRRECTION_CONSTANT, 0));

	//vehicle_config_page_2
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_SPEED1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_ACC1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_SPEED2, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::MOVE_ACC2, 0));

	//attach_config
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::STROKE_SPEED1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::STROKE_ACC1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::STROKE_SPEED2, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::STROKE_ACC2, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::WIDTH_SPEED1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::WIDTH_ACC1, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::WIDTH_SPEED2, 0));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::WIDTH_ACC2, 0));


	//1. success the allocate
	status = 1;

	return status;
}



//-------------------------------------------------------------write data to main data
int WriteDataToMainData(void const* argument, int key, int value)
{
	data_structure* Dst_ = (data_structure*)argument;

	int status = -1;

	const int key_ = key, value_ = value;

	//if key is available
	if (Dst_->main_data_.find(key_) != Dst_->main_data_.end() )
	{
		Dst_->main_data_.at(key_) = value_;

		status = 1;
	}

	return status;
}



//get transactionid from header's transactionid
uint64_t GetTransactionIdFromHeader(const char * const msg, int msg_leng)
{
	uint64_t id = 0;

	char recv_buf[msg_leng + 1] = {0,};

	strncpy (recv_buf, msg, msg_leng);


	//declare header buffers
    const cJSON *header = NULL;

    const cJSON *transactionid = NULL;

	//-----------------------------------------------------------
	cJSON *msg_json = cJSON_ParseWithLength(recv_buf, msg_leng + 1);

	//cjson ptr check
	if (msg_json == NULL)
	{
		cJSON_Delete(msg_json);

		id = JsonErrOffset::JSON_FORMAT_ERROR;

		return id;
	}

	//Get header object pointer
	header = cJSON_GetObjectItemCaseSensitive(msg_json, "header");

	if (header == NULL)
	{
		cJSON_Delete(msg_json);

		id = JsonErrOffset::JSON_FORMAT_ERROR;

		return id;
	}

	transactionid = cJSON_GetObjectItemCaseSensitive(header, "transactionId");

	if (cJSON_IsString(transactionid) && (transactionid->valuestring != NULL))
		id = strtoull(transactionid->valuestring, NULL, 10); 	// succeess

	cJSON_Delete(msg_json);

	return id;
}

//get command code from header's msgtype and catrgory
int GetCmdFromHeader(const char * const msg, int msg_leng)
{
	int cmd = 0;

	//memory copy
	char recv_buf[msg_leng + 1] = {0,};

	strncpy (recv_buf, msg, msg_leng);

	//declare header buffers
    const cJSON *header = NULL;
    const cJSON *msgtype = NULL;
    const cJSON *category = NULL;
    //const cJSON *timestamp = NULL;


	//-----------------------------------------------------------
	cJSON *msg_json = cJSON_ParseWithLength(recv_buf, msg_leng + 1);

	//cjson ptr check
	if (msg_json == NULL)
	{
		cJSON_Delete(msg_json);

		cmd = JsonErrOffset::JSON_FORMAT_ERROR;

		return cmd;
	}

	//Get header object pointer
	header = cJSON_GetObjectItemCaseSensitive(msg_json, "header");

	if (header == NULL)
	{
		cJSON_Delete(msg_json);

		cmd = JsonErrOffset::JSON_FORMAT_ERROR;

		return cmd;
	}


	msgtype = cJSON_GetObjectItemCaseSensitive(header, "msgType");

	if (cJSON_IsString(msgtype) && (msgtype->valuestring != NULL))
		//success

	category = cJSON_GetObjectItemCaseSensitive(header, "category");

	if (cJSON_IsString(category) && (category->valuestring != NULL))
		//success

	//middle check for checking error
	if(cmd < 0)
	{
		cJSON_Delete(msg_json);

		return cmd;
	}


	//get command type for enqeue the command queue

	if(strcmp(msgtype->valuestring, "request") == 0)
	{
		cmd += RecvCmdRangeOffset::START_REQUEST_CMD_RANGE;

		if(strcmp(category->valuestring, "info") == 0) cmd += RequestCmdOffset::REQUEST_INFO;

		else if(strcmp(category->valuestring, "status") == 0) cmd += RequestCmdOffset::REQUEST_STATUS;

		else if(strcmp(category->valuestring, "taskStatus") == 0) cmd += RequestCmdOffset::REQUEST_TASKSTATUS;

		else if(strcmp(category->valuestring, "setMode") == 0) cmd += RequestCmdOffset::REQUEST_SETMODE;

		else if(strcmp(category->valuestring, "alarmClear") == 0) cmd += RequestCmdOffset::REQUEST_ALARMCLEAR;

		else if(strcmp(category->valuestring, "sysReset") == 0) cmd += RequestCmdOffset::REQUEST_SYSRESET;

		else if(strcmp(category->valuestring, "taskPause") == 0) cmd += RequestCmdOffset::REQUEST_TASKPAUSE;

		else if(strcmp(category->valuestring, "taskResume") == 0) cmd += RequestCmdOffset::REQUEST_TASKRESUME;

		else if(strcmp(category->valuestring, "swems") == 0) cmd += RequestCmdOffset::REQUEST_SWEMS;

		else if(strcmp(category->valuestring, "timeSync") == 0) cmd += RequestCmdOffset::REQUEST_TIMESYNC;

		else if(strcmp(category->valuestring, "readParam") == 0) cmd += RequestCmdOffset::REQUEST_READPARAM;

		else if(strcmp(category->valuestring, "writeParam") == 0) cmd += RequestCmdOffset::REQUEST_WRITEPARAM;

		else if(strcmp(category->valuestring, "task") == 0) cmd += RequestCmdOffset::REQUEST_TASK;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "ack") == 0)
	{
		cmd += RecvCmdRangeOffset::START_ACK_CMD_RANGE;

		if(strcmp(category->valuestring, "task") == 0) cmd += AckCmdOffset::ACK_TASK;

		else if(strcmp(category->valuestring, "alert") == 0) cmd += AckCmdOffset::ACK_ALERT;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "approve") == 0)
	{
		cmd += RecvCmdRangeOffset::START_APRROVE_CMD_RANGE;

		if(strcmp(category->valuestring, "enterElevator") == 0) cmd += ApproveCmdOffset::APPROVE_ENTERELEVATOR;

		else if(strcmp(category->valuestring, "leaveElevator") == 0) cmd += ApproveCmdOffset::APPROVE_LEAVEELEVATOR;

		else if(strcmp(category->valuestring, "bufferPick") == 0) cmd += ApproveCmdOffset::APPROVE_BUFFERPICK;

		else if(strcmp(category->valuestring, "bufferPlace") == 0) cmd += ApproveCmdOffset::APPROVE_BUFFERPLACE;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "execute") == 0)
	{
		cmd += RecvCmdRangeOffset::START_EXCUTE_CMD_RANGE;

		if(strcmp(category->valuestring, "enterElevator") == 0) cmd += ExcuteCmdOffset::EXCUTE_ENTERELEVATOR;

		else if(strcmp(category->valuestring, "leaveElevator") == 0) cmd += ExcuteCmdOffset::EXCUTE_LEAVEELEVATOR;

		else if(strcmp(category->valuestring, "bufferPick") == 0) cmd += ExcuteCmdOffset::EXCUTE_BUFFERPICK;

		else if(strcmp(category->valuestring, "bufferPlace") == 0) cmd += ExcuteCmdOffset::EXCUTE_BUFFERPLACE;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "heartbeatRequset") == 0)
	{
		cmd += RecvCmdRangeOffset::START_HEARTTBEAT_CMD_RANGE;

		if(strcmp(category->valuestring, "Heartbeat") == 0) cmd += HeartbeatCmdOffset::heartbeat;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else
	{
		cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	cJSON_Delete(msg_json);

	return cmd;
}

//Get data from body
std::vector<int> GetDataFromBody(void const* argument, const char * const msg, int msg_leng, int cmd)
{

	//memory copy
	char recv_buf[msg_leng + 1] = {0,};

	strncpy (recv_buf, msg, msg_leng);

	std::vector<int> data_;

	data_.clear();

	int cmd_  = cmd;

	//-----------------------------------------------------------
	cJSON* msg_json = cJSON_ParseWithLength(recv_buf, msg_leng + 1);

	//cjson ptr check
	if (msg_json == NULL)
	{
		cJSON_Delete(msg_json);

		cmd_ = JsonErrOffset::JSON_FORMAT_ERROR;

		return data_;
	}

	//Get body object pointer
	cJSON* body = cJSON_GetObjectItemCaseSensitive(msg_json, "body");

	if (body == NULL)
	{
		cJSON_Delete(msg_json);

		cmd_ = JsonErrOffset::JSON_FORMAT_ERROR;

		return data_;
	}


	//-----------------------------------------------------------request body data

	if(cmd_ < RecvCmdRangeOffset::START_ACK_CMD_RANGE) //request
	{
		/*
		 * request - write setmode(4),  timesync(10), readparma(11), writeparam(12), task(20~)
		 * */

		switch(cmd_)
		{
			case RequestCmdOffset::REQUEST_SETMODE: //setmode
			{
				cJSON* mode = cJSON_GetObjectItemCaseSensitive(body, "mode");

				if (cJSON_IsString(mode) && (mode->valuestring != NULL))
				{
					int val = atoi(mode->valuestring);

					data_.push_back(val);

				}
				break;
			}


			case RequestCmdOffset::REQUEST_TIMESYNC:  //timesync
			{
				cJSON* systime1 = cJSON_GetObjectItemCaseSensitive(body, "systime1");

				if (cJSON_IsString(systime1) && (systime1->valuestring != NULL))
				{
					int val = atoi(systime1->valuestring);

					data_.push_back(val);
				}

				cJSON* systime2 = cJSON_GetObjectItemCaseSensitive(body, "systime2");

				if (cJSON_IsString(systime2) && (systime2->valuestring != NULL))
				{
					int val = atoi(systime2->valuestring);

					data_.push_back(val);
				}

				break;
			}

			case RequestCmdOffset::REQUEST_READPARAM: //readparam
			{
				cJSON* index = cJSON_GetObjectItemCaseSensitive(body, "index");

				if (cJSON_IsString(index) && (index->valuestring != NULL))
				{
					//int val = atoi(index->valuestring);

					//----------------------------------------------------------make switch case

					//data_.push_back(val);
				}

				break;
			}

			case RequestCmdOffset::REQUEST_WRITEPARAM: //writeparam
			{
				cJSON* index = cJSON_GetObjectItemCaseSensitive(body, "index");

				if (cJSON_IsString(index) && (index->valuestring != NULL))
				{
					//int val = atoi(index->valuestring);

					//----------------------------------------------------------make switch case

					//data_.push_back(val);
				}

				cJSON* data = cJSON_GetObjectItemCaseSensitive(body, "data");

				if (cJSON_IsString(data) && (data->valuestring != NULL))
				{
					int val = atoi(data->valuestring);

					data_.push_back(val);
				}

				break;
			}

			case RequestCmdOffset::REQUEST_TASK: //task
			{
				cJSON* taskType = cJSON_GetObjectItemCaseSensitive(body, "taskType");

				if (cJSON_IsString(taskType) && (taskType->valuestring != NULL))
				{
					int val = atoi(taskType->valuestring);

					data_.push_back(val);

					//switch case
					switch(val)
					{
						case TaskTypeOffset::TASK_MOVE://					 *	move - 1
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* destination = cJSON_GetObjectItemCaseSensitive(body, "destination");

							if (cJSON_IsString(destination) && (destination->valuestring != NULL))
							{
								int val = atoi(destination->valuestring);

								data_.push_back(val);
							}

							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");

							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
							{
								int val = atoi(speed->valuestring);

								data_.push_back(val);
							}

							cJSON* inquireOption = cJSON_GetObjectItemCaseSensitive(body, "inquireOption");

							if (cJSON_IsString(inquireOption) && (inquireOption->valuestring != NULL))
							{
								int val = atoi(inquireOption->valuestring);

								data_.push_back(val);
							}

							break;
						}

						case TaskTypeOffset::TASK_MANUALMOVE://*	manualmove -2
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* distance = cJSON_GetObjectItemCaseSensitive(body, "distance");

							if (cJSON_IsString(distance) && (distance->valuestring != NULL))
							{
								int val = atoi(distance->valuestring);

								data_.push_back(val);
							}

							cJSON* direction = cJSON_GetObjectItemCaseSensitive(body, "direction");

							if (cJSON_IsString(direction) && (direction->valuestring != NULL))
							{
								int val = atoi(direction->valuestring);

								data_.push_back(val);
							}

							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");

							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
							{
								int val = atoi(speed->valuestring);

								data_.push_back(val);
							}

							break;
						}

						case TaskTypeOffset::TASK_PICK: case TaskTypeOffset::TASK_PLACE://					 *	pick -3 *place - 4
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* pickup = cJSON_GetObjectItemCaseSensitive(body, "pickup");

							if (cJSON_IsString(pickup) && (pickup->valuestring != NULL))
							{
								int val = atoi(pickup->valuestring);

								data_.push_back(val);
							}

							cJSON* dropoff = cJSON_GetObjectItemCaseSensitive(body, "dropoff");

							if (cJSON_IsString(dropoff) && (dropoff->valuestring != NULL))
							{
								int val = atoi(dropoff->valuestring);

								data_.push_back(val);
							}

							cJSON* depth = cJSON_GetObjectItemCaseSensitive(body, "depth");

							if (cJSON_IsString(depth) && (depth->valuestring != NULL))
							{
								int val = atoi(depth->valuestring);

								data_.push_back(val);
							}

							cJSON* width = cJSON_GetObjectItemCaseSensitive(body, "width");

							if (cJSON_IsString(width) && (width->valuestring != NULL))
							{
								int val = atoi(width->valuestring);

								data_.push_back(val);
							}

							cJSON* lateralLength = cJSON_GetObjectItemCaseSensitive(body, "lateralLength");

							if (cJSON_IsString(lateralLength) && (lateralLength->valuestring != NULL))
							{
								int val = atoi(lateralLength->valuestring);

								data_.push_back(val);
							}

							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");

							if (cJSON_IsString(speed) && (width->valuestring != NULL))
							{
								int val = atoi(speed->valuestring);

								data_.push_back(val);
							}

							cJSON* inquireOption = cJSON_GetObjectItemCaseSensitive(body, "inquireOption");

							if (cJSON_IsString(inquireOption) && (width->valuestring != NULL))
							{
								int val = atoi(inquireOption->valuestring);

								data_.push_back(val);
							}

							break;
						}

						case TaskTypeOffset::TASK_STROKE://					 *	stroke - 5
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* stroke = cJSON_GetObjectItemCaseSensitive(body, "stroke");

							if (cJSON_IsString(stroke) && (stroke->valuestring != NULL))
							{
								int val = atoi(stroke->valuestring);

								data_.push_back(val);
							}

							cJSON* direction = cJSON_GetObjectItemCaseSensitive(body, "direction");

							if (cJSON_IsString(direction) && (direction->valuestring != NULL))
							{
								int val = atoi(direction->valuestring);

								data_.push_back(val);
							}

							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");

							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
							{
								int val = atoi(speed->valuestring);

								data_.push_back(val);
							}

							break;
						}

						case TaskTypeOffset::TASK_WIDTH://					 *	width - 6
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* width = cJSON_GetObjectItemCaseSensitive(body, "width");

							if (cJSON_IsString(width) && (width->valuestring != NULL))
							{
								int val = atoi(width->valuestring);

								data_.push_back(val);
							}

							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");

							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
							{
								int val = atoi(speed->valuestring);

								data_.push_back(val);
							}

							break;
						}

						case TaskTypeOffset::TASK_FINGER://					 *  finger - 7
						{
							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
							{
								int val = atoi(taskGroup->valuestring);

								data_.push_back(val);
							}

							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
							{
								int val = atoi(taskId->valuestring);

								data_.push_back(val);
							}

							cJSON* finger = cJSON_GetObjectItemCaseSensitive(body, "finger");

							if (cJSON_IsString(finger) && (finger->valuestring != NULL))
							{
								int val = atoi(finger->valuestring);

								data_.push_back(val);
							}

							break;
						}
						default:
							break;
					}
				}
			}
		}
	}

	if(cmd_ < RecvCmdRangeOffset::START_APRROVE_CMD_RANGE) //report - ack
	{
		/*
		 * ack - result
		 * */
		cmd_ -= RecvCmdRangeOffset::START_ACK_CMD_RANGE;

		switch(cmd_)
		{

			case AckCmdOffset::ACK_TASK: case AckCmdOffset::ACK_ALERT://task, alert
			{
				cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");

				if (cJSON_IsString(result) && (result->valuestring != NULL))
				{
					int val = atoi(result->valuestring);

					data_.push_back(val);
				}
				break;
			}

			default:
				break;
		}
	}

	if(cmd_ < RecvCmdRangeOffset::START_EXCUTE_CMD_RANGE) //approve
	{
		/*
		 * approve -action, result
		 * */
		//cmd_ -= RecvCmdRangeOffset::START_APRROVE_CMD_RANGE;

		cJSON* action = cJSON_GetObjectItemCaseSensitive(body, "action");

		if (cJSON_IsString(action) && (action->valuestring != NULL))
		{
			int val = atoi(action->valuestring);

			data_.push_back(val);
		}

		cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");

		if (cJSON_IsString(result) && (result->valuestring != NULL))
		{
			int val = atoi(result->valuestring);

			data_.push_back(val);
		}
	}

	if(cmd_ < RecvCmdRangeOffset::START_RESERVED1_CMD_RANGE) //approve excute
	{
		/*
		 * approve - enterElevator(1),  leaveElevator(2), bufferPick(3), bufferPlace(4)
		 * */

		//cmd_ -= RecvCmdRangeOffset::START_EXCUTE_CMD_RANGE;

		cJSON* taskType = cJSON_GetObjectItemCaseSensitive(body, "taskType");

		if (cJSON_IsString(taskType) && (taskType->valuestring != NULL))
		{
			int val = atoi(taskType->valuestring);

			data_.push_back(val);
		}

		cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");

		if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
		{
			int val = atoi(taskGroup->valuestring);

			data_.push_back(val);
		}

		cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");

		if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
		{
			int val = atoi(taskId->valuestring);

			data_.push_back(val);
		}

		cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");

		if (cJSON_IsString(result) && (result->valuestring != NULL))
		{
			int val = atoi(result->valuestring);

			data_.push_back(val);
		}

	}
	if(cmd_ < RecvCmdRangeOffset::START_RESERVED2_CMD_RANGE) //heartbeat
	{
		//cmd_ -= RecvCmdRangeOffset::START_HEARTTBEAT_CMD_RANGE;

		cJSON* heartbeat = cJSON_GetObjectItemCaseSensitive(body, "heartbeat");

		if (cJSON_IsString(heartbeat) && (heartbeat->valuestring != NULL))
		{
			int val = atoi(heartbeat->valuestring);

			data_.push_back(val);
		}
	}

	cJSON_Delete(msg_json);

	return data_;
}

//Do thing like send queue to openamp-send or tcp-send,

//Dst_->tcp_send_queue_.push_back(cmd_queue_data_);
//Dst_->openamp_send_queue_.push_back(cmd_queue_data_);
//Dst_->fatfs_write_queue_.push_back(cmd_queue_data_);

//save the data to main structure
//WriteDataToMainData(Dst_, configIP_ADDR1_, 168)


//behavior function
int DoCmdFromData(void const* argument, cmd_queue_data data)
{
	data_structure* Dst_ = (data_structure*)argument;

	const cmd_queue_data cmd_queue_data_ = data;

	int cmd_ = cmd_queue_data_.cmd_;

	std::vector<int> parameter_ = cmd_queue_data_.parameter_;



	//send data to tcp sender
	Dst_->tcp_send_queue_.push_back(cmd_queue_data_);


	return 0;
}


//Get All data from ethernet String
int GetDataFromEthernet(void const* argument, const char * const msg, int const msg_leng)
{
	data_structure* Dst_ = (data_structure*)argument;

	cmd_queue_data cmd_queue_data_;

	//get queue data from string
	cmd_queue_data_.transactionid_ = GetTransactionIdFromHeader(msg, msg_leng);

	cmd_queue_data_.cmd_ = GetCmdFromHeader(msg, msg_leng);

	cmd_queue_data_.parameter_= GetDataFromBody(Dst_, msg, msg_leng, cmd_queue_data_.cmd_);


	//do the things from here send queue or data save etc.
	DoCmdFromData(Dst_, cmd_queue_data_);

	return 0;
}



//-------------------------------------------------------------read(get) data from main data




const int ReadDataFromMainData(void const* argument, const char * const msg, int key)
{
	const int key_ = key;

	data_structure* Dst_ = (data_structure*)argument;

	//if key is available
	if (Dst_->main_data_.find(key_) != Dst_->main_data_.end() )
		return Dst_->main_data_.at(key_);

	return -1;

}


//in data out string
int GetStringFromMainData(cmd_queue_data data, char* json_string)
{
	int status = 0;

	const cmd_queue_data cmd_queue_data_ = data;

	//get string data for sending json
	//get transactionid for string



	int cmd_ = cmd_queue_data_.cmd_;

	std::vector<int>parameter_ = cmd_queue_data_.parameter_;

	std::string temp_buffer;


    //-------------------------------------------------------string start

	//make string start
    cJSON* sender = cJSON_CreateObject();

	if (sender == NULL)
	{
		cJSON_Delete(sender);

		cmd_ = JsonErrOffset::JSON_FORMAT_ERROR;
	}


    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */

    //-------------------------------------------------------header contents

    cJSON* header = cJSON_CreateObject();

    cJSON_AddItemToObject(sender, "header", header);



    temp_buffer = std::to_string(cmd_queue_data_.transactionid_);

    cJSON* transactionId = cJSON_CreateString(temp_buffer.c_str());

    //if (transactionId == NULL)
    	//error

	temp_buffer.clear();

    cJSON_AddItemToObject(header, "transactionId", transactionId);


    if(cmd_ < RecvCmdRangeOffset::START_ACK_CMD_RANGE)
    {
    	temp_buffer.append("response");
    }
    else
    {
    	return -1;
    }

    cJSON* msgType = cJSON_CreateString(temp_buffer.c_str());
    //  if (msgType == NULL)

    cJSON_AddItemToObject(header, "msgType", msgType);

	temp_buffer.clear();



    switch(cmd_)
    {
    	case RequestCmdOffset::REQUEST_INFO: temp_buffer.append("info"); break;

    	case RequestCmdOffset::REQUEST_STATUS: temp_buffer.append("status"); break;

    	case RequestCmdOffset::REQUEST_TASKSTATUS: temp_buffer.append("taskCancel"); break;

    	case RequestCmdOffset::REQUEST_SETMODE: temp_buffer.append("taskStatus"); break;

    	case RequestCmdOffset::REQUEST_ALARMCLEAR: temp_buffer.append("setMode"); break;

    	case RequestCmdOffset::REQUEST_SYSRESET: temp_buffer.append("alarmClear"); break;

    	case RequestCmdOffset::REQUEST_TASKPAUSE: temp_buffer.append("sysReset"); break;

    	case RequestCmdOffset::REQUEST_TASKRESUME: temp_buffer.append("taskPause"); break;

    	case RequestCmdOffset::REQUEST_SWEMS: temp_buffer.append("taskResume"); break;

    	case RequestCmdOffset::REQUEST_TIMESYNC: temp_buffer.append("ems"); break;

    	case RequestCmdOffset::REQUEST_READPARAM: temp_buffer.append("readParam"); break;

    	case RequestCmdOffset::REQUEST_WRITEPARAM: temp_buffer.append("writeParam"); break;

    	case RequestCmdOffset::REQUEST_TASK: temp_buffer.append("task"); break;
    }


    cJSON* category = cJSON_CreateString(temp_buffer.c_str());
    //if (category == NULL)

    cJSON_AddItemToObject(header, "category", category);

	temp_buffer.clear();


    cJSON* timeStamp = cJSON_CreateString("1680063015500");
    //if (timeStamp == NULL)

    cJSON_AddItemToObject(header, "timeStamp", timeStamp);


	//get command type for enqeue the command queue

	/*add the if-case command for getting json string data*/


   //cJSON_Print(sender);

    char* temp_data = cJSON_Print(sender);

    memcpy(json_string, temp_data , strlen(cJSON_Print(sender)));

    if (json_string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

    cJSON_Delete(sender);

    free(temp_data);

    temp_buffer.clear();

	return status;
}





























int ethernet_data_parser(const char * const msg, int msg_leng)
{
	//memory copy
	char send_buf[msg_leng + 1];

	strncpy (send_buf, msg, sizeof(send_buf));

	send_buf[msg_leng] = '\0';

	//declare header buffers
    const cJSON *header = NULL;
    const cJSON *transactionid = NULL;
    const cJSON *msgtype = NULL;
    const cJSON *category = NULL;
    const cJSON *timestamp = NULL;

    printf("%s\r\n",send_buf);


    int status = 0;

    //cJSON *msg_json = cJSON_Parse(send_buf);
    cJSON *msg_json = cJSON_ParseWithLength(send_buf, msg_leng);

    //error check
    if (msg_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = -1;
        goto end;
    }

    //Get header object pointer
    header = cJSON_GetObjectItemCaseSensitive(msg_json, "header");

    if (header == NULL)
    {
        status = -1;
        goto end;
    }


    transactionid = cJSON_GetObjectItemCaseSensitive(header, "transactionId");

    if (cJSON_IsString(transactionid) && (transactionid->valuestring != NULL))
    {
        printf("transactionid is: \"%s\"\n", transactionid->valuestring);
    }

    msgtype = cJSON_GetObjectItemCaseSensitive(header, "msgType");

    if (cJSON_IsString(msgtype) && (msgtype->valuestring != NULL))
    {
        printf("msgtype is: \"%s\"\n", msgtype->valuestring);
    }

    category = cJSON_GetObjectItemCaseSensitive(header, "category");

    if (cJSON_IsString(category) && (category->valuestring != NULL))
    {
        printf("category is: \"%s\"\n", category->valuestring);
    }

    timestamp = cJSON_GetObjectItemCaseSensitive(header, "timeStamp");

    if (cJSON_IsString(msgtype) && (timestamp->valuestring != NULL))
    {
        printf("timestamp is: \"%s\"\n", timestamp->valuestring);
    }


    //switch fucntion for each command type

//    if(strcmp(msgtype->valuestring, "request") == 0)
//    {
//       // printf("1\r\n");
//    }
//    else if (strcmp(msgtype->valuestring, "response") == 0)
//    {
//        //printf("2\r\n");
//
//    }
//


end:
    cJSON_Delete(msg_json);
    return status;
}



const char* ethernet_create_message(void)
{

    char* string = NULL;

	//declare header buffers
    cJSON *header = NULL;
    cJSON *transactionId = NULL;
    cJSON *msgType = NULL;
    cJSON *category = NULL;
    cJSON *timeStamp = NULL;

	//declare body buffers
    cJSON *body = NULL;
    cJSON *taskType = NULL;
    cJSON *JobId = NULL;
    cJSON *taskId = NULL;
    cJSON *taskStatus = NULL;
    cJSON *mode = NULL;
    cJSON *status = NULL;
    cJSON *position = NULL;
    cJSON *destination = NULL;
    cJSON *speed = NULL;
    cJSON *forkStroke = NULL;
    cJSON *forkWidth = NULL;
    cJSON *forkOnLoad = NULL;
    cJSON *alarmCode = NULL;
    cJSON *errorCode = NULL;
    cJSON *sensorGroup1 = NULL;
    cJSON *sensorGroup2 = NULL;
    cJSON *odometer = NULL;


    cJSON *sender = cJSON_CreateObject();
    if (sender == NULL)
    {
        goto end;
    }

    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */

    //-------------------------------------------------------header contents

    header = cJSON_CreateObject();
    if (header == NULL)
        goto end;

    cJSON_AddItemToObject(sender, "header", header);

    transactionId = cJSON_CreateString("12");
    if (transactionId == NULL)
        goto end;

    cJSON_AddItemToObject(header, "transactionId", transactionId);

    msgType = cJSON_CreateString("response");
    if (msgType == NULL)
        goto end;

    cJSON_AddItemToObject(header, "msgType", msgType);

    category = cJSON_CreateString("status");
    if (category == NULL)
        goto end;

    cJSON_AddItemToObject(header, "category", category);

    timeStamp = cJSON_CreateString("1680063015500");
    if (timeStamp == NULL)
        goto end;

    cJSON_AddItemToObject(header, "timeStamp", timeStamp);

    //-------------------------------------------------------body contents
    body = cJSON_CreateObject();
    if (body == NULL)
        goto end;

    cJSON_AddItemToObject(sender, "body", body);

    taskType = cJSON_CreateString("move");
    if (taskType == NULL)
        goto end;

    cJSON_AddItemToObject(body, "taskType", taskType);

    JobId = cJSON_CreateString("abcd123456789");
    if (JobId == NULL)
        goto end;

    cJSON_AddItemToObject(body, "JobId", JobId);

    taskId = cJSON_CreateString("1");
    if (taskId == NULL)
        goto end;

    cJSON_AddItemToObject(body, "taskId", taskId);

    taskStatus = cJSON_CreateString("2");
    if (taskStatus == NULL)
        goto end;

    cJSON_AddItemToObject(body, "taskStatus", taskStatus);

    mode = cJSON_CreateString("2");
    if (mode == NULL)
        goto end;

    cJSON_AddItemToObject(body, "mode", mode);

    status = cJSON_CreateString("1");
    if (status == NULL)
        goto end;

    cJSON_AddItemToObject(body, "status", status);

    position = cJSON_CreateString("1234");
    if (position == NULL)
        goto end;

    cJSON_AddItemToObject(body, "position", position);

    destination = cJSON_CreateString("12345");
    if (destination == NULL)
        goto end;

    cJSON_AddItemToObject(body, "destination", destination);

    speed = cJSON_CreateString("4200");
    if (speed == NULL)
        goto end;

    cJSON_AddItemToObject(body, "speed", speed);

    forkStroke = cJSON_CreateString("0");
    if (forkStroke == NULL)
        goto end;

    cJSON_AddItemToObject(body, "forkStroke", forkStroke);

    forkWidth = cJSON_CreateString("500");
    if (forkWidth == NULL)
        goto end;

    cJSON_AddItemToObject(body, "forkWidth", forkWidth);

    forkOnLoad = cJSON_CreateString("3");
    if (forkOnLoad == NULL)
        goto end;

    cJSON_AddItemToObject(body, "forkOnLoad", forkOnLoad);

    alarmCode = cJSON_CreateString("0");
    if (alarmCode == NULL)
        goto end;

    cJSON_AddItemToObject(body, "alarmCode", alarmCode);

    errorCode = cJSON_CreateString("0");
    if (errorCode == NULL)
        goto end;

    cJSON_AddItemToObject(body, "errorCode", errorCode);

    sensorGroup1 = cJSON_CreateString("0");
    if (sensorGroup1 == NULL)
        goto end;

    cJSON_AddItemToObject(body, "sensorGroup1", sensorGroup1);

    sensorGroup2 = cJSON_CreateString("0");
    if (sensorGroup2 == NULL)
        goto end;

    cJSON_AddItemToObject(body, "sensorGroup2", sensorGroup2);

    odometer = cJSON_CreateString("4294967296");
    if (odometer == NULL)
        goto end;

    cJSON_AddItemToObject(body, "odometer", odometer);



    string = cJSON_Print(sender);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }
    cJSON_free (string);

end:

    cJSON_Delete(sender);
    return string;
}














/* return 1 if the monitor supports full hd, 0 otherwise */
int supports_full_hd(const char * const msg, int msg_leng)
{
	char send_buf[msg_leng + 1];

	strncpy (send_buf, msg, sizeof(send_buf));

	send_buf[msg_leng] = '\0';

	char* st = NULL;

    const cJSON *value = NULL;
    const cJSON *values = NULL;
    const cJSON *command = NULL;
    const cJSON *mode = NULL;

    int status = 0;

    cJSON *msg_json = cJSON_Parse(send_buf);

    //error check
    if (msg_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    //command parse
    command = cJSON_GetObjectItemCaseSensitive(msg_json, "command");

    if (cJSON_IsString(command) && (command->valuestring != NULL))
    {
        printf("command is: \"%s\"\n", command->valuestring);
    }

    //mode parse
    mode = cJSON_GetObjectItemCaseSensitive(msg_json, "mode");

    if (cJSON_IsString(mode) && (mode->valuestring != NULL))
    {
        printf("mode is: \"%s\"\n", mode->valuestring);
    }

    //value parse
    values = cJSON_GetObjectItemCaseSensitive(msg_json, "values");

    //for
    cJSON_ArrayForEach(value, values)
    {
        cJSON *from = cJSON_GetObjectItemCaseSensitive(value, "from");
        cJSON *to = cJSON_GetObjectItemCaseSensitive(value, "to");

        printf("from : %d, to :%d \r\n", from->valueint, to->valueint);

        itoa(from->valueint, st, 10);

//        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
//        {
//            status = 0;
//            goto end;
//        }
//
//        if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
//        {
//            status = 1;
//            goto end;
//        }
    }



end:
    cJSON_Delete(msg_json);
    return status;
}

//create a monitor with a list of supported resolutions
//NOTE: Returns a heap allocated string, you are required to free it after use.
const char* create_monitor(void)
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char *string = NULL;
    cJSON *command = NULL;
    cJSON *mode = NULL;
    cJSON *values = NULL;
    cJSON *value = NULL;
    cJSON *from = NULL;
    cJSON *to = NULL;
    size_t index = 0;

    cJSON *sender = cJSON_CreateObject();

    if (sender == NULL)
    {
        goto end;
    }

    command = cJSON_CreateString("Stop");
    if (command == NULL)
    {
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transferring ownership of the pointer to it */
    cJSON_AddItemToObject(sender, "command", command);

    mode = cJSON_CreateString("Auto");
    if (mode == NULL)
    {
        goto end;
    }

    cJSON_AddItemToObject(sender, "mode", mode);


    values = cJSON_CreateArray();
    if (values == NULL)
    {
        goto end;
    }
    cJSON_AddItemToObject(sender, "values", values);

    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
    	value = cJSON_CreateObject();
        if (value == NULL)
        {
            goto end;
        }
        cJSON_AddItemToArray(values, value);

        from = cJSON_CreateNumber(resolution_numbers[index][0]);
        if (from == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(value, "from", from);

        to = cJSON_CreateNumber(resolution_numbers[index][1]);
        if (to == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(value, "to", to);
    }

    string = cJSON_Print(sender);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(sender);
    return string;
}

//-----------------------------------------------------------Eth

struct netconn* ConnectEthToDataStructure()
{

}







