#include <Arduino.h>

static bool COL_1 = false;
#define NOT(x) ((x) ? false : true)
//#define NOT(x) ((x))
//The setup function is called once at startup of the sketch
void setup() {
	pinMode(2, INPUT);
	pinMode(3, INPUT);

	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);

	digitalWrite(4, COL_1);	//Columns active low
	digitalWrite(5, NOT(COL_1));

	Serial.begin(57600);
}

static unsigned long lastColLoop = 0;
static unsigned long lastDataDump = 0;
static unsigned long loopCount = 0;
void loop() {
	if (millis() - lastColLoop >= 20) {
		digitalWrite(4, COL_1);	//Columns active low
		digitalWrite(5, NOT(COL_1));
//		Serial.print("col> ");
//		Serial.print(COL_1);
//		Serial.print("  ");
//		Serial.println(NOT(COL_1));
		lastColLoop = millis();
		COL_1 = NOT(COL_1);
		loopCount++;
//		Serial.println(loopCount / 5);
	}
	if (millis() - lastDataDump > 1000) {
		Serial.println(loopCount);
		loopCount = 0;
		lastDataDump = millis();
	}
}
