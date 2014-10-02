################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
PDE_SRCS += \
../examples/FlashLed/FlashLed.pde 

PDE_DEPS += \
./examples/FlashLed/FlashLed.pde.d 


# Each subdirectory must supply rules for building sources it contributes
examples/FlashLed/FlashLed.o: ../examples/FlashLed/FlashLed.pde
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


