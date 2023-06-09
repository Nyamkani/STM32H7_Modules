/*
 * fatfs.c
 *
 *  Created on: Mar 16, 2023
 *      Author: studio3s
 */



#include <fatfs_h7/include/fatfs_h7/fatfs_h7.h>
/* Private variables ---------------------------------------------------------*/
	//FATFS data
	FATFS SDFatFs;  /* File system object for SD card logical drive */
	FIL SDFile;
	char SDPath[4]; /* SD card logical drive path */



static bool is_init_ = false;
char workBuffer[FF_MAX_SS];

static void BSPInit()
{
	if(!(is_init_)) BSP_SD_Init();

	if(BSP_SD_IsDetected()) is_init_ = true;

	return;
}



void FatFsInit()
{

	if(FATFS_LinkDriver(&SD_Driver, SDPath) == 0)
	{
		BSPInit();

		if(BSP_SD_IsDetected())
		{
			FRESULT res;

			res = f_mkfs(SDPath, 0, workBuffer, sizeof(workBuffer));

			if(res != FR_OK) return; // Error_Handler();

			if(f_mount(&SDFatFs, (TCHAR const*)SDPath, 1) != FR_OK) return;

			printf("Successfully formatted\n");
		}


	}

	return;
}



void FatFsTest(const char *filename)
{
  FRESULT res;
  uint32_t written_bytes=0 ,read_bytes= 0;
  char buf[50];
  char readbuf[200] =  {0.};

  int total_byte_ = 0;
  const char *p = "FatFs example for STM32F747i-Dicovery!\r\n";

  res = f_open(&SDFile, (const char*)filename, FA_CREATE_ALWAYS | FA_WRITE);
  //res = f_open(&SDFile, "test.txt", FA_CREATE_ALWAYS | FA_WRITE);

  if(res == FR_OK){
    sprintf(buf, "%s\r\n", p);
    f_write(&SDFile, (const void*)buf, strlen(buf), (unsigned int*)&written_bytes);
    printf("%ld bytes written.\r\n", written_bytes);

    total_byte_ += written_bytes;

    sprintf(buf, "Filename : %s\r\n", filename);
    f_write(&SDFile, (const void*)buf, strlen(buf), (unsigned int*)&written_bytes);
    printf("%ld bytes written.\r\n", written_bytes);

    total_byte_ += written_bytes;

    sprintf(buf, "Tick : %ld\r\n", HAL_GetTick());
    f_write(&SDFile, (const void*)buf, strlen(buf), (unsigned int*)&written_bytes);
    printf("%ld bytes written.\r\n", written_bytes);

    total_byte_ += written_bytes;

    sprintf(buf, "parameter1 : 3\r\n");
    f_write(&SDFile, (const void*)buf, strlen(buf), (unsigned int*)&written_bytes);
    printf("%ld bytes written.\r\n", written_bytes);

    total_byte_ += written_bytes;

    sprintf(buf, "parameter2 : 5\r\n");
    f_write(&SDFile, (const void*)buf, strlen(buf), (unsigned int*)&written_bytes);
    printf("%ld bytes written.\r\n", written_bytes);

    total_byte_ += written_bytes;

    printf("total %d bytes written.\r\n", total_byte_);

    f_close(&SDFile);

    res = f_open(&SDFile, (const char*)filename, FA_READ);
    if(res == FR_OK)
    {
        printf("\r\n---------------Reading Start-----------------\r\n");
        res = f_read(&SDFile, readbuf, sizeof(readbuf), (unsigned int*)&read_bytes);

        if(res == FR_OK && read_bytes > 0) printf("%s",readbuf);

        printf("\r\n---------------Reading End-----------------\r\n");

        printf("total read bytes : %d\r\n", total_byte_);
    }



    f_close(&SDFile);

    printf("SD card Writing is successfully complete!\n");
  }else{
  	printf("[ERROR] f_open failed (%d)\r\n", (int)res);
  }
}

int SDCard_Write(const char *filename, const char *msg, int msg_leng_)
{
	const char* msg_ = msg;
	FRESULT res = FR_OK;
	uint32_t written_bytes=0;
	//char no_null_char_buf[msg_leng_+1];

	char char_buf[msg_leng_ +1];

	strncpy (char_buf, msg_, msg_leng_);   // get the message from the client

	char_buf[msg_leng_] = '\0';

	res = f_open(&SDFile, (const char*)filename, FA_WRITE | FA_OPEN_APPEND);

	if(res == FR_OK)
	{
		//sprintf(buf, "Your TCP data was : %s\r\n", msg_);
		//sprintf(buf, "Your TCP data was : %s\r\n", msg_);
		f_write(&SDFile, (const void*)char_buf, strlen(char_buf), (unsigned int*)&written_bytes);
		printf("%s is written, Tick : %ld, %ld bytes written.\r\n", char_buf, HAL_GetTick(), written_bytes);

	    f_close(&SDFile);
	}

	return (int)res;
}

int SDCard_Read(const char *filename)
{
	char read_buf_[255];
	FRESULT res = FR_OK;

	res = f_open(&SDFile, (const char*)filename, FA_READ);

	if(res == FR_OK)
	{
		while(f_gets((TCHAR*)&read_buf_, sizeof(read_buf_), &SDFile) != NULL)
		{
			printf("%s", read_buf_);
		}

		f_close(&SDFile);
	}
	return (int)res;
}


