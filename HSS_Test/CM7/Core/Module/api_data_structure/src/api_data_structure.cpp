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
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::ROBOT_NAME_, 11));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FW_VERSION, 102));

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
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::POSITION, 123456));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::DESTINATION, 1));

	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::SPEED, 100));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_STROKE, 20));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_WIDTH, 34));
	Dst_->main_data_.insert(std::pair<int, int>(RobotDataId::FORK_ON_LOAD, 1));

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

	//declare header buffers
    const cJSON *header = NULL;

    const cJSON *transactionid = NULL;

	//-----------------------------------------------------------
	cJSON *msg_json = cJSON_ParseWithLength(msg, msg_leng);

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

	//declare header buffers
    const cJSON *header = NULL;
    const cJSON *msgtype = NULL;
    const cJSON *category = NULL;
    //const cJSON *timestamp = NULL;


	//-----------------------------------------------------------
	cJSON *msg_json = cJSON_ParseWithLength(msg, msg_leng);

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
		cmd += RecvCmdRangeOffset::RECV_REQUEST_CMD_RANGE;

		if(strcmp(category->valuestring, "info") == 0) cmd += RequestCmdOffset::REQUEST_INFO;

		else if(strcmp(category->valuestring, "status") == 0) cmd += RequestCmdOffset::REQUEST_STATUS;

		else if(strcmp(category->valuestring, "taskCancel") == 0) cmd += RequestCmdOffset::REQUEST_TASKCANCEL;

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
		cmd += RecvCmdRangeOffset::RECV_ACK_CMD_RANGE;

		if(strcmp(category->valuestring, "task") == 0) cmd += AckCmdOffset::ACK_TASK;

		else if(strcmp(category->valuestring, "alert") == 0) cmd += AckCmdOffset::ACK_ALERT;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "answer") == 0)
	{
		cmd += RecvCmdRangeOffset::RECV_ANSWER_CMD_RANGE;

		if(strcmp(category->valuestring, "enterElevator") == 0) cmd += AnswerCmdOffset::ANSWER_ENTERELEVATOR;

		else if(strcmp(category->valuestring, "leaveElevator") == 0) cmd += AnswerCmdOffset::ANSWER_LEAVEELEVATOR;

		else if(strcmp(category->valuestring, "bufferPick") == 0) cmd += AnswerCmdOffset::ANSWER_BUFFERPICK;

		else if(strcmp(category->valuestring, "bufferPlace") == 0) cmd += AnswerCmdOffset::ANSWER_BUFFERPLACE;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "execute") == 0)
	{
		cmd += RecvCmdRangeOffset::RECV_EXCUTE_CMD_RANGE;

		if(strcmp(category->valuestring, "enterElevator") == 0) cmd += ExcuteCmdOffset::EXCUTE_ENTERELEVATOR;

		else if(strcmp(category->valuestring, "leaveElevator") == 0) cmd += ExcuteCmdOffset::EXCUTE_LEAVEELEVATOR;

		else if(strcmp(category->valuestring, "bufferPick") == 0) cmd += ExcuteCmdOffset::EXCUTE_BUFFERPICK;

		else if(strcmp(category->valuestring, "bufferPlace") == 0) cmd += ExcuteCmdOffset::EXCUTE_BUFFERPLACE;

		else cmd = JsonErrOffset::JSON_WRONG_DATA_ERROR;

	}

	else if (strcmp(msgtype->valuestring, "heartbeatRequset") == 0)
	{
		cmd += RecvCmdRangeOffset::RECV_HEARTTBEAT_CMD_RANGE;

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
	std::vector<int> data_;

	data_.clear();

	int cmd_  = cmd;

	//-----------------------------------------------------------
	cJSON* msg_json = cJSON_ParseWithLength(msg, msg_leng);

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

	if(cmd_ >= RecvCmdRangeOffset::RECV_REQUEST_CMD_RANGE
		&& cmd_ < RecvCmdRangeOffset::RECV_ACK_CMD_RANGE)
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

	else if(cmd_ >= RecvCmdRangeOffset::RECV_ACK_CMD_RANGE
		&& cmd_ < RecvCmdRangeOffset::RECV_ANSWER_CMD_RANGE) //report - ack
	{
		/*
		 * ack - result
		 * */
		cmd_ -= RecvCmdRangeOffset::RECV_ACK_CMD_RANGE;

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

	else if(cmd_ >= RecvCmdRangeOffset::RECV_ANSWER_CMD_RANGE
		&& cmd_ < RecvCmdRangeOffset::RECV_EXCUTE_CMD_RANGE) //answer
	{
		/*
		 * approve -action, result
		 * */
		//cmd_ -= RecvCmdRangeOffset::START_ANSWER_CMD_RANGE;

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

	else if(cmd_ >= RecvCmdRangeOffset::RECV_EXCUTE_CMD_RANGE
		&& cmd_ < RecvCmdRangeOffset::RECV_RESERVED1_CMD_RANGE) //approve excute
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
	else if(cmd_ >= RecvCmdRangeOffset::RECV_HEARTTBEAT_CMD_RANGE
		&& cmd_ < RecvCmdRangeOffset::RECV_RESERVED2_CMD_RANGE) //heartbeat
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
	if(cmd_queue_data_.cmd_  != 65535)
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




const int ReadDataFromMainData(void const* argument, int key)
{
	const int key_ = key;

	data_structure* Dst_ = (data_structure*)argument;

	//if key is available
	if (Dst_->main_data_.find(key_) != Dst_->main_data_.end() )
		return Dst_->main_data_.at(key_);

	return -1;

}

//in data out string
int GetStringFromMainData(void const* argument, cmd_queue_data data, char* json_string)
{
	int status = 0;

	data_structure* Dst_ = (data_structure*)argument;

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

	//-------------------------------transactionId

    temp_buffer = std::to_string(cmd_queue_data_.transactionid_);

    cJSON* transactionId = cJSON_CreateString(temp_buffer.c_str());
    //if (transactionId == NULL)

    cJSON_AddItemToObject(header, "transactionId", transactionId);

	temp_buffer.clear();

	//-------------------------------msgtype

	if(cmd_ >= SendCmdRangeOffset::SEND_RESPONSE_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_REPORT_CMD_RANGE)
    		temp_buffer.append("response");

	else if(cmd_ >= SendCmdRangeOffset::SEND_REPORT_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE)
			temp_buffer.append("report");

	else if(cmd_ >= SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE)
			temp_buffer.append("inquire");

	else if(cmd_ >= SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_RESERVED1_CMD_RANGE)
			temp_buffer.append("confirm");

	else if(cmd_ >= SendCmdRangeOffset::SEND_HEARTTBEAT_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_RESERVED2_CMD_RANGE)
			temp_buffer.append("heartbeat");



    cJSON* msgType = cJSON_CreateString(temp_buffer.c_str());

    cJSON_AddItemToObject(header, "msgType", msgType);

	temp_buffer.clear();

	//-------------------------------category

	if(cmd_ >= SendCmdRangeOffset::SEND_RESPONSE_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_REPORT_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_RESPONSE_CMD_RANGE;

	    switch(cmd_)
	    {
	    	case ResponseCmdOffset::RESPONSE_INFO: temp_buffer.append("info"); break;

	    	case ResponseCmdOffset::RESPONSE_STATUS: temp_buffer.append("status"); break;

			case ResponseCmdOffset::RESPONSE_TASKCANCEL: temp_buffer.append("taskCancel"); break;

	    	case ResponseCmdOffset::RESPONSE_TASKSTATUS: temp_buffer.append("taskStatus"); break;

	    	case ResponseCmdOffset::RESPONSE_SETMODE: temp_buffer.append("setMode"); break;

	    	case ResponseCmdOffset::RESPONSE_ALARMCLEAR: temp_buffer.append("alarmClear"); break;

	    	case ResponseCmdOffset::RESPONSE_SYSRESET: temp_buffer.append("sysReset"); break;

	    	case ResponseCmdOffset::RESPONSE_TASKPAUSE: temp_buffer.append("taskPause"); break;

	    	case ResponseCmdOffset::RESPONSE_TASKRESUME: temp_buffer.append("taskResume"); break;

	    	case ResponseCmdOffset::RESPONSE_SWEMS: temp_buffer.append("ems"); break;

	    	case ResponseCmdOffset::RESPONSE_TIMESYNC: temp_buffer.append("timeSync"); break;

	    	case ResponseCmdOffset::RESPONSE_READPARAM: temp_buffer.append("readParam"); break;

	    	case ResponseCmdOffset::RESPONSE_WRITEPARAM: temp_buffer.append("writeParam"); break;

	    	case ResponseCmdOffset::RESPONSE_TASK: temp_buffer.append("task"); break;
	    }
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_REPORT_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_REPORT_CMD_RANGE;

	    switch(cmd_)
	    {
			case ReportCmdOffset::REPORT_TASK: temp_buffer.append("task"); break;

			case ReportCmdOffset::REPORT_ALERT: temp_buffer.append("alert"); break;
	    }
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE;

	    switch(cmd_)
	    {
			case InquireCmdOffset::INQUIRE_ENTERELEVATOR: temp_buffer.append("enterElevator"); break;

			case InquireCmdOffset::INQUIRE_LEAVEELEVATOR: temp_buffer.append("leaveElevator"); break;

			case InquireCmdOffset::INQUIRE_BUFFERPICK: temp_buffer.append("bufferPick"); break;

			case InquireCmdOffset::INQUIRE_BUFFERPLACE: temp_buffer.append("bufferPlace"); break;

	    }
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_RESERVED1_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE;

	    switch(cmd_)
	    {
			case ConfirmCmdOffset::CONFIRM_ENTERELEVATOR: temp_buffer.append("enterElevator"); break;

			case ConfirmCmdOffset::CONFIRM_LEAVEELEVATOR: temp_buffer.append("leaveElevator"); break;

			case ConfirmCmdOffset::CONFIRM_BUFFERPICK: temp_buffer.append("bufferPick"); break;

			case ConfirmCmdOffset::CONFIRM_BUFFERPLACE: temp_buffer.append("bufferPlace"); break;
	    }
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_HEARTTBEAT_CMD_RANGE
		&& cmd_ <SendCmdRangeOffset::SEND_RESERVED2_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_HEARTTBEAT_CMD_RANGE;
		
	    switch(cmd_)
	    {
			case HeartbeatCmdOffset::heartbeat: temp_buffer.append("heartbeatresponse"); break;
	    }
	}


   cJSON* category = cJSON_CreateString(temp_buffer.c_str());
   // if (category == NULL)

    cJSON_AddItemToObject(header, "category", category);

	temp_buffer.clear();


	//-------------------------------timestamp

    cJSON* timeStamp = cJSON_CreateString("1680063015500");
   // if (timeStamp == NULL)


    cJSON_AddItemToObject(header, "timeStamp", timeStamp);


	//get command type for enqeue the command queue

	/*add the if-case command for getting json string data*/



    //-------------------------------------------------------body contents

	cJSON* body = cJSON_CreateObject();

	cJSON_AddItemToObject(sender, "body", body);


	//----------------------------------------request
	if(cmd_ >= SendCmdRangeOffset::SEND_RESPONSE_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_REPORT_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_RESPONSE_CMD_RANGE;

		switch(cmd_)
		{
			case ResponseCmdOffset::RESPONSE_INFO:
			{
				int val = 0;

				std::string str;

				/*------------------------*/

				val = ReadDataFromMainData(Dst_, RobotDataId::ROBOT_NAME_);

				str.append("ST");

				std::string robot_name_ = std::to_string(val);

				if (robot_name_.length() < 2)
				{
					int itr = 2 - robot_name_.length();

					for(int i = 0; i < itr; i++)
						str.append("0");
				}


				//if (robot_name_.length() < 2)
				//	str.insert(str.front() == '-' ? 1 : 0, 2 - str.length(), '0');

				str.append(std::to_string(val));

				cJSON* name = cJSON_CreateString(str.c_str());
				// if (category == NULL)

				cJSON_AddItemToObject(body, "name", name);

				str.clear();

				/*------------------------*/
				AddItemToObjectFromMainData(Dst_, body, "fwver", RobotDataId::FW_VERSION);

				break;
			}

			case ResponseCmdOffset::RESPONSE_STATUS:
			{

				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				AddItemToObjectFromMainData(Dst_, body, "taskStatus", RobotDataId::TASK_STATUS);

				AddItemToObjectFromMainData(Dst_, body, "mode", RobotDataId::MODE);

				AddItemToObjectFromMainData(Dst_, body, "status", RobotDataId::STATUS);

				AddItemToObjectFromMainData(Dst_, body, "position", RobotDataId::POSITION);

				AddItemToObjectFromMainData(Dst_, body, "destination", RobotDataId::DESTINATION);

				AddItemToObjectFromMainData(Dst_, body, "speed", RobotDataId::SPEED);

				AddItemToObjectFromMainData(Dst_, body, "forkStroke", RobotDataId::FORK_STROKE);

				AddItemToObjectFromMainData(Dst_, body, "forkWidth", RobotDataId::FORK_WIDTH);

				AddItemToObjectFromMainData(Dst_, body, "forkOnLoad", RobotDataId::FORK_ON_LOAD);

				AddItemToObjectFromMainData(Dst_, body, "alarmCode", RobotDataId::ALARM_CODE);

				AddItemToObjectFromMainData(Dst_, body, "errorCode", RobotDataId::ERROR_CODE);

				//AddItemToObjectFromMainData(Dst_, body, "odometer", RobotDataId::ODOMETER);

				AddItemToObjectFromMainData(Dst_, body, "sensorInput", RobotDataId::SENSOR_INPUT);

				break;
			}

			case ResponseCmdOffset::RESPONSE_TASKCANCEL:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_TASKSTATUS:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				AddItemToObjectFromMainData(Dst_, body, "taskStatus", RobotDataId::TASK_STATUS);

				break;
			}

			case ResponseCmdOffset::RESPONSE_SETMODE:
			{
				AddItemToObjectFromMainData(Dst_, body, "mode", RobotDataId::MODE);

				break;
			}

			case ResponseCmdOffset::RESPONSE_ALARMCLEAR:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_SYSRESET:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_TASKPAUSE:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_TASKRESUME:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_SWEMS:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_TIMESYNC:
			{
				cJSON* item = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case ResponseCmdOffset::RESPONSE_READPARAM: 
			{

				break;
			}


			case ResponseCmdOffset::RESPONSE_WRITEPARAM:
			{

				break;
			}

			case ResponseCmdOffset::RESPONSE_TASK:
			{
				int tasktype = parameter_.front();

				cJSON* taskType = cJSON_CreateString(std::to_string(tasktype).c_str());
				// if (category == NULL)

				cJSON_AddItemToObject(body, "taskType", taskType);

				int taskgroup = parameter_.at(1);

				cJSON* taskGroup = cJSON_CreateString(std::to_string(taskgroup).c_str());
				// if (category == NULL)

				cJSON_AddItemToObject(body, "taskGroup", taskGroup);

				int taskid = parameter_.at(2);

				cJSON* taskId = cJSON_CreateString(std::to_string(taskid).c_str());
				// if (category == NULL)

				cJSON_AddItemToObject(body, "taskId", taskId);

				cJSON* result = cJSON_CreateString("1");
				// if (category == NULL)

				cJSON_AddItemToObject(body, "result", result);

				break;
			}
		}
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_REPORT_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_REPORT_CMD_RANGE;

		switch(cmd_)
		{
			case ReportCmdOffset::REPORT_TASK:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				AddItemToObjectFromMainData(Dst_, body, "taskStatus", RobotDataId::TASK_STATUS);

				AddItemToObjectFromMainData(Dst_, body, "alramCode", RobotDataId::ALARM_CODE);

				AddItemToObjectFromMainData(Dst_, body, "errorCode", RobotDataId::ERROR_CODE);

				break;
			}

			case ReportCmdOffset::REPORT_ALERT:
			{
				AddItemToObjectFromMainData(Dst_, body, "alramCode", RobotDataId::ALARM_CODE);

				AddItemToObjectFromMainData(Dst_, body, "errorCode", RobotDataId::ERROR_CODE);

				break;
			}
		}
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_INQUIRE_CMD_RANGE;

		switch(cmd_)
		{
			case InquireCmdOffset::INQUIRE_ENTERELEVATOR:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				break;
			}

			case InquireCmdOffset::INQUIRE_LEAVEELEVATOR:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				break;
			}

			case InquireCmdOffset::INQUIRE_BUFFERPICK:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				break;
			}

			case InquireCmdOffset::INQUIRE_BUFFERPLACE:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				break;
			}
		}
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_RESERVED1_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_CONFIRM_CMD_RANGE;

		switch(cmd_)
		{

			case InquireCmdOffset::INQUIRE_ENTERELEVATOR:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				cJSON* item = cJSON_CreateString("1");
					// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case InquireCmdOffset::INQUIRE_LEAVEELEVATOR:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				cJSON* item = cJSON_CreateString("1");
					// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case InquireCmdOffset::INQUIRE_BUFFERPICK:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				cJSON* item = cJSON_CreateString("1");
					// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}

			case InquireCmdOffset::INQUIRE_BUFFERPLACE:
			{
				AddItemToObjectFromMainData(Dst_, body, "taskType", RobotDataId::TASK_TYPE);

				AddItemToObjectFromMainData(Dst_, body, "taskGroup", RobotDataId::TASK_GROUP);

				AddItemToObjectFromMainData(Dst_, body, "taskId", RobotDataId::TASK_ID);

				cJSON* item = cJSON_CreateString("1");
					// if (category == NULL)

				cJSON_AddItemToObject(body, "result", item);

				break;
			}
		}
	}

	else if(cmd_ >= SendCmdRangeOffset::SEND_HEARTTBEAT_CMD_RANGE
		&& cmd_ < SendCmdRangeOffset::SEND_RESERVED2_CMD_RANGE)
	{
		cmd_ -= SendCmdRangeOffset::SEND_HEARTTBEAT_CMD_RANGE;
	}

    //-------------------------------------------------------printing
	//static char* temp_data = cJSON_Print(sender);


	char* temp_data = cJSON_Print(sender);

    if (temp_data == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

	memcpy(json_string, temp_data , strlen(temp_data));

	cJSON_free(temp_data);

	cJSON_Delete(sender);

	return status;
}








//-----------------------------------------------------------Eth

struct netconn* ConnectEthToDataStructure()
{

}

//-----------------------------------------------------------Eth


void AddItemToObjectFromMainData(void const* argument, cJSON* object, const char* item_name, int main_data_index)
{
	data_structure* Dst_ = (data_structure*)argument;

	int val = ReadDataFromMainData(Dst_, main_data_index);

	std::string str(std::to_string(val));

	cJSON* item = cJSON_CreateString(str.c_str());
	// if (category == NULL)

	cJSON_AddItemToObject(object, item_name, item);

	return;
}


//-----------------------------------------------------------openamp app




