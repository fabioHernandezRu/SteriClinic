################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/src/imex/CppExporter.cpp \
../Control/src/imex/Exporter.cpp \
../Control/src/imex/FclExporter.cpp \
../Control/src/imex/FclImporter.cpp \
../Control/src/imex/FisExporter.cpp \
../Control/src/imex/FisImporter.cpp \
../Control/src/imex/FldExporter.cpp \
../Control/src/imex/FllExporter.cpp \
../Control/src/imex/FllImporter.cpp \
../Control/src/imex/Importer.cpp \
../Control/src/imex/JavaExporter.cpp 

OBJS += \
./Control/src/imex/CppExporter.o \
./Control/src/imex/Exporter.o \
./Control/src/imex/FclExporter.o \
./Control/src/imex/FclImporter.o \
./Control/src/imex/FisExporter.o \
./Control/src/imex/FisImporter.o \
./Control/src/imex/FldExporter.o \
./Control/src/imex/FllExporter.o \
./Control/src/imex/FllImporter.o \
./Control/src/imex/Importer.o \
./Control/src/imex/JavaExporter.o 

CPP_DEPS += \
./Control/src/imex/CppExporter.d \
./Control/src/imex/Exporter.d \
./Control/src/imex/FclExporter.d \
./Control/src/imex/FclImporter.d \
./Control/src/imex/FisExporter.d \
./Control/src/imex/FisImporter.d \
./Control/src/imex/FldExporter.d \
./Control/src/imex/FllExporter.d \
./Control/src/imex/FllImporter.d \
./Control/src/imex/Importer.d \
./Control/src/imex/JavaExporter.d 


# Each subdirectory must supply rules for building sources it contributes
Control/src/imex/%.o: ../Control/src/imex/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


