#include "WPCHardware.h"

#include <Debug.h>

void setup()
{
	Serial.begin(57600);

	//set up passthrough
	WPCHardware::INSTANCE.attachController(&WPCHardware::PASSTHROUGH_CONTROLLER_INSTANCE);
}

static unsigned long t = 0;
static unsigned long count = 0;
void loop()
{
	count++;
	{
		char buf[256];
		if (DebugSerial::INSTANCE.getContents(buf) > 0) {
			Serial.print(buf);
		}

	}
	if (millis() - t > 1000) {
		for (byte i = 0; i < 9; i++) {
			Serial << WPCHardware::INSTANCE.counts[i] << "  ";
			WPCHardware::INSTANCE.counts[i] = 0;
		}
		Serial << "  " << count << endl;
		t = millis();
		count = 0;
	}
}
