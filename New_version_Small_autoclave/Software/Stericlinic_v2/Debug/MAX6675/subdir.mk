################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MAX6675/max6675.cpp 

OBJS += \
./MAX6675/max6675.o 

CPP_DEPS += \
./MAX6675/max6675.d 


# Each subdirectory must supply rules for building sources it contributes
MAX6675/%.o: ../MAX6675/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -std=c++11 -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av" -I"C:\altera\15.0\embedded\ip\altera\hps\altera_hps\hwlib\include\soc_cv_av\socal" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


