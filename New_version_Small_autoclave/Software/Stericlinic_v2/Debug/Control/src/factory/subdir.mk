################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/factory/CloningFactory.cpp \
../Control/src/factory/ConstructionFactory.cpp \
../Control/src/factory/DefuzzifierFactory.cpp \
../Control/src/factory/FactoryManager.cpp \
../Control/src/factory/FunctionFactory.cpp \
../Control/src/factory/HedgeFactory.cpp \
../Control/src/factory/SNormFactory.cpp \
../Control/src/factory/TNormFactory.cpp \
../Control/src/factory/TermFactory.cpp 

OBJS += \
./Control/src/factory/CloningFactory.o \
./Control/src/factory/ConstructionFactory.o \
./Control/src/factory/DefuzzifierFactory.o \
./Control/src/factory/FactoryManager.o \
./Control/src/factory/FunctionFactory.o \
./Control/src/factory/HedgeFactory.o \
./Control/src/factory/SNormFactory.o \
./Control/src/factory/TNormFactory.o \
./Control/src/factory/TermFactory.o 

CPP_DEPS += \
./Control/src/factory/CloningFactory.d \
./Control/src/factory/ConstructionFactory.d \
./Control/src/factory/DefuzzifierFactory.d \
./Control/src/factory/FactoryManager.d \
./Control/src/factory/FunctionFactory.d \
./Control/src/factory/HedgeFactory.d \
./Control/src/factory/SNormFactory.d \
./Control/src/factory/TNormFactory.d \
./Control/src/factory/TermFactory.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/factory/%.o: ../Control/src/factory/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


