################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/defuzzifier/Bisector.cpp \
../Control/src/defuzzifier/Centroid.cpp \
../Control/src/defuzzifier/IntegralDefuzzifier.cpp \
../Control/src/defuzzifier/LargestOfMaximum.cpp \
../Control/src/defuzzifier/MeanOfMaximum.cpp \
../Control/src/defuzzifier/SmallestOfMaximum.cpp \
../Control/src/defuzzifier/WeightedAverage.cpp \
../Control/src/defuzzifier/WeightedDefuzzifier.cpp \
../Control/src/defuzzifier/WeightedSum.cpp 

OBJS += \
./Control/src/defuzzifier/Bisector.o \
./Control/src/defuzzifier/Centroid.o \
./Control/src/defuzzifier/IntegralDefuzzifier.o \
./Control/src/defuzzifier/LargestOfMaximum.o \
./Control/src/defuzzifier/MeanOfMaximum.o \
./Control/src/defuzzifier/SmallestOfMaximum.o \
./Control/src/defuzzifier/WeightedAverage.o \
./Control/src/defuzzifier/WeightedDefuzzifier.o \
./Control/src/defuzzifier/WeightedSum.o 

CPP_DEPS += \
./Control/src/defuzzifier/Bisector.d \
./Control/src/defuzzifier/Centroid.d \
./Control/src/defuzzifier/IntegralDefuzzifier.d \
./Control/src/defuzzifier/LargestOfMaximum.d \
./Control/src/defuzzifier/MeanOfMaximum.d \
./Control/src/defuzzifier/SmallestOfMaximum.d \
./Control/src/defuzzifier/WeightedAverage.d \
./Control/src/defuzzifier/WeightedDefuzzifier.d \
./Control/src/defuzzifier/WeightedSum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/defuzzifier/%.o: ../Control/src/defuzzifier/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


