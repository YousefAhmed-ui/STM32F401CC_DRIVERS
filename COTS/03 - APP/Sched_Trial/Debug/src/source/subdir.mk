################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/source/App.c \
../src/source/GPIO.c \
../src/source/HLED.c \
../src/source/HLED_cfg.c \
../src/source/RCC.c \
../src/source/SCHED.c \
../src/source/SCHED_cfg.c \
../src/source/SYSTICK.c 

OBJS += \
./src/source/App.o \
./src/source/GPIO.o \
./src/source/HLED.o \
./src/source/HLED_cfg.o \
./src/source/RCC.o \
./src/source/SCHED.o \
./src/source/SCHED_cfg.o \
./src/source/SYSTICK.o 

C_DEPS += \
./src/source/App.d \
./src/source/GPIO.d \
./src/source/HLED.d \
./src/source/HLED_cfg.d \
./src/source/RCC.d \
./src/source/SCHED.d \
./src/source/SCHED_cfg.d \
./src/source/SYSTICK.d 


# Each subdirectory must supply rules for building sources it contributes
src/source/%.o: ../src/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"D:\iti_9m_diploma\ARM_ITI\ARM_WorkSpace\Sched_Trial\src\include" -I"D:\iti_9m_diploma\ARM_ITI\ARM_WorkSpace\Sched_Trial\src\source" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


