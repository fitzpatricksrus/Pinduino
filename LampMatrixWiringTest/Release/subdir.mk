################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../.ino.cpp 

INO_SRCS += \
../LampMatrixWiringTest.ino 

INO_DEPS += \
./LampMatrixWiringTest.ino.d 

CPP_DEPS += \
./.ino.cpp.d 

LINK_OBJ += \
./.ino.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

LampMatrixWiringTest.o: ../LampMatrixWiringTest.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


