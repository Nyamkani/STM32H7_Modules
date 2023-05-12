/*
 * api_cjson.cpp
 *
 *  Created on: Apr 28, 2023
 *      Author: studio3s
 */




#include "cjson/include/cjson/api_cjson.h"
#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>



int ethernet_data_parser(const char * const msg, int msg_leng)
{
	//memory copy
	char send_buf[msg_leng + 1];

	strncpy (send_buf, msg, sizeof(send_buf));

	send_buf[msg_leng] = '\0';

	//declare buffers
    const cJSON *header = NULL;
    const cJSON *transactionid = NULL;
    const cJSON *msgtype = NULL;
    const cJSON *category = NULL;
    const cJSON *timestamp = NULL;

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


    //data command

    if(strcmp(msgtype->valuestring, "request") == 0)
    {
       // printf("1\r\n");
    }
    else if (strcmp(msgtype->valuestring, "response") == 0)
    {
        //printf("2\r\n");

    }



end:
    cJSON_Delete(msg_json);
    return status;
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


