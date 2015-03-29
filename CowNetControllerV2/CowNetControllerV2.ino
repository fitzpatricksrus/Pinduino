
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


//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	CowZoneHardware::INSTANCE.init();

#if 0
	while (1) {
		for (byte col = 0; col < 8; col++) {
			CowZoneHardware::INSTANCE.write(CowZoneHardware::LAMP_COL, ~(1 << col));
			for (byte row = 0; row < 8; row++) {
				CowZoneHardware::INSTANCE.write(CowZoneHardware::LAMP_ROW, ~(1 << row));
//				delay(1);
				CowZoneHardware::INSTANCE.read((CowZoneHardware::Signal)CowZoneHardware::LAMP_ROW);
			}
		}
	}
#endif
}

// The loop function is called repeatedly.  Each iteration copies all the buses.
void loop()
{
	for (byte i = CowZoneHardware::LAMP_ROW; i < CowZoneHardware::SOL1; i++) {
//		CowZoneHardware::INSTANCE.read((CowZoneHardware::Signal)i);

		CowZoneHardware::INSTANCE.write(
				(CowZoneHardware::Signal)i,
				CowZoneHardware::INSTANCE.read((CowZoneHardware::Signal)i));
	}
//	delayMicroseconds(25);
}
