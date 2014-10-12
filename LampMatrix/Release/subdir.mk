################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../.ino.cpp \
../AnalogOutputPins.cpp \
../BAMOutputPins.cpp \
../DirectOutputPins.cpp \
../Matrix5by7.cpp \
../Matrix8x8.cpp \
../MatrixOoze.cpp \
../MatrixPattern.cpp \
../MatrixPins.cpp \
../OutputPins.cpp \
../SPI.cpp \
../SPIOutputPins.cpp \
../SimpleMatrixPattern.cpp 

INO_SRCS += \
../LampMatrix.ino 

INO_DEPS += \
./LampMatrix.ino.d 

CPP_DEPS += \
./.ino.cpp.d \
./AnalogOutputPins.cpp.d \
./BAMOutputPins.cpp.d \
./DirectOutputPins.cpp.d \
./Matrix5by7.cpp.d \
./Matrix8x8.cpp.d \
./MatrixOoze.cpp.d \
./MatrixPattern.cpp.d \
./MatrixPins.cpp.d \
./OutputPins.cpp.d \
./SPI.cpp.d \
./SPIOutputPins.cpp.d \
./SimpleMatrixPattern.cpp.d 

LINK_OBJ += \
./.ino.cpp.o \
./AnalogOutputPins.cpp.o \
./BAMOutputPins.cpp.o \
./DirectOutputPins.cpp.o \
./Matrix5by7.cpp.o \
./Matrix8x8.cpp.o \
./MatrixOoze.cpp.o \
./MatrixPattern.cpp.o \
./MatrixPins.cpp.o \
./OutputPins.cpp.o \
./SPI.cpp.o \
./SPIOutputPins.cpp.o \
./SimpleMatrixPattern.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
.ino.cpp.o: ../.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

AnalogOutputPins.cpp.o: ../AnalogOutputPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

BAMOutputPins.cpp.o: ../BAMOutputPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

DirectOutputPins.cpp.o: ../DirectOutputPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

LampMatrix.o: ../LampMatrix.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Matrix5by7.cpp.o: ../Matrix5by7.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

Matrix8x8.cpp.o: ../Matrix8x8.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

MatrixOoze.cpp.o: ../MatrixOoze.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

MatrixPattern.cpp.o: ../MatrixPattern.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

MatrixPins.cpp.o: ../MatrixPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

OutputPins.cpp.o: ../OutputPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

SPI.cpp.o: ../SPI.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

SPIOutputPins.cpp.o: ../SPIOutputPins.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

SimpleMatrixPattern.cpp.o: ../SimpleMatrixPattern.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/standard" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


