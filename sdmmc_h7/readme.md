# this project has generated for mdma+sdmmc+FATfs+rtos for stm32h7.
  
## 0. porting fatfs library - > use "R0.15" Highly recommended because lib. generated from cubeide is not working(R0.12)  
  
    0-1. highly recommend to copy fatfs lib. from this project  
  
    0-2. make generate code using cubeide then paste related "Fatfs" lib.  
  
## 1. .ioc - sdmmc1 + MDMA settings  
  
    1-1. sdmmc1- cortex-m7 enable - sd 4 bits wide bus  
  
    1-2. mdma - add channel - sdmmc1 data end  
  
    1-3. nvic - sdmmc1 global interrupt, mdma global interrupt  
  
    1-4. fatfs(m7) - detect_sdio ->gpio:input - uSD_Detect  
    
## 2. Modified this code to linker  "xx_flash.ld"  

```c

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM_D1) + LENGTH(RAM_D1); /* end of "RAM_D1" Ram type memory */

/*change this*/
_Min_Heap_Size = 0x400; /* required amount of heap  */
_Min_Stack_Size = 0x800; /* required amount of stack */


``` 

## 3. in sd_diskio.c file  
	line 72. if you use MDMA.  

```c

/*make define uncomment*/ 
"#define ENABLE_SD_DMA_CACHE_MAINTENANCE  1"

/*line 262. if you use MDMA. edit your code */ 
/*change this*/
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)
//uint32_t alignedAddr;

    /*---Edited for managing DCache*/
    uint32_t alignedAddr = (uint32_t)buff & ~0x1F;

    SCB_CleanDCache_by_Addr((uint32_t*)alignedAddr,
            count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));

    SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr,
                    count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));
    /*---Edited for managing DCache*/

#endif

...

/*line 317. if you use MDMA. edit your code*/ 
/*change this*/
#if (ENABLE_SD_DMA_CACHE_MAINTENANCE == 1)

            /*the SCB_InvalidateDCache_by_Addr() requires a 32-Byte aligned address,
            adjust the address and the D-Cache size to invalidate accordingly.*/

            //alignedAddr = (uint32_t)buff & ~0x1F;
            //SCB_InvalidateDCache_by_Addr((uint32_t*)alignedAddr, count*BLOCKSIZE + ((uint32_t)buff - alignedAddr));
#endif

```