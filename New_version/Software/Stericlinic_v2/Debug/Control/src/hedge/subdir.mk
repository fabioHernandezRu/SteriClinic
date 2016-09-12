################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/hedge/Any.cpp \
../Control/src/hedge/Extremely.cpp \
../Control/src/hedge/Not.cpp \
../Control/src/hedge/Seldom.cpp \
../Control/src/hedge/Somewhat.cpp \
../Control/src/hedge/Very.cpp 

OBJS += \
./Control/src/hedge/Any.o \
./Control/src/hedge/Extremely.o \
./Control/src/hedge/Not.o \
./Control/src/hedge/Seldom.o \
./Control/src/hedge/Somewhat.o \
./Control/src/hedge/Very.o 

CPP_DEPS += \
./Control/src/hedge/Any.d \
./Control/src/hedge/Extremely.d \
./Control/src/hedge/Not.d \
./Control/src/hedge/Seldom.d \
./Control/src/hedge/Somewhat.d \
./Control/src/hedge/Very.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/hedge/%.o: ../Control/src/hedge/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


