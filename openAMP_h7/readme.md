# this project has generated for rtos+openAMP for stm32h7.

* 0. Modified this code to linker  "xx_flash.ld"

```c

MEMORY
{
...

  /*add this*/
	OPEN_AMP_RSC_TAB (xrw)	: ORIGIN = 0x38000000, LENGTH = 1K
	OPEN_AMP_SHMEM (xrw) : ORIGIN = 0x38000400, LENGTH = 63K
}

  /*add this*/
__OPENAMP_region_start__ = ORIGIN(OPEN_AMP_SHMEM);
__OPENAMP_region_end__ = ORIGIN(OPEN_AMP_SHMEM) + LENGTH(OPEN_AMP_SHMEM);

...

/* User_heap_stack section, used to check that there is enough "RAM" Ram  type memory left */
._user_heap_stack :
{
...
} >RAM_D1

/*add this*/
.openamp_section (NOLOAD) : 
{
  . = ABSOLUTE(0x38000000);
  *(.resource_table)
} > OPEN_AMP_RSC_TAB AT >FLASH

```


0. Enable rtos -> 512 words, 32768 heap memory, cmsis-v1 recommended


2. Check the debug setting 
 2)-1. cm7 - add cm4 debug download
 2)-2. cm4 - under reset to none / change the cm7 port (rec. +3(core number)
 
 3. RTOS task struct change(for cpp)
 3)-1. char -> const char
  
4. change the code in OpenAMP/virtqueue.h(for Cpp)
 4)-1. in 211.  'um_desc_extra * sizeof(struct vq_desc_extra);'
                         to  'num_desc_extra * sizeof(vqs->vq_descx[0]);'
 
 5. change the code in CMSIS_RTOS/cmsis_os.h(for Cpp)
  -1. in 281.  ' char  *name;'        
                          to 'const char  *name;'  

