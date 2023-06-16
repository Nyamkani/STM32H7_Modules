/*
 * ShuttleMain.h
 *
 *  Created on: Jun 16, 2023
 *      Author: studio3s
 */

#ifndef MODULE_SHUTTLE_MAIN_M7_INCLUDE_SHUTTLE_MAIN_M7_SHUTTLE_MAIN_M7_H_
#define MODULE_SHUTTLE_MAIN_M7_INCLUDE_SHUTTLE_MAIN_M7_SHUTTLE_MAIN_M7_H_


#include <openAMP_RTOS_M7/include/openAMP_RTOS_M7/openAMP_RTOS_M7.h>
#include <ethernet/tcp_rtos/server/tcp_rtos_server.h>

class ShuttleMain
{
	private:
		data_structure* Dst_ = nullptr;

		TcpRtos* TcpRtos_ = nullptr;
		OpenAMP_M7* OpenAMP_M7_ = nullptr;
		//FATF* fatfs = nullptr;

	public:

	private:


	public:
		ShuttleMain();
		ShuttleMain(data_structure* data_structure_global);
		ShuttleMain(data_structure* data_structure_global
									, TcpRtos* TcpRtos_global
									, OpenAMP_M7* OpenAMP_M7_global);

		virtual ~ShuttleMain();

		void Initialize();
};

#endif /* MODULE_SHUTTLE_MAIN_M7_INCLUDE_SHUTTLE_MAIN_M7_SHUTTLE_MAIN_M7_H_ */
