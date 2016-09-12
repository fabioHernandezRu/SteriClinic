################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/Console.cpp \
../Control/fl/Engine.cpp \
../Control/fl/Exception.cpp \
../Control/fl/Operation.cpp \
../Control/fl/fuzzylite.cpp 

OBJS += \
./Control/fl/Console.o \
./Control/fl/Engine.o \
./Control/fl/Exception.o \
./Control/fl/Operation.o \
./Control/fl/fuzzylite.o 

CPP_DEPS += \
./Control/fl/Console.d \
./Control/fl/Engine.d \
./Control/fl/Exception.d \
./Control/fl/Operation.d \
./Control/fl/fuzzylite.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/%.o: ../Control/fl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


