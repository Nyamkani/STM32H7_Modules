*this project has generated for mdma+sdmmc+FATfs.

*. porting fatfs library - > use "R0.15" Highly recommended because lib. generated from cubeide is not working(R0.12)
    *-1. highly recommend to copy fatfs lib. from this project 
    *-2. make generate code using cubeide then paste related "Fatfs" lib.

1. .ioc - sdmmc1 + MDMA settings
    1)-1. sdmmc1- cortex-m7 enable - sd 4 bits wide bus
    1)-2. mdma - add channel - sdmmc1 data end
    1)-3. nvic - sdmmc1 global interrupt, mdma global interrupt
    1)-4. fatfs(m7) - detect_sdio ->gpio:input - uSD_Detect
    
2. in sd_diskio.c file
	line 72. if you use MDMA . uncomment "#define ENABLE_SD_DMA_CACHE_MAINTENANCE  1"
    
    
