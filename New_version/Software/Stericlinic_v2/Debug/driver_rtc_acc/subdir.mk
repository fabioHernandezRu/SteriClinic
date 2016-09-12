################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver_rtc_acc/I2C_core.c \
../driver_rtc_acc/rtc_driver.c 

OBJS += \
./driver_rtc_acc/I2C_core.o \
./driver_rtc_acc/rtc_driver.o 

C_DEPS += \
./driver_rtc_acc/I2C_core.d \
./driver_rtc_acc/rtc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
driver_rtc_acc/%.o: ../driver_rtc_acc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


