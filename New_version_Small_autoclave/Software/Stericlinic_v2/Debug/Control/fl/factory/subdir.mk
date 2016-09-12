################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/factory/CloningFactory.cpp \
../Control/fl/factory/ConstructionFactory.cpp \
../Control/fl/factory/DefuzzifierFactory.cpp \
../Control/fl/factory/FactoryManager.cpp \
../Control/fl/factory/FunctionFactory.cpp \
../Control/fl/factory/HedgeFactory.cpp \
../Control/fl/factory/SNormFactory.cpp \
../Control/fl/factory/TNormFactory.cpp \
../Control/fl/factory/TermFactory.cpp 

OBJS += \
./Control/fl/factory/CloningFactory.o \
./Control/fl/factory/ConstructionFactory.o \
./Control/fl/factory/DefuzzifierFactory.o \
./Control/fl/factory/FactoryManager.o \
./Control/fl/factory/FunctionFactory.o \
./Control/fl/factory/HedgeFactory.o \
./Control/fl/factory/SNormFactory.o \
./Control/fl/factory/TNormFactory.o \
./Control/fl/factory/TermFactory.o 

CPP_DEPS += \
./Control/fl/factory/CloningFactory.d \
./Control/fl/factory/ConstructionFactory.d \
./Control/fl/factory/DefuzzifierFactory.d \
./Control/fl/factory/FactoryManager.d \
./Control/fl/factory/FunctionFactory.d \
./Control/fl/factory/HedgeFactory.d \
./Control/fl/factory/SNormFactory.d \
./Control/fl/factory/TNormFactory.d \
./Control/fl/factory/TermFactory.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/factory/%.o: ../Control/fl/factory/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


