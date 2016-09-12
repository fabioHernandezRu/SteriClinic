################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/variable/InputVariable.cpp \
../Control/src/variable/OutputVariable.cpp \
../Control/src/variable/Variable.cpp 

OBJS += \
./Control/src/variable/InputVariable.o \
./Control/src/variable/OutputVariable.o \
./Control/src/variable/Variable.o 

CPP_DEPS += \
./Control/src/variable/InputVariable.d \
./Control/src/variable/OutputVariable.d \
./Control/src/variable/Variable.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/variable/%.o: ../Control/src/variable/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


