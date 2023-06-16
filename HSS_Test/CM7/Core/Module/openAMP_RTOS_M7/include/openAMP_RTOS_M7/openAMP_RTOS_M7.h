/*
 * openAMP_RTOS_M7.h
 *
 *  Created on: Mar 8, 2023
 *      Author: studio3s
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_
#define MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_

#include <iostream>
#include <string>
#include <functional>
#include <algorithm>


#include <api_data_structure/include/api_data_structure/api_data_structure.h>

#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7_define.h>

#include "stm32h7xx_hal.h"
#include "openamp.h"
#include "cmsis_os.h"



#ifdef __cplusplus
 extern "C" {
#endif


#ifdef __cplusplus
}
#endif






class OpenAMP_M7
{
	private:
		/*main data structure*/
		data_structure* Dst_ = nullptr;

		/*status values*/
		bool is_init_ = false;
		bool is_run_ = false;
		bool is_error_ = false;

		/*sync(scheduler queue*/
		std::vector<priority_data> send_data_queue_;

	public:

	private:
		void startTask();
		int OpenAMPSendToSlave(openamp_data data);
		static void service_destroy_cb(struct rpmsg_endpoint *ept);
		static void new_service_cb(struct rpmsg_device *rdev, const char *name, uint32_t dest);
		static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data,
		                size_t len, uint32_t src, void *priv);


		static void OpenAMPOperationTask(void const *argument);
		static void OpenAMPChkMsgtask(void const *argument);

	public:
		OpenAMP_M7();
		OpenAMP_M7(data_structure* Dst);
		virtual ~OpenAMP_M7();

		void Initialize();

		OpenAMP_M7& SetData(data_structure* Dst);


};






#endif /* MODULE_OPENAMP_RTOS_M7_INCLUDE_OPENAMP_RTOS_M7_OPENAMP_RTOS_M7_H_ */
