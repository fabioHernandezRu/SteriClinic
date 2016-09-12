################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/hedge/Any.cpp \
../Control/fl/hedge/Extremely.cpp \
../Control/fl/hedge/Not.cpp \
../Control/fl/hedge/Seldom.cpp \
../Control/fl/hedge/Somewhat.cpp \
../Control/fl/hedge/Very.cpp 

OBJS += \
./Control/fl/hedge/Any.o \
./Control/fl/hedge/Extremely.o \
./Control/fl/hedge/Not.o \
./Control/fl/hedge/Seldom.o \
./Control/fl/hedge/Somewhat.o \
./Control/fl/hedge/Very.o 

CPP_DEPS += \
./Control/fl/hedge/Any.d \
./Control/fl/hedge/Extremely.d \
./Control/fl/hedge/Not.d \
./Control/fl/hedge/Seldom.d \
./Control/fl/hedge/Somewhat.d \
./Control/fl/hedge/Very.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/hedge/%.o: ../Control/fl/hedge/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


