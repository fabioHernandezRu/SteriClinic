################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/norm/s/AlgebraicSum.cpp \
../Control/fl/norm/s/BoundedSum.cpp \
../Control/fl/norm/s/DrasticSum.cpp \
../Control/fl/norm/s/EinsteinSum.cpp \
../Control/fl/norm/s/HamacherSum.cpp \
../Control/fl/norm/s/Maximum.cpp \
../Control/fl/norm/s/NilpotentMaximum.cpp \
../Control/fl/norm/s/NormalizedSum.cpp 

OBJS += \
./Control/fl/norm/s/AlgebraicSum.o \
./Control/fl/norm/s/BoundedSum.o \
./Control/fl/norm/s/DrasticSum.o \
./Control/fl/norm/s/EinsteinSum.o \
./Control/fl/norm/s/HamacherSum.o \
./Control/fl/norm/s/Maximum.o \
./Control/fl/norm/s/NilpotentMaximum.o \
./Control/fl/norm/s/NormalizedSum.o 

CPP_DEPS += \
./Control/fl/norm/s/AlgebraicSum.d \
./Control/fl/norm/s/BoundedSum.d \
./Control/fl/norm/s/DrasticSum.d \
./Control/fl/norm/s/EinsteinSum.d \
./Control/fl/norm/s/HamacherSum.d \
./Control/fl/norm/s/Maximum.d \
./Control/fl/norm/s/NilpotentMaximum.d \
./Control/fl/norm/s/NormalizedSum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/norm/s/%.o: ../Control/fl/norm/s/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


