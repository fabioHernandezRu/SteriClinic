################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Interruptores/interruptores.cpp 

OBJS += \
./Interruptores/interruptores.o 

CPP_DEPS += \
./Interruptores/interruptores.d 


# Each subdirectory must supply rules for building sources it contributes
Interruptores/%.o: ../Interruptores/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -std=c++11 -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av\socal" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


