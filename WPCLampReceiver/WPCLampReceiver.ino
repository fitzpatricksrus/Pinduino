/*
 * The WPC lamp matrix is driven by a row select pin, a column select pin, and
 * a shared 8 bit data bus.  To turn a set of rows on, 8 bits of data is put on the
 * data bus, low signifying that the row should be ENABLED.  The row select pin is then
 * toggled from low to high to latch the data.  The setup for the columns is the same.
 * data is put on the data bus, low signifying the column is on, and the rising transition
 * on the column select pin latches the data.  The columns have a single master output
 * control (OC) line that turns the enables the output of puts them into a high impedance state.
 * When OC is low, the output are high impedance.
 */

#include <Arduino.h>

#include <Max7221.h>
#include <debug.h>

static const byte firstDataPin = 0;
static const byte rowSelectPin = A1;
static const byte colSelectPin = A2;
static const byte cs = 10;
static byte lastSelectedColumn = 0;

Max7221 matrix(cs);

void setup() {
//	Serial.begin(57600);
	pinMode(rowSelectPin, INPUT);
	pinMode(colSelectPin, INPUT);
	pinMode(0, INPUT);
	pinMode(1, INPUT);
	for (byte i = 0; i < 8; i++) {
		pinMode(firstDataPin + i, INPUT);
	}
	matrix.init();
}

void loop() {
	if (digitalRead(colSelectPin) == LOW) {
		for (int i = 0; i < 8; i++) {
			if (digitalRead(firstDataPin + i) == LOW) {
				lastSelectedColumn = i;
//				Serial << "col " << lastSelectedColumn << endl;
			}
		}
	} else if (digitalRead(rowSelectPin) == LOW) {
		byte value = 0;
		for (int i = 0; i < 8; i++) {
			if (digitalRead(firstDataPin + i) == LOW) {
				value |= (1 << i);
			}
		}
		matrix.setColumn(lastSelectedColumn, value);
//		Serial << lastSelectedColumn << " " << _BIN(value) << endl;
	}
}
