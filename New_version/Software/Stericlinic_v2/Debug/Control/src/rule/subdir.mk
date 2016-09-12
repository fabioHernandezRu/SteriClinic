################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/rule/Antecedent.cpp \
../Control/src/rule/Consequent.cpp \
../Control/src/rule/Expression.cpp \
../Control/src/rule/Rule.cpp \
../Control/src/rule/RuleBlock.cpp 

OBJS += \
./Control/src/rule/Antecedent.o \
./Control/src/rule/Consequent.o \
./Control/src/rule/Expression.o \
./Control/src/rule/Rule.o \
./Control/src/rule/RuleBlock.o 

CPP_DEPS += \
./Control/src/rule/Antecedent.d \
./Control/src/rule/Consequent.d \
./Control/src/rule/Expression.d \
./Control/src/rule/Rule.d \
./Control/src/rule/RuleBlock.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/rule/%.o: ../Control/src/rule/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


