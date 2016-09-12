################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Control/fl/imex/CppExporter.cpp \
../Control/fl/imex/Exporter.cpp \
../Control/fl/imex/FclExporter.cpp \
../Control/fl/imex/FclImporter.cpp \
../Control/fl/imex/FisExporter.cpp \
../Control/fl/imex/FisImporter.cpp \
../Control/fl/imex/FldExporter.cpp \
../Control/fl/imex/FllExporter.cpp \
../Control/fl/imex/FllImporter.cpp \
../Control/fl/imex/Importer.cpp \
../Control/fl/imex/JavaExporter.cpp 

OBJS += \
./Control/fl/imex/CppExporter.o \
./Control/fl/imex/Exporter.o \
./Control/fl/imex/FclExporter.o \
./Control/fl/imex/FclImporter.o \
./Control/fl/imex/FisExporter.o \
./Control/fl/imex/FisImporter.o \
./Control/fl/imex/FldExporter.o \
./Control/fl/imex/FllExporter.o \
./Control/fl/imex/FllImporter.o \
./Control/fl/imex/Importer.o \
./Control/fl/imex/JavaExporter.o 

CPP_DEPS += \
./Control/fl/imex/CppExporter.d \
./Control/fl/imex/Exporter.d \
./Control/fl/imex/FclExporter.d \
./Control/fl/imex/FclImporter.d \
./Control/fl/imex/FisExporter.d \
./Control/fl/imex/FisImporter.d \
./Control/fl/imex/FldExporter.d \
./Control/fl/imex/FllExporter.d \
./Control/fl/imex/FllImporter.d \
./Control/fl/imex/Importer.d \
./Control/fl/imex/JavaExporter.d 


# Each subdirectory must supply rules for building sources it contributes
Control/fl/imex/%.o: ../Control/fl/imex/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -I"C:\Users\Holguer\Documents\ARMFPGASOC2\Stericlinic\Control\fl" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


