/*
 * api_lwjson.cpp
 *
 *  Created on: Apr 27, 2023
 *      Author: studio3s
 */


#include "lwjson/include/lwjson/api_lwjson.h"

#include <stdio.h>
#include "lwjson/include/lwjson/lwjson.h"

/* LwJSON instance and tokens */
static lwjson_token_t tokens[128];
static lwjson_t lwjson;

/* Parse JSON */
void example_minimal_run()
{
    lwjson_init(&lwjson, tokens, LWJSON_ARRAYSIZE(tokens));
    if (lwjson_parse(&lwjson, "{\"mykey\":\"myvalue\"}") == lwjsonOK) {
        const lwjson_token_t* t;
        printf("JSON parsed..\r\n");

        /* Find custom key in JSON */
        if ((t = lwjson_find(&lwjson, "mykey")) != NULL) {
            printf("Key found with data type: %d\r\n", (int)t->type);
        }

        /* Call this when not used anymore */
        lwjson_free(&lwjson);
    }
    return;
}

/* Parse JSON */
void example_traverse_run(const char* msg, int msg_leng)
{

	char send_buf[msg_leng + 1];

	strncpy (send_buf, msg, sizeof(send_buf));

	send_buf[msg_leng] = '\0';


    /* Initialize and pass statically allocated tokens */
    lwjson_init(&lwjson, tokens, LWJSON_ARRAYSIZE(tokens));

    /* Try to parse input string */
    if (lwjson_parse(&lwjson, send_buf) == lwjsonOK)
    //if (lwjson_parse(&lwjson, "{\"mykey\":\"myvalue\",\"num\":1,\"obj\":{},\"arr\":[1,2,3,4]}") == lwjsonOK)
    //if (lwjson_parse(&lwjson, "{\"command\":\"0x11\",\"id\":0x01,\"obj\":{},\"arr\":[1,2,3,4]}") == lwjsonOK)
    {
        lwjson_token_t* t;
        printf("JSON parsed..\r\n");

        /* Get very first token as top object */
        t = lwjson_get_first_token(&lwjson);

        if (t->type == LWJSON_TYPE_ARRAY) {
            printf("JSON starts with array..\r\n");
        } else if (t->type == LWJSON_TYPE_OBJECT) {
            printf("JSON starts with object..\r\n");
        } else {
            printf("This should never happen..\r\n");
        }


        /* Now print all keys in the object */

        const lwjson_token_t* tkn1 = lwjson_find(&lwjson, "command");
        const lwjson_token_t* tkn2 = lwjson_find(&lwjson, "value.#0");


        printf("Token name: %.*s", (int)tkn1->token_name_len, tkn1->token_name);
        printf(" : %.*s\r\n", (int)tkn1->u.str.token_value_len, tkn1->u.str.token_value);

        printf("Token name : %.*s", (int)tkn2->token_name_len, tkn2->token_name);

		for (const lwjson_token_t* tkn = lwjson_get_first_child(tkn2); tkn != NULL; tkn = tkn->next)
		{
	        printf(" : %.*s\r\n", (int)tkn->u.str.token_value_len, tkn->u.str.token_value);
		}




//        for (const lwjson_token_t* tkn = lwjson_get_first_child(t); tkn != NULL; tkn = tkn->next)
//        {
//
//            printf("Token: %.*s", (int)tkn->token_name_len, tkn->token_name);
//            printf(": %.*s", (int)tkn->u.str.token_value_len, tkn->u.str.token_value);
//
//            if (tkn->type == LWJSON_TYPE_ARRAY || tkn->type == LWJSON_TYPE_OBJECT)
//            {
//
//                printf(": Token is array or object...check children tokens if any, in recursive mode..");
//                /* Get first child of token */
//                //lwjson_get_first_child(tkn);
//            }
//            printf("\n");
//        }

        /* Call this when not used anymore */
        lwjson_free(&lwjson);
    }
    return;
}



