################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../uart_fpga/fifo_control.c \
../uart_fpga/uart.c 

OBJS += \
./uart_fpga/fifo_control.o \
./uart_fpga/uart.o 

C_DEPS += \
./uart_fpga/fifo_control.d \
./uart_fpga/uart.d 


# Each subdirectory must supply rules for building sources it contributes
uart_fpga/%.o: ../uart_fpga/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


