################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/Console.cpp \
../Control/src/Engine.cpp \
../Control/src/Exception.cpp \
../Control/src/Operation.cpp \
../Control/src/fuzzylite.cpp 

OBJS += \
./Control/src/Console.o \
./Control/src/Engine.o \
./Control/src/Exception.o \
./Control/src/Operation.o \
./Control/src/fuzzylite.o 

CPP_DEPS += \
./Control/src/Console.d \
./Control/src/Engine.d \
./Control/src/Exception.d \
./Control/src/Operation.d \
./Control/src/fuzzylite.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/%.o: ../Control/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


