################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/rule/Antecedent.cpp \
../Control/fl/rule/Consequent.cpp \
../Control/fl/rule/Expression.cpp \
../Control/fl/rule/Rule.cpp \
../Control/fl/rule/RuleBlock.cpp 

OBJS += \
./Control/fl/rule/Antecedent.o \
./Control/fl/rule/Consequent.o \
./Control/fl/rule/Expression.o \
./Control/fl/rule/Rule.o \
./Control/fl/rule/RuleBlock.o 

CPP_DEPS += \
./Control/fl/rule/Antecedent.d \
./Control/fl/rule/Consequent.d \
./Control/fl/rule/Expression.d \
./Control/fl/rule/Rule.d \
./Control/fl/rule/RuleBlock.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/rule/%.o: ../Control/fl/rule/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


