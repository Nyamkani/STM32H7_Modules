################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Module/fatfs_h7/src/fatfs_h7.c 

C_DEPS += \
./Core/Module/fatfs_h7/src/fatfs_h7.d 

OBJS += \
./Core/Module/fatfs_h7/src/fatfs_h7.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Module/fatfs_h7/src/%.o Core/Module/fatfs_h7/src/%.su Core/Module/fatfs_h7/src/%.cyclo: ../Core/Module/fatfs_h7/src/%.c Core/Module/fatfs_h7/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../Core/Inc -I"/home/kssvm/STM32CubeIDE/workspace_1.10.1/STM32H7_Modules/sdmmc_h7/CM7/Core/Module" -I../LWIP/App -I../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/lan8742 -I../../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Middlewares/Third_Party/LwIP/src/include/lwip -I../../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../../Middlewares/Third_Party/LwIP/src/include/netif -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../../Middlewares/Third_Party/LwIP/system/arch -I../../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Module-2f-fatfs_h7-2f-src

clean-Core-2f-Module-2f-fatfs_h7-2f-src:
	-$(RM) ./Core/Module/fatfs_h7/src/fatfs_h7.cyclo ./Core/Module/fatfs_h7/src/fatfs_h7.d ./Core/Module/fatfs_h7/src/fatfs_h7.o ./Core/Module/fatfs_h7/src/fatfs_h7.su

.PHONY: clean-Core-2f-Module-2f-fatfs_h7-2f-src

