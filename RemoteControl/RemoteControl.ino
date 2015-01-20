#include <Arduino.h>
#include <Stream.h>
#include "StringStream.h"
#include <SPI.h>

template<class T> inline Print &operator <<(Print &obj, T arg) {
	obj.print(arg);
	return obj;
}

static const int BUFFER_SIZE = 120;
char buffer[BUFFER_SIZE];
char* args[10];
StringStream input(buffer, 0);
bool spiStarted = false;

void setup() {
	Serial.begin(9600);
	Serial.setTimeout(30 * 1000);
}

void loop() {
	while (Serial.available() > 0) {
		input.setInput(buffer,
				Serial.readBytesUntil('\n', buffer, BUFFER_SIZE));
		while (input.available()) {
			input.skipSpaces();
			String cmd = input.readStringUntil(' ');
			if (cmd == "ping") {
				Serial << "pong" << "\n";
			} else if (cmd == "dw") {
				input.skipSpaces();
				long pin = input.parseInt();
				input.skipSpaces();
				long value = input.parseInt();
				digitalWrite(pin, value);
				Serial << "digitalWrite(" << pin << "," << value << ")" << "\n";
			} else if (cmd == "dr") {
				input.skipSpaces();
				long pin = input.parseInt();
				Serial << "digitalRead(" << pin << ") == " << digitalRead(pin)
						<< "\n";
			} else if (cmd == "aw") {
				input.skipSpaces();
				long pin = input.parseInt();
				input.skipSpaces();
				long value = input.parseInt();
				analogWrite(pin, value);
				Serial << "analogWrite(" << pin << "," << value << ")" << "\n";
			} else if (cmd == "ar") {

			} else if (cmd == "pm") {
				input.skipSpaces();
				long pin = input.parseInt();
				input.skipSpaces();
				String mode = input.readStringUntil(' ');
				pinMode(pin, mode == "output" ? OUTPUT : INPUT);
				Serial << "pinMode(" << pin << "," << mode << " - "
						<< (mode == "output" ? "OUTPUT)\n" : "INPUT)\n");
			} else if (cmd == "spi") {
				if (!spiStarted) {
					SPI.begin();
					spiStarted = true;
					Serial << "Starting SPI interface\n";
				}
				Serial << "SPI: ";
				while (input.available()) {
					input.skipSpaces();
					long value = input.parseInt();
					SPI.transfer(value);
					Serial << value << " ";
				}
				Serial << "\n";
			}
		}
	}
}
