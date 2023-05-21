################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.cpp 

OBJS += \
./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.o 

CPP_DEPS += \
./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Module/openAMP_RTOS_M4/src/%.o Core/Module/openAMP_RTOS_M4/src/%.su Core/Module/openAMP_RTOS_M4/src/%.cyclo: ../Core/Module/openAMP_RTOS_M4/src/%.cpp Core/Module/openAMP_RTOS_M4/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H747xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=1024 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I"/home/kssvm/STM32CubeIDE/workspace_1.10.1/STM32H7_Modules/HSS_Test/CM4/Core/Module" -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Module-2f-openAMP_RTOS_M4-2f-src

clean-Core-2f-Module-2f-openAMP_RTOS_M4-2f-src:
	-$(RM) ./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.cyclo ./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.d ./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.o ./Core/Module/openAMP_RTOS_M4/src/openAMP_RTOS_M4.su

.PHONY: clean-Core-2f-Module-2f-openAMP_RTOS_M4-2f-src

