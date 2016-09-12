################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include uart_fpga/subdir.mk
-include tasks/subdir.mk
-include rtc/subdir.mk
-include fpga_ports/subdir.mk
-include audio/subdir.mk
-include Valves/subdir.mk
-include Printer/subdir.mk
-include PWM/subdir.mk
-include Nextion/subdir.mk
-include Network/subdir.mk
-include MAX6675/subdir.mk
-include Interruptores/subdir.mk
-include DataLog/subdir.mk
-include Control/subdir.mk
-include ADC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Stericlinic_v2

# Tool invocations
Stericlinic_v2: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker 4 [arm-linux-gnueabihf]'
	arm-linux-gnueabihf-g++ -lm -lpthread -o "Stericlinic_v2" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS) $(C++_DEPS) $(C_DEPS) $(CC_DEPS) $(CPP_DEPS) $(EXECUTABLES) $(CXX_DEPS) $(C_UPPER_DEPS) Stericlinic_v2 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
