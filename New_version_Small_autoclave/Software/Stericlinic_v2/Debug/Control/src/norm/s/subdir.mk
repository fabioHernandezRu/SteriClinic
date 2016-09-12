################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/norm/s/AlgebraicSum.cpp \
../Control/src/norm/s/BoundedSum.cpp \
../Control/src/norm/s/DrasticSum.cpp \
../Control/src/norm/s/EinsteinSum.cpp \
../Control/src/norm/s/HamacherSum.cpp \
../Control/src/norm/s/Maximum.cpp \
../Control/src/norm/s/NilpotentMaximum.cpp \
../Control/src/norm/s/NormalizedSum.cpp 

OBJS += \
./Control/src/norm/s/AlgebraicSum.o \
./Control/src/norm/s/BoundedSum.o \
./Control/src/norm/s/DrasticSum.o \
./Control/src/norm/s/EinsteinSum.o \
./Control/src/norm/s/HamacherSum.o \
./Control/src/norm/s/Maximum.o \
./Control/src/norm/s/NilpotentMaximum.o \
./Control/src/norm/s/NormalizedSum.o 

CPP_DEPS += \
./Control/src/norm/s/AlgebraicSum.d \
./Control/src/norm/s/BoundedSum.d \
./Control/src/norm/s/DrasticSum.d \
./Control/src/norm/s/EinsteinSum.d \
./Control/src/norm/s/HamacherSum.d \
./Control/src/norm/s/Maximum.d \
./Control/src/norm/s/NilpotentMaximum.d \
./Control/src/norm/s/NormalizedSum.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/norm/s/%.o: ../Control/src/norm/s/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


