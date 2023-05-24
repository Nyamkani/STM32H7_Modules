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
	Dst_->main_data_.insert(std::pair<int, int>(robot_name_, 1));
	Dst_->main_data_.insert(std::pair<int, int>(fw_version_, 1));

	//ipaddress_info
	Dst_->main_data_.insert(std::pair<int, int>(configIP_ADDR0, 192));
	Dst_->main_data_.insert(std::pair<int, int>(configIP_ADDR1, 168));
	Dst_->main_data_.insert(std::pair<int, int>(configIP_ADDR2, 17));
	Dst_->main_data_.insert(std::pair<int, int>(configIP_ADDR3, 11));

	Dst_->main_data_.insert(std::pair<int, int>(configNET_MASK0, 255));
	Dst_->main_data_.insert(std::pair<int, int>(configNET_MASK1, 255));
	Dst_->main_data_.insert(std::pair<int, int>(configNET_MASK2, 255));
	Dst_->main_data_.insert(std::pair<int, int>(configNET_MASK3, 0));

	Dst_->main_data_.insert(std::pair<int, int>(configGW_ADDR0, 192));
	Dst_->main_data_.insert(std::pair<int, int>(configGW_ADDR1, 168));
	Dst_->main_data_.insert(std::pair<int, int>(configGW_ADDR2, 17));
	Dst_->main_data_.insert(std::pair<int, int>(configGW_ADDR3, 1));

	//status_page_1;
	Dst_->main_data_.insert(std::pair<int, int>(mode_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(status_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(position_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(destination_, 0));

	Dst_->main_data_.insert(std::pair<int, int>(speed_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(fork_stroke_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(fork_width_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(fork_on_load_, 0));

	Dst_->main_data_.insert(std::pair<int, int>(alarm_code_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(error_code_, 0));

	//status_page_2
	Dst_->main_data_.insert(std::pair<int, int>(sensor_input_, 0));

	//status_page_3
	Dst_->main_data_.insert(std::pair<int, int>(task_type_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(job_id_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(task_id_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(task_status_, 0));

	Dst_->main_data_.insert(std::pair<int, int>(pending_task_no_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(callback_msg_, 0));

	//vehicle_config_page_1
	Dst_->main_data_.insert(std::pair<int, int>(move_limit_min_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(move_limit_max_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(elevator_entry_pos_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(elevator_board_pos_, 0));

	Dst_->main_data_.insert(std::pair<int, int>(elevator_exit_pos_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(fwd_stop_calibration_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(bwd_stop_calibration_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(position_correction_constant_, 0));

	//vehicle_config_page_2
	Dst_->main_data_.insert(std::pair<int, int>(move_speed1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(move_acc1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(move_speed2_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(move_acc2_, 0));

	//attach_config
	Dst_->main_data_.insert(std::pair<int, int>(stroke_speed1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(stroke_acc1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(stroke_speed2_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(stroke_acc2_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(width_speed1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(width_acc1_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(width_speed2_, 0));
	Dst_->main_data_.insert(std::pair<int, int>(width_acc2_, 0));


	//1. success the allocate
//	if(main_data_)
		status = 1;

	return status;
}



//-------------------------------------------------------------write data to main data
//int WriteDataToMainData(int key, int value)
//{
//	int status = -1;
//
//	const int key_ = key, value_ = value;
//
//	//if key is available
//	if (Dst_->main_data_.find(key_) != Dst_->main_data_.end() )
//	{
//		main_data_.at(key_) = value_;
//
//		status = 1;
//	}
//
//	return status;
//}


//json parsing and get command or write thing
int GetDataFromEthernet(const char * const msg, int msg_leng)
{
	int status = 1;
	_Message* send_msg = NULL;

	//memory copy
	char recv_buf[msg_leng + 1] = {0,};

	strncpy (recv_buf, msg, msg_leng);

	//declare header buffers
    const cJSON *header = NULL;
    const cJSON *transactionid = NULL;
    const cJSON *msgtype = NULL;
    const cJSON *category = NULL;
    const cJSON *timestamp = NULL;



	//-----------------------------------------------------------
	  //cJSON *msg_json = cJSON_Parse(send_buf);
	cJSON *msg_json = cJSON_ParseWithLength(recv_buf, msg_leng+1);

	//error check
	if (msg_json == NULL)
	{
		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL)
		{
			//fprintf(stderr, "Error before: %s\n", error_ptr);
			//parsing error
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

	if(strcmp(msgtype->valuestring, "request") == 0)
	{
	   // printf("1\r\n");

		if(strcmp(category->valuestring, "info") == 0)
		{
			//send 'robot_info' data


			send_msg->id_ = 0x11;
			send_msg->cmd_ = 1;

			//osMessagePut(TCPSendQueueHandle, (uint32_t)(&send_msg), 100); //enqueue

		}
		else if(strcmp(category->valuestring, "status") == 0)
		{
			//send 'task_status and status_page_1,2,3' data
			//send_msg = (_Message *)osPoolAlloc (Pool_ID);


			send_msg->id_ = 0x11;
			send_msg->cmd_ = 2;

		//	osMessagePut(TCPSendQueueHandle, (uint32_t)(send_msg), 10); //enqueue
			//osMessagePut(TCPSendQueueHandle, (uint32_t)(&send_msg), 100); //enqueue

		}
		else if(strcmp(category->valuestring, "taskCancel") == 0)
		{
			//send 'result' data
		}


	}
	else if (strcmp(msgtype->valuestring, "ack") == 0)
	{
		//printf("2\r\n");

	}
	else if (strcmp(msgtype->valuestring, "approve") == 0)
	{
		//printf("3\r\n");

	}
	else if (strcmp(msgtype->valuestring, "heartbeatresponse") == 0)
	{
		//printf("3\r\n");

	}
	else
	{
		//unknown recv data error

	}


	end:
		cJSON_Delete(msg_json);

	return status;
}






















//const int ReadDataFromMainData(int key)
//{
//	const int key_ = key;
//
//	//if key is available
//	if (Dst_->main_data_.find(key_) != Dst_->main_data_.end() )
//	{
//		main_data_.at(key_) = value_;
//
//		return main_data_.at(key_);
//	}
//	return -1;
//
//}


































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







