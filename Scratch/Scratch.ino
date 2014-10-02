#include <Arduino.h>

static int ROW_PIN_NUMBERS[] = { 3,4, -1  };
static int COL_PIN_NUMBERS[] = { 5,6, -1 };


//-------------------------------------------------

void setup() {
   Serial.begin(115200);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   pinMode(6, OUTPUT);
}

// The loop function is called in an endless loop
void loop()
{
	digitalWrite(3, HIGH);
	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	delay(10);
	digitalWrite(3, LOW);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	delay(1000);
}
