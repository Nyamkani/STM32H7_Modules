################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Module/api_debug/api_debug.cpp 

OBJS += \
./Core/Module/api_debug/api_debug.o 

CPP_DEPS += \
./Core/Module/api_debug/api_debug.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Module/api_debug/%.o Core/Module/api_debug/%.su: ../Core/Module/api_debug/%.cpp Core/Module/api_debug/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DDATA_IN_D2_SRAM -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=1024 -DVIRTIO_MASTER_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I"/home/studio3s/STM32CubeIDE/workspace_1.11.0/STM32H7_Modules/HSS_Test/CM7/Core/Module" -I../LWIP/App -I../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/lan8742 -I../../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Middlewares/Third_Party/LwIP/src/include/lwip -I../../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../../Middlewares/Third_Party/LwIP/src/include/netif -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../../Middlewares/Third_Party/LwIP/system/arch -I../../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Module-2f-api_debug

clean-Core-2f-Module-2f-api_debug:
	-$(RM) ./Core/Module/api_debug/api_debug.d ./Core/Module/api_debug/api_debug.o ./Core/Module/api_debug/api_debug.su

.PHONY: clean-Core-2f-Module-2f-api_debug
