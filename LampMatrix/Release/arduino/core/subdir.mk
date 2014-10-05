################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/CDC.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/HID.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/HardwareSerial.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/IPAddress.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Print.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Stream.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Tone.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/USBCore.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WMath.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WString.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/main.cpp \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/new.cpp 

C_SRCS += \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WInterrupts.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/hooks.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_analog.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_digital.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_pulse.c \
/Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_shift.c 

C_DEPS += \
./arduino/WInterrupts.c.d \
./arduino/hooks.c.d \
./arduino/wiring.c.d \
./arduino/wiring_analog.c.d \
./arduino/wiring_digital.c.d \
./arduino/wiring_pulse.c.d \
./arduino/wiring_shift.c.d 

AR_OBJ += \
./arduino/CDC.cpp.o \
./arduino/HID.cpp.o \
./arduino/HardwareSerial.cpp.o \
./arduino/IPAddress.cpp.o \
./arduino/Print.cpp.o \
./arduino/Stream.cpp.o \
./arduino/Tone.cpp.o \
./arduino/USBCore.cpp.o \
./arduino/WInterrupts.c.o \
./arduino/WMath.cpp.o \
./arduino/WString.cpp.o \
./arduino/hooks.c.o \
./arduino/main.cpp.o \
./arduino/new.cpp.o \
./arduino/wiring.c.o \
./arduino/wiring_analog.c.o \
./arduino/wiring_digital.c.o \
./arduino/wiring_pulse.c.o \
./arduino/wiring_shift.c.o 

CPP_DEPS += \
./arduino/CDC.cpp.d \
./arduino/HID.cpp.d \
./arduino/HardwareSerial.cpp.d \
./arduino/IPAddress.cpp.d \
./arduino/Print.cpp.d \
./arduino/Stream.cpp.d \
./arduino/Tone.cpp.d \
./arduino/USBCore.cpp.d \
./arduino/WMath.cpp.d \
./arduino/WString.cpp.d \
./arduino/main.cpp.d \
./arduino/new.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
arduino/CDC.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/CDC.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/HID.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/HID.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/HardwareSerial.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/HardwareSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/IPAddress.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/IPAddress.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/Print.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Print.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/Stream.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Stream.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/Tone.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/Tone.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/USBCore.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/USBCore.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/WInterrupts.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WInterrupts.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/WMath.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WMath.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/WString.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/WString.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/hooks.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/hooks.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/main.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/main.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/new.cpp.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/new.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -O3 -fno-exceptions -ffunction-sections -fdata-sections -MMD -finline-functions -fgcse -fexpensive-optimizations -fstrict-aliasing -funroll-loops -frerun-loop-opt -frerun-cse-after-loop -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_analog.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_analog.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_digital.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_digital.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_pulse.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_pulse.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/wiring_shift.c.o: /Users/Dad/GoogleDrive/arduino/Arduino\ 1.5.5.app/Contents/Resources/Java/hardware/arduino\ (1)/avr/cores/arduino/wiring_shift.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-gcc" -c -g -O3 -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=155 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR    -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/cores/arduino" -I"/Users/Dad/GoogleDrive/arduino/Arduino 1.5.5.app/Contents/Resources/Java/hardware/arduino (1)/avr/variants/mega" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


