################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
111_ADC_serial.lss \

FLASH_IMAGE += \
111_ADC_serial.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: 111_ADC_serial.elf secondary-outputs

# Tool invocations
111_ADC_serial.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,111_ADC_serial.map -uvfprintf -mmcu=atmega328p -o "111_ADC_serial.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

111_ADC_serial.lss: 111_ADC_serial.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 111_ADC_serial.elf  >"111_ADC_serial.lss"
	@echo 'Finished building: $@'
	@echo ' '

111_ADC_serial.hex: 111_ADC_serial.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 111_ADC_serial.elf  "111_ADC_serial.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 111_ADC_serial.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p 111_ADC_serial.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) 111_ADC_serial.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
