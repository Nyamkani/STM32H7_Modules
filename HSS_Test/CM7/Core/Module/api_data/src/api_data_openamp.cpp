/*
 * api_data_openamp.cpp
 *
 *  Created on: Jun 17, 2023
 *      Author: kssvm
 */



#include <api_data/include/api_data/api_data.h>



//-----------------------------------------------------------openamp app

priority_data GetOpenAMPRequestCommand(int cmd_code, void* data)
{
	priority_data data_;

	const int cmd_ = cmd_code;

	std::vector<int> parameter_= (std::vector<int>*)data;


	/*behavior from cmd*/
	if(cmd_ >= IPCFuctionOffset::IPC_CONTROL 
		&& cmd_ < IPCFuctionOffset::IPC_CALLBACK) //control
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;

	}
	else if(cmd_ >= IPCFuctionOffset::IPC_CALLBACK 
		&& cmd_ < IPCFuctionOffset::IPC_EXCUTE) //Callback
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;

		switch (cmd_)
		{
		case 301:

			break;
		
		default:
			break;
		}


	}

	else if(cmd_ >= IPCFuctionOffset::IPC_EXCUTE 
		&& cmd_ < IPCFuctionOffset::IPC_PARAM) //excute
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;
	}

	else if(cmd_ >= IPCFuctionOffset::IPC_PARAM 
		&& cmd_ < IPCFuctionOffset::IPC_TASK) //read/write param
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;
	}

	else if(cmd_ >= IPCFuctionOffset::IPC_TASK 
		&& cmd_ < IPCFuctionOffset::TPC_READSTATUS) //task
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;
	}
	else if(cmd_ >= IPCFuctionOffset::TPC_READSTATUS 
		&& cmd_ < IPCFuctionOffset::IPC_RESERVED1) //readstatus
	{
		data_.priority = cmd_ / 100;
		data_.data_.cmd_ = cmd_;
	}








	return data_;
}










//priority_data GetDataFromOtherThread(cmd_queue_data data)
//{
//	priority_data converted_data_;
//
//	const cmd_queue_data data_ = data;
//
//	/*analizing and decoding*/
//
//	uint16_t cmd_ = data_.cmd_;
//
//	/*behavior from cmd*/
//	if(cmd_ >= RecvCmdRangeOffset::RECV_REQUEST_CMD_RANGE
//		&& cmd_ < RecvCmdRangeOffset::RECV_ACK_CMD_RANGE)
//	{
//		/*
//		 * request - write setmode(4),  timesync(10), readparma(11), writeparam(12), task(20~)
//		 * */
//
//		switch(cmd_)
//		{
//			case RequestCmdOffset::REQUEST_SETMODE: //setmode
//			{
//				cJSON* mode = cJSON_GetObjectItemCaseSensitive(body, "mode");
//
//				if (cJSON_IsString(mode) && (mode->valuestring != NULL))
//				{
//					int val = atoi(mode->valuestring);
//
//					data_.push_back(val);
//
//				}
//				break;
//			}
//
//
//			case RequestCmdOffset::REQUEST_TIMESYNC:  //timesync
//			{
//				cJSON* systime1 = cJSON_GetObjectItemCaseSensitive(body, "systime1");
//
//				if (cJSON_IsString(systime1) && (systime1->valuestring != NULL))
//				{
//					int val = atoi(systime1->valuestring);
//
//					data_.push_back(val);
//				}
//
//				cJSON* systime2 = cJSON_GetObjectItemCaseSensitive(body, "systime2");
//
//				if (cJSON_IsString(systime2) && (systime2->valuestring != NULL))
//				{
//					int val = atoi(systime2->valuestring);
//
//					data_.push_back(val);
//				}
//
//				break;
//			}
//
//			case RequestCmdOffset::REQUEST_READPARAM: //readparam
//			{
//				cJSON* index = cJSON_GetObjectItemCaseSensitive(body, "index");
//
//				if (cJSON_IsString(index) && (index->valuestring != NULL))
//				{
//					//int val = atoi(index->valuestring);
//
//					//----------------------------------------------------------make switch case
//
//					//data_.push_back(val);
//				}
//
//				break;
//			}
//
//			case RequestCmdOffset::REQUEST_WRITEPARAM: //writeparam
//			{
//				cJSON* index = cJSON_GetObjectItemCaseSensitive(body, "index");
//
//				if (cJSON_IsString(index) && (index->valuestring != NULL))
//				{
//					//int val = atoi(index->valuestring);
//
//					//----------------------------------------------------------make switch case
//
//					//data_.push_back(val);
//				}
//
//				cJSON* data = cJSON_GetObjectItemCaseSensitive(body, "data");
//
//				if (cJSON_IsString(data) && (data->valuestring != NULL))
//				{
//					int val = atoi(data->valuestring);
//
//					data_.push_back(val);
//				}
//
//				break;
//			}
//
//			case RequestCmdOffset::REQUEST_TASK: //task
//			{
//				cJSON* taskType = cJSON_GetObjectItemCaseSensitive(body, "taskType");
//
//				if (cJSON_IsString(taskType) && (taskType->valuestring != NULL))
//				{
//					int val = atoi(taskType->valuestring);
//
//					data_.push_back(val);
//
//					//switch case
//					switch(val)
//					{
//						case TaskTypeOffset::TASK_MOVE://					 *	move - 1
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* destination = cJSON_GetObjectItemCaseSensitive(body, "destination");
//
//							if (cJSON_IsString(destination) && (destination->valuestring != NULL))
//							{
//								int val = atoi(destination->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");
//
//							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
//							{
//								int val = atoi(speed->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* inquireOption = cJSON_GetObjectItemCaseSensitive(body, "inquireOption");
//
//							if (cJSON_IsString(inquireOption) && (inquireOption->valuestring != NULL))
//							{
//								int val = atoi(inquireOption->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//
//						case TaskTypeOffset::TASK_MANUALMOVE://*	manualmove -2
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* distance = cJSON_GetObjectItemCaseSensitive(body, "distance");
//
//							if (cJSON_IsString(distance) && (distance->valuestring != NULL))
//							{
//								int val = atoi(distance->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* direction = cJSON_GetObjectItemCaseSensitive(body, "direction");
//
//							if (cJSON_IsString(direction) && (direction->valuestring != NULL))
//							{
//								int val = atoi(direction->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");
//
//							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
//							{
//								int val = atoi(speed->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//
//						case TaskTypeOffset::TASK_PICK: case TaskTypeOffset::TASK_PLACE://					 *	pick -3 *place - 4
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* pickup = cJSON_GetObjectItemCaseSensitive(body, "pickup");
//
//							if (cJSON_IsString(pickup) && (pickup->valuestring != NULL))
//							{
//								int val = atoi(pickup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* dropoff = cJSON_GetObjectItemCaseSensitive(body, "dropoff");
//
//							if (cJSON_IsString(dropoff) && (dropoff->valuestring != NULL))
//							{
//								int val = atoi(dropoff->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* depth = cJSON_GetObjectItemCaseSensitive(body, "depth");
//
//							if (cJSON_IsString(depth) && (depth->valuestring != NULL))
//							{
//								int val = atoi(depth->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* width = cJSON_GetObjectItemCaseSensitive(body, "width");
//
//							if (cJSON_IsString(width) && (width->valuestring != NULL))
//							{
//								int val = atoi(width->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* lateralLength = cJSON_GetObjectItemCaseSensitive(body, "lateralLength");
//
//							if (cJSON_IsString(lateralLength) && (lateralLength->valuestring != NULL))
//							{
//								int val = atoi(lateralLength->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");
//
//							if (cJSON_IsString(speed) && (width->valuestring != NULL))
//							{
//								int val = atoi(speed->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* inquireOption = cJSON_GetObjectItemCaseSensitive(body, "inquireOption");
//
//							if (cJSON_IsString(inquireOption) && (width->valuestring != NULL))
//							{
//								int val = atoi(inquireOption->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//
//						case TaskTypeOffset::TASK_STROKE://					 *	stroke - 5
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* stroke = cJSON_GetObjectItemCaseSensitive(body, "stroke");
//
//							if (cJSON_IsString(stroke) && (stroke->valuestring != NULL))
//							{
//								int val = atoi(stroke->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* direction = cJSON_GetObjectItemCaseSensitive(body, "direction");
//
//							if (cJSON_IsString(direction) && (direction->valuestring != NULL))
//							{
//								int val = atoi(direction->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");
//
//							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
//							{
//								int val = atoi(speed->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//
//						case TaskTypeOffset::TASK_WIDTH://					 *	width - 6
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* width = cJSON_GetObjectItemCaseSensitive(body, "width");
//
//							if (cJSON_IsString(width) && (width->valuestring != NULL))
//							{
//								int val = atoi(width->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* speed = cJSON_GetObjectItemCaseSensitive(body, "speed");
//
//							if (cJSON_IsString(speed) && (speed->valuestring != NULL))
//							{
//								int val = atoi(speed->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//
//						case TaskTypeOffset::TASK_FINGER://					 *  finger - 7
//						{
//							cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//							if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//							{
//								int val = atoi(taskGroup->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//							if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//							{
//								int val = atoi(taskId->valuestring);
//
//								data_.push_back(val);
//							}
//
//							cJSON* finger = cJSON_GetObjectItemCaseSensitive(body, "finger");
//
//							if (cJSON_IsString(finger) && (finger->valuestring != NULL))
//							{
//								int val = atoi(finger->valuestring);
//
//								data_.push_back(val);
//							}
//
//							break;
//						}
//						default:
//							break;
//					}
//				}
//			}
//		}
//	}
//
//	else if(cmd_ >= RecvCmdRangeOffset::RECV_ACK_CMD_RANGE
//		&& cmd_ < RecvCmdRangeOffset::RECV_ANSWER_CMD_RANGE) //report - ack
//	{
//		/*
//		 * ack - result
//		 * */
//		cmd_ -= RecvCmdRangeOffset::RECV_ACK_CMD_RANGE;
//
//		switch(cmd_)
//		{
//
//			case AckCmdOffset::ACK_TASK: case AckCmdOffset::ACK_ALERT://task, alert
//			{
//				cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");
//
//				if (cJSON_IsString(result) && (result->valuestring != NULL))
//				{
//					int val = atoi(result->valuestring);
//
//					data_.push_back(val);
//				}
//				break;
//			}
//
//			default:
//				break;
//		}
//	}
//
//	else if(cmd_ >= RecvCmdRangeOffset::RECV_ANSWER_CMD_RANGE
//		&& cmd_ < RecvCmdRangeOffset::RECV_EXCUTE_CMD_RANGE) //answer
//	{
//		/*
//		 * approve -action, result
//		 * */
//		//cmd_ -= RecvCmdRangeOffset::START_ANSWER_CMD_RANGE;
//
//		cJSON* action = cJSON_GetObjectItemCaseSensitive(body, "action");
//
//		if (cJSON_IsString(action) && (action->valuestring != NULL))
//		{
//			int val = atoi(action->valuestring);
//
//			data_.push_back(val);
//		}
//
//		cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");
//
//		if (cJSON_IsString(result) && (result->valuestring != NULL))
//		{
//			int val = atoi(result->valuestring);
//
//			data_.push_back(val);
//		}
//	}
//
//	else if(cmd_ >= RecvCmdRangeOffset::RECV_EXCUTE_CMD_RANGE
//		&& cmd_ < RecvCmdRangeOffset::RECV_RESERVED1_CMD_RANGE) //approve excute
//	{
//		/*
//		 * approve - enterElevator(1),  leaveElevator(2), bufferPick(3), bufferPlace(4)
//		 * */
//
//		//cmd_ -= RecvCmdRangeOffset::START_EXCUTE_CMD_RANGE;
//
//		cJSON* taskType = cJSON_GetObjectItemCaseSensitive(body, "taskType");
//
//		if (cJSON_IsString(taskType) && (taskType->valuestring != NULL))
//		{
//			int val = atoi(taskType->valuestring);
//
//			data_.push_back(val);
//		}
//
//		cJSON* taskGroup = cJSON_GetObjectItemCaseSensitive(body, "taskGroup");
//
//		if (cJSON_IsString(taskGroup) && (taskGroup->valuestring != NULL))
//		{
//			int val = atoi(taskGroup->valuestring);
//
//			data_.push_back(val);
//		}
//
//		cJSON* taskId = cJSON_GetObjectItemCaseSensitive(body, "taskId");
//
//		if (cJSON_IsString(taskId) && (taskId->valuestring != NULL))
//		{
//			int val = atoi(taskId->valuestring);
//
//			data_.push_back(val);
//		}
//
//		cJSON* result = cJSON_GetObjectItemCaseSensitive(body, "result");
//
//		if (cJSON_IsString(result) && (result->valuestring != NULL))
//		{
//			int val = atoi(result->valuestring);
//
//			data_.push_back(val);
//		}
//
//	}
//	else if(cmd_ >= RecvCmdRangeOffset::RECV_HEARTTBEAT_CMD_RANGE
//		&& cmd_ < RecvCmdRangeOffset::RECV_RESERVED2_CMD_RANGE) //heartbeat
//	{
//		//cmd_ -= RecvCmdRangeOffset::START_HEARTTBEAT_CMD_RANGE;
//
//		cJSON* heartbeat = cJSON_GetObjectItemCaseSensitive(body, "heartbeat");
//
//		if (cJSON_IsString(heartbeat) && (heartbeat->valuestring != NULL))
//		{
//			int val = atoi(heartbeat->valuestring);
//
//			data_.push_back(val);
//		}
//
//	}
//	return
//}
//
//
//int GetDataFromSlave()
//
//
//
//
//





