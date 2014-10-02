################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include examples/FlashLed/subdir.mk
-include arduino/core/avr-libc/subdir.mk
-include arduino/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/arduino.ar \

ELF += \
FlexiTimer2.elf \

EEP += \
FlexiTimer2.eep \

FLASH_IMAGE += \
FlexiTimer2.hex \


# All Target
all: FlexiTimer2

# Tool invocations
FlexiTimer2: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-size" -A "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-ar" rcs "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/arduino.ar"   $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

FlexiTimer2.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p -o "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.elf"   $(LINK_OBJ) $(AR)  "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/arduino.ar" "-L/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

FlexiTimer2.eep: $(ELF)
	@echo 'Create eeprom image'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.elf" "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.eep"
	@echo 'Finished building: $@'
	@echo ' '

FlexiTimer2.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-objcopy" -O ihex -R .eeprom "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.elf" "/Users/Dad/GoogleDrive/arduino/WorkspaceGit/FlexiTimer2/Release/FlexiTimer2.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(AR)$(C_DEPS)$(FLASH_IMAGE)$(EEP)$(CXX_DEPS)$(S_UPPER_DEPS)$(ELF)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(INO_DEPS)$(AR_OBJ)$(CPP_DEPS)$(PDE_DEPS)$(LINK_OBJ)$(C_UPPER_DEPS)$(SIZEDUMMY) FlexiTimer2
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
