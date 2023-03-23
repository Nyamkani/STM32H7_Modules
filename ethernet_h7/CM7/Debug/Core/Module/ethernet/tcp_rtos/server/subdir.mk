################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.c 

C_DEPS += \
./Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.d 

OBJS += \
./Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Module/ethernet/tcp_rtos/server/%.o Core/Module/ethernet/tcp_rtos/server/%.su: ../Core/Module/ethernet/tcp_rtos/server/%.c Core/Module/ethernet/tcp_rtos/server/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DDATA_IN_D2_SRAM -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H747xx -c -I../Core/Inc -I"/home/studio3s/STM32CubeIDE/workspace_1.11.0/STM32H7_Modules/ethernet_h7/CM7/Core/Module" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../../Middlewares/Third_Party/LwIP/src/include -I../../Middlewares/Third_Party/LwIP/system -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/BSP/Components/lan8742 -I../../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../../Middlewares/Third_Party/LwIP/src/include/lwip -I../../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../../Middlewares/Third_Party/LwIP/src/include/netif -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Module-2f-ethernet-2f-tcp_rtos-2f-server

clean-Core-2f-Module-2f-ethernet-2f-tcp_rtos-2f-server:
	-$(RM) ./Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.d ./Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.o ./Core/Module/ethernet/tcp_rtos/server/tcp_rtos_server.su

.PHONY: clean-Core-2f-Module-2f-ethernet-2f-tcp_rtos-2f-server

