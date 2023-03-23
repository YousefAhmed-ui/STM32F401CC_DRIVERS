################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Source/GPIO.c \
../src/Source/HLED.c \
../src/Source/HLED_cfg.c \
../src/Source/NVIC.c \
../src/Source/RCC.c 

OBJS += \
./src/Source/GPIO.o \
./src/Source/HLED.o \
./src/Source/HLED_cfg.o \
./src/Source/NVIC.o \
./src/Source/RCC.o 

C_DEPS += \
./src/Source/GPIO.d \
./src/Source/HLED.d \
./src/Source/HLED_cfg.d \
./src/Source/NVIC.d \
./src/Source/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
src/Source/%.o: ../src/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"D:\iti_9m_diploma\ARM_ITI\ARM_WorkSpace\Hello_NVIC\src\Include" -I"D:\iti_9m_diploma\ARM_ITI\ARM_WorkSpace\Hello_NVIC\src\Source" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


