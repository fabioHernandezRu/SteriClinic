################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/term/Accumulated.cpp \
../Control/src/term/Activated.cpp \
../Control/src/term/Bell.cpp \
../Control/src/term/Concave.cpp \
../Control/src/term/Constant.cpp \
../Control/src/term/Cosine.cpp \
../Control/src/term/Discrete.cpp \
../Control/src/term/Function.cpp \
../Control/src/term/Gaussian.cpp \
../Control/src/term/GaussianProduct.cpp \
../Control/src/term/Linear.cpp \
../Control/src/term/PiShape.cpp \
../Control/src/term/Ramp.cpp \
../Control/src/term/Rectangle.cpp \
../Control/src/term/SShape.cpp \
../Control/src/term/Sigmoid.cpp \
../Control/src/term/SigmoidDifference.cpp \
../Control/src/term/SigmoidProduct.cpp \
../Control/src/term/Spike.cpp \
../Control/src/term/Term.cpp \
../Control/src/term/Trapezoid.cpp \
../Control/src/term/Triangle.cpp \
../Control/src/term/ZShape.cpp 

OBJS += \
./Control/src/term/Accumulated.o \
./Control/src/term/Activated.o \
./Control/src/term/Bell.o \
./Control/src/term/Concave.o \
./Control/src/term/Constant.o \
./Control/src/term/Cosine.o \
./Control/src/term/Discrete.o \
./Control/src/term/Function.o \
./Control/src/term/Gaussian.o \
./Control/src/term/GaussianProduct.o \
./Control/src/term/Linear.o \
./Control/src/term/PiShape.o \
./Control/src/term/Ramp.o \
./Control/src/term/Rectangle.o \
./Control/src/term/SShape.o \
./Control/src/term/Sigmoid.o \
./Control/src/term/SigmoidDifference.o \
./Control/src/term/SigmoidProduct.o \
./Control/src/term/Spike.o \
./Control/src/term/Term.o \
./Control/src/term/Trapezoid.o \
./Control/src/term/Triangle.o \
./Control/src/term/ZShape.o 

CPP_DEPS += \
./Control/src/term/Accumulated.d \
./Control/src/term/Activated.d \
./Control/src/term/Bell.d \
./Control/src/term/Concave.d \
./Control/src/term/Constant.d \
./Control/src/term/Cosine.d \
./Control/src/term/Discrete.d \
./Control/src/term/Function.d \
./Control/src/term/Gaussian.d \
./Control/src/term/GaussianProduct.d \
./Control/src/term/Linear.d \
./Control/src/term/PiShape.d \
./Control/src/term/Ramp.d \
./Control/src/term/Rectangle.d \
./Control/src/term/SShape.d \
./Control/src/term/Sigmoid.d \
./Control/src/term/SigmoidDifference.d \
./Control/src/term/SigmoidProduct.d \
./Control/src/term/Spike.d \
./Control/src/term/Term.d \
./Control/src/term/Trapezoid.d \
./Control/src/term/Triangle.d \
./Control/src/term/ZShape.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/term/%.o: ../Control/src/term/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


