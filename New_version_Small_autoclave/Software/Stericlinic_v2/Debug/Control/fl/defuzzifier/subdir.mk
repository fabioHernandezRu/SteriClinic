################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/defuzzifier/Bisector.cpp \
../Control/fl/defuzzifier/Centroid.cpp \
../Control/fl/defuzzifier/IntegralDefuzzifier.cpp \
../Control/fl/defuzzifier/LargestOfMaximum.cpp \
../Control/fl/defuzzifier/MeanOfMaximum.cpp \
../Control/fl/defuzzifier/SmallestOfMaximum.cpp \
../Control/fl/defuzzifier/WeightedAverage.cpp \
../Control/fl/defuzzifier/WeightedDefuzzifier.cpp \
../Control/fl/defuzzifier/WeightedSum.cpp 

OBJS += \
./Control/fl/defuzzifier/Bisector.o \
./Control/fl/defuzzifier/Centroid.o \
./Control/fl/defuzzifier/IntegralDefuzzifier.o \
./Control/fl/defuzzifier/LargestOfMaximum.o \
./Control/fl/defuzzifier/MeanOfMaximum.o \
./Control/fl/defuzzifier/SmallestOfMaximum.o \
./Control/fl/defuzzifier/WeightedAverage.o \
./Control/fl/defuzzifier/WeightedDefuzzifier.o \
./Control/fl/defuzzifier/WeightedSum.o 

CPP_DEPS += \
./Control/fl/defuzzifier/Bisector.d \
./Control/fl/defuzzifier/Centroid.d \
./Control/fl/defuzzifier/IntegralDefuzzifier.d \
./Control/fl/defuzzifier/LargestOfMaximum.d \
./Control/fl/defuzzifier/MeanOfMaximum.d \
./Control/fl/defuzzifier/SmallestOfMaximum.d \
./Control/fl/defuzzifier/WeightedAverage.d \
./Control/fl/defuzzifier/WeightedDefuzzifier.d \
./Control/fl/defuzzifier/WeightedSum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/defuzzifier/%.o: ../Control/fl/defuzzifier/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


