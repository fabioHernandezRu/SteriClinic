################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/norm/t/AlgebraicProduct.cpp \
../Control/src/norm/t/BoundedDifference.cpp \
../Control/src/norm/t/DrasticProduct.cpp \
../Control/src/norm/t/EinsteinProduct.cpp \
../Control/src/norm/t/HamacherProduct.cpp \
../Control/src/norm/t/Minimum.cpp \
../Control/src/norm/t/NilpotentMinimum.cpp 

OBJS += \
./Control/src/norm/t/AlgebraicProduct.o \
./Control/src/norm/t/BoundedDifference.o \
./Control/src/norm/t/DrasticProduct.o \
./Control/src/norm/t/EinsteinProduct.o \
./Control/src/norm/t/HamacherProduct.o \
./Control/src/norm/t/Minimum.o \
./Control/src/norm/t/NilpotentMinimum.o 

CPP_DEPS += \
./Control/src/norm/t/AlgebraicProduct.d \
./Control/src/norm/t/BoundedDifference.d \
./Control/src/norm/t/DrasticProduct.d \
./Control/src/norm/t/EinsteinProduct.d \
./Control/src/norm/t/HamacherProduct.d \
./Control/src/norm/t/Minimum.d \
./Control/src/norm/t/NilpotentMinimum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/norm/t/%.o: ../Control/src/norm/t/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


