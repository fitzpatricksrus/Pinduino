
/*
 * The hardware looks as follows:
 * 8 pins, 0 - 7, used for data bus I/O.  Since it's shared for input and output,
 * pin 8 is used to select the direction: LOW input, HIGH output.
 *
 * There are 7 I/O buses that the data signals can be send down: TRIAC, LAMP_COL,
 * LAMP_ROW, SOL1, SOL2, SOL3, SOL4.  These buses are selected through a 74XX138
 * 3 -> 8 decoder, pins 9 - 11.  This allows fully selectable input through 12 pins.
 *
 * One additional pin is used to sense the ZERO_CROSS signal (120Hz) in order to sync
 * TRIAC changes.  Pin 12.  This signal is read-only.
 *
 * Output is over the same 7 I/O buses, 0 - 7.  The output buses are selected through
 * the another 3 - 8 decoder through the same pins, 9 - 11, but pin 8 should signal
 * output instead of input.
 */

#include "CowZoneHardware.h"


static long lastPrint = 0;
static long count = 0;

static byte signalCache[CowZoneHardware::SIGNAL_COUNT];

void setup()
{
	for (byte i = 0; i < CowZoneHardware::SIGNAL_COUNT; i++) {
		signalCache[i] = 0;
	}
}

void loop()
{
	CowZoneHardware::INSTANCE.init();
	Serial.begin(57600);
	while (1) {
		for (byte i = CowZoneHardware::LAMP_ROW; i < CowZoneHardware::SOL1; i++) {
#if 1
			byte val = CowZoneHardware::INSTANCE.read((CowZoneHardware::Signal)i);
			if (val != signalCache[i]) {
				CowZoneHardware::INSTANCE.write((CowZoneHardware::Signal)i, val);
				signalCache[i] = val;
			}
#else
			CowZoneHardware::INSTANCE.write((CowZoneHardware::Signal)i,
					CowZoneHardware::INSTANCE.read((CowZoneHardware::Signal)i));
#endif
		}
		count++;
		if (millis() - lastPrint > 1000) {
			Serial.println(count);
			count = 0;
			lastPrint = millis();
		}
	}
}
