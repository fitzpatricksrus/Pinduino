#include <Arduino.h>

static const byte EN_DATA_IN = 37;
static const byte CLK_DATA_IN = 36;
static const byte EN_DATA_OUT = 35;
static const byte CLK_DATA_OUT = 34;
static const byte OUT1 = 33;
static const byte OUT2 = 32;
static const byte OUT4 = 31;
static const byte EN_OUT = 30;

void setDataDirection(bool read) {
	if (read) {
		DDRL = 0;
		digitalWrite(EN_DATA_IN, LOW);
	} else {
		digitalWrite(EN_DATA_IN, HIGH);
		DDRL = -1;
	}
}



void setup() {
}

void loop() {
}
