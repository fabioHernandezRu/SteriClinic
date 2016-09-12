################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/variable/InputVariable.cpp \
../Control/fl/variable/OutputVariable.cpp \
../Control/fl/variable/Variable.cpp 

OBJS += \
./Control/fl/variable/InputVariable.o \
./Control/fl/variable/OutputVariable.o \
./Control/fl/variable/Variable.o 

CPP_DEPS += \
./Control/fl/variable/InputVariable.d \
./Control/fl/variable/OutputVariable.d \
./Control/fl/variable/Variable.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/variable/%.o: ../Control/fl/variable/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


