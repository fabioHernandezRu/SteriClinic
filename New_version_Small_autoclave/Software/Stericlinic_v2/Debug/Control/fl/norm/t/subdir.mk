################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/norm/t/AlgebraicProduct.cpp \
../Control/fl/norm/t/BoundedDifference.cpp \
../Control/fl/norm/t/DrasticProduct.cpp \
../Control/fl/norm/t/EinsteinProduct.cpp \
../Control/fl/norm/t/HamacherProduct.cpp \
../Control/fl/norm/t/Minimum.cpp \
../Control/fl/norm/t/NilpotentMinimum.cpp 

OBJS += \
./Control/fl/norm/t/AlgebraicProduct.o \
./Control/fl/norm/t/BoundedDifference.o \
./Control/fl/norm/t/DrasticProduct.o \
./Control/fl/norm/t/EinsteinProduct.o \
./Control/fl/norm/t/HamacherProduct.o \
./Control/fl/norm/t/Minimum.o \
./Control/fl/norm/t/NilpotentMinimum.o 

CPP_DEPS += \
./Control/fl/norm/t/AlgebraicProduct.d \
./Control/fl/norm/t/BoundedDifference.d \
./Control/fl/norm/t/DrasticProduct.d \
./Control/fl/norm/t/EinsteinProduct.d \
./Control/fl/norm/t/HamacherProduct.d \
./Control/fl/norm/t/Minimum.d \
./Control/fl/norm/t/NilpotentMinimum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/norm/t/%.o: ../Control/fl/norm/t/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


