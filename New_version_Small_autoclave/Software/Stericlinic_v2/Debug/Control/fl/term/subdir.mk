################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/term/Accumulated.cpp \
../Control/fl/term/Activated.cpp \
../Control/fl/term/Bell.cpp \
../Control/fl/term/Concave.cpp \
../Control/fl/term/Constant.cpp \
../Control/fl/term/Cosine.cpp \
../Control/fl/term/Discrete.cpp \
../Control/fl/term/Function.cpp \
../Control/fl/term/Gaussian.cpp \
../Control/fl/term/GaussianProduct.cpp \
../Control/fl/term/Linear.cpp \
../Control/fl/term/PiShape.cpp \
../Control/fl/term/Ramp.cpp \
../Control/fl/term/Rectangle.cpp \
../Control/fl/term/SShape.cpp \
../Control/fl/term/Sigmoid.cpp \
../Control/fl/term/SigmoidDifference.cpp \
../Control/fl/term/SigmoidProduct.cpp \
../Control/fl/term/Spike.cpp \
../Control/fl/term/Term.cpp \
../Control/fl/term/Trapezoid.cpp \
../Control/fl/term/Triangle.cpp \
../Control/fl/term/ZShape.cpp 

OBJS += \
./Control/fl/term/Accumulated.o \
./Control/fl/term/Activated.o \
./Control/fl/term/Bell.o \
./Control/fl/term/Concave.o \
./Control/fl/term/Constant.o \
./Control/fl/term/Cosine.o \
./Control/fl/term/Discrete.o \
./Control/fl/term/Function.o \
./Control/fl/term/Gaussian.o \
./Control/fl/term/GaussianProduct.o \
./Control/fl/term/Linear.o \
./Control/fl/term/PiShape.o \
./Control/fl/term/Ramp.o \
./Control/fl/term/Rectangle.o \
./Control/fl/term/SShape.o \
./Control/fl/term/Sigmoid.o \
./Control/fl/term/SigmoidDifference.o \
./Control/fl/term/SigmoidProduct.o \
./Control/fl/term/Spike.o \
./Control/fl/term/Term.o \
./Control/fl/term/Trapezoid.o \
./Control/fl/term/Triangle.o \
./Control/fl/term/ZShape.o 

CPP_DEPS += \
./Control/fl/term/Accumulated.d \
./Control/fl/term/Activated.d \
./Control/fl/term/Bell.d \
./Control/fl/term/Concave.d \
./Control/fl/term/Constant.d \
./Control/fl/term/Cosine.d \
./Control/fl/term/Discrete.d \
./Control/fl/term/Function.d \
./Control/fl/term/Gaussian.d \
./Control/fl/term/GaussianProduct.d \
./Control/fl/term/Linear.d \
./Control/fl/term/PiShape.d \
./Control/fl/term/Ramp.d \
./Control/fl/term/Rectangle.d \
./Control/fl/term/SShape.d \
./Control/fl/term/Sigmoid.d \
./Control/fl/term/SigmoidDifference.d \
./Control/fl/term/SigmoidProduct.d \
./Control/fl/term/Spike.d \
./Control/fl/term/Term.d \
./Control/fl/term/Trapezoid.d \
./Control/fl/term/Triangle.d \
./Control/fl/term/ZShape.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/term/%.o: ../Control/fl/term/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


