#include <Arduino.h>

//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(2, INPUT);
	pinMode(3, INPUT);
	pinMode(4, INPUT);
	pinMode(5, INPUT);

	pinMode(10, INPUT_PULLUP);
	pinMode(11, INPUT_PULLUP);
	pinMode(12, INPUT_PULLUP);
	pinMode(13, INPUT_PULLUP);

	Serial.begin(57600);
}

/*
 * row 1 - 2
 * row 2 - 3
 * col 1 - 4
 * col 2 - 5
 */

#define bitValue(x, y) ((x & (1<<y)) ? 1 : 0)

static int switches[2][2];
static unsigned long lastLoop = 0;
static unsigned long lastLoop2 = 0;
void loop()
{
#if 0
	if (millis() - lastLoop > 200) {
		int p10 = digitalRead(10);
		int p11 = digitalRead(11);
		int p12 = digitalRead(12);
		int p13 = digitalRead(13);
		Serial.print("row(");
		Serial.print(p10);
		Serial.print("  ");
		Serial.print(p11);
		Serial.print(") col(");
		Serial.print(p12);
		Serial.print("  ");
		Serial.print(p13);
		Serial.print(")    ");

		switches[p12][0] = p10;
		switches[p12][1] = p11;

		Serial.print("(");
		Serial.print(switches[0][0]);
		Serial.print("  ");
		Serial.print(switches[0][1]);
		Serial.print(") (");
		Serial.print(switches[1][0]);
		Serial.print("  ");
		Serial.print(switches[1][1]);
		Serial.println(")");
		lastLoop = millis();
	}
#else
	if (millis() - lastLoop > 10) {
		int p10 = digitalRead(10);
		int p11 = digitalRead(11);
		int p12 = digitalRead(12);
		int p13 = digitalRead(13);
		switches[p12][0] = p10;
		switches[p12][1] = p11;
		lastLoop = millis();
	}

	if (millis() - lastLoop2 > 200) {
		Serial.print("(");
		Serial.print(switches[0][0]);
		Serial.print("  ");
		Serial.print(switches[0][1]);
		Serial.print(") (");
		Serial.print(switches[1][0]);
		Serial.print("  ");
		Serial.print(switches[1][1]);
		Serial.println(")");
		lastLoop2 = millis();
	}
#endif
}
