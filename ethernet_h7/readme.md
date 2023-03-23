%standard Flash Memory Area
CPU1(CM7) 0x00800000
CPU2(CM4) 0x00810000

%standard sRam area
CPU1 D1 0x24000000(512KB) D2 0x30000000 (288KB) D3 0x38000000 (64KB)
CPU2 D1 0x10000000(KB) D2 0x10020000 (KB) D3 0x10040000 (KB)

%since we are using eth. we use sram d2 - 0x30020000 ~ 0x30047fff ~160kb
rx buffer heap pointer: 0x30020000
rx descriptor : 0x30040000
tx descriptor: 0x30040060

% project defime - DATA_IN_D2_SRAM



*this project has modifed for eth.

Changed files are followed below.

1. STM32H747XIHX_FLASH.ld -> memory area has been changed. also, lwip ram memory area has beed added.

2. ethernetif.c, lwip.c -> ethernet link thread has been deleted -> merging with ethernet_input thread 

3. LAN8742.c -> auto nego. time increased 2s->5s


Applied files are followed below.


1. udp server, client source files

2. tcp server, client source files
 



0. Enable rtos -> 512 words, 32768 heap memory, cmsis-v1 recommended

1.. lwip 
 3)-1. MEM_Size(heap) 0x20000 -> 128KB byte(s) 
 3)-2. main memory pointer is in D3 - 0x30020000~ 0x30040000 (128KB - refer 3)-1.)

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

 5. MPU settings
  -1. enable i/d cache and Protection area in D3(lwip) 0x30040000~(32KB) all enable(permtiable) and buffable is disable
