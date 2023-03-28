#this project has generated for Ethernet+rtos for stm32h7.


* standard Flash Memory Area
    * CPU1(CM7) 0x00800000
    * CPU2(CM4) 0x00810000

* standard sRam area
    * CPU1 
        * D1 0x24000000 (512KB) 
        * D2 0x30000000 (288KB) 
        * D3 0x38000000 (64KB)
    * CPU2 (alias)
        * D1 0x10000000 (KB) 
        * D2 0x10020000 (KB) 
        * D3 0x10040000 (KB)


* 0. Modified this code to linker  "xx_flash.ld"

```c

/* Memories definition */
MEMORY
{
  ...

  /*change this*/
  /* ETH_CODE: change offset & reduce size of RAM_D2 to not collide with M4 */
  RAM_D2 (xrw)   : ORIGIN = 0x30020000, LENGTH = 160K

  ...
}

...

/* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */
._user_heap_stack :
{
  ...
} >RAM_D1

/*add this*/
/* ETH_CODE: add placement of DMA descriptors and RX buffers */
.lwip_sec (NOLOAD) :
{
. = ABSOLUTE(0x30040000);
*(.RxDecripSection) 

. = ABSOLUTE(0x30040060);
*(.TxDecripSection)

. = ABSOLUTE(0x30040200);
*(.Rx_PoolSection)  
} >RAM_D2


```

* 1. Add define for project configuration "xx_flash.ld"

    * 1-1. c/c++ build -> GCC/G++ compiler -> preprocesser - > add "DATA_IN_D2_SRAM"


* 2. Changed files are followed below.

    * 2-1. STM32H747XIHX_FLASH.ld -> memory area has been changed. also, lwip ram memory area has beed added.

    * 2-2. ethernetif.c, lwip.c -> ethernet link thread has been deleted -> merging with ethernet_input thread 

    * 2-3. LAN8742.c -> auto nego. time increased 2s->5s

* 3. Added files are followed below.

    * 3-1. udp server, client source files

    * 3-2. tcp server, client source files

* 4. .ioc - ethernet + rtos settings

    * 4-1. Enable rtos -> 512 words, 30720 heap memory, cmsis-v1 recommended

    * 4-2. lwip 

        * 4-2-1). MEM_Size(heap) 0x20000 -> 128KB byte(s) 

        * 4-3-2). main memory pointer is in D2-SRAM3 - 0x30020000 ~ 0x30040000 



* 5. MPU settings

    * 5-1. enable i/d cache and Protection area in D3(lwip) 0x30040000~(32KB) all enable(permtiable) and buffable is disable

```c


/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x30020000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.BaseAddress = 0x30040000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512B;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

```