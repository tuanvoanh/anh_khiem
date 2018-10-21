################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../core/core.c 

OBJS += \
./core/core.o 

C_DEPS += \
./core/core.d 


# Each subdirectory must supply rules for building sources it contributes
core/%.o: ../core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F030x6 -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/Inc" -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/Drivers/STM32F0xx_HAL_Driver/Inc" -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/Drivers/STM32F0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/Drivers/CMSIS/Device/ST/STM32F0xx/Include" -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/Drivers/CMSIS/Include" -I"C:/Users/Administrator/Desktop/Part time/19_10Read_five_Devices/19_10Read_five_Device/core"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


