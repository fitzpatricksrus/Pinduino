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

//#define _DEBUG_
#ifdef _DEBUG_
#include <debug.h>
#endif

#define _FAST_READ_

#ifdef _FAST_READ_
static const byte firstDataPin = 0;
#else
static const byte firstDataPin = 2;
#endif
static const byte rowSelectPin = A1;
static const byte colSelectPin = A2;
static byte lastSelectedColumn = 0;

Max7221 matrix(SS);

void setup() {
#ifdef _DEBUG_
	Serial.begin(57600);
#endif
	pinMode(rowSelectPin, INPUT);
	pinMode(colSelectPin, INPUT);
	for (byte i = 0; i < 8; i++) {
		pinMode(firstDataPin + i, INPUT);
	}
	matrix.init();
}

static byte bitMask[] = { 1, 2, 4, 8, 16, 32, 64, 128 };
void loopY() {
	if (digitalRead(colSelectPin) == LOW) {
#ifdef _FAST_READ_
		byte value = ~PIND;
		for (int i = 0; i < 8; i++) {
			if (value & bitMask[i]) {
				lastSelectedColumn = i;
#ifdef _DEBUG_
				Serial << "col " << lastSelectedColumn << endl;
#endif
			}
		}

#else
		byte newColumn = lastSelectedColumn;
		for (int i = 0; i < 8; i++) {
			if (digitalRead(firstDataPin + i) == LOW) {
				newColumn = i;
			}
		}
		if (newColumn != lastSelectedColumn) {
			lastSelectedColumn = newColumn;
#ifdef _DEBUG_
			Serial << "col " << lastSelectedColumn << endl;
#endif
		}
#endif
	} else if (digitalRead(rowSelectPin) == LOW) {
#ifdef _FAST_READ_
		byte value = ~PIND;
#else
		byte value = 0;
		for (int i = 0; i < 8; i++) {
			value = value << 1;
			if (digitalRead(firstDataPin + i) == LOW) {
				value |= 1;
			}
		}
#endif
		matrix.setColumn(lastSelectedColumn, value);
#ifdef _DEBUG_
		Serial << lastSelectedColumn << " " << _BIN(value) << endl;
#endif
	}
}

void loop() {
	if (digitalRead(colSelectPin) == LOW) {
#ifdef _FAST_READ_
		byte value = ~PIND;
		for (int i = 0; i < 8; i++) {
			if (value & bitMask[i]) {
				lastSelectedColumn = i;
#ifdef _DEBUG_
				Serial << "col " << lastSelectedColumn << endl;
#endif
			}
		}

#else
		byte newColumn = lastSelectedColumn;
		for (int i = 0; i < 8; i++) {
			if (digitalRead(firstDataPin + i) == LOW) {
				newColumn = i;
			}
		}
		if (newColumn != lastSelectedColumn) {
			lastSelectedColumn = newColumn;
#ifdef _DEBUG_
			Serial << "col " << lastSelectedColumn << endl;
#endif
		}
#endif
	} else if (digitalRead(rowSelectPin) == LOW) {
#ifdef _FAST_READ_
		byte value = ~PIND;
#else
		byte value = 0;
		for (int i = 0; i < 8; i++) {
			value = value << 1;
			if (digitalRead(firstDataPin + i) == LOW) {
				value |= 1;
			}
		}
#endif
//		for (byte i = 0; i < 8; i++) {
//			matrix.setColumn(i, (i == lastSelectedColumn) ? value : 0);
//		}
		matrix.setColumn(lastSelectedColumn, value);
#ifdef _DEBUG_
		Serial << lastSelectedColumn << " " << _BIN(value) << endl;
#endif
	}
}

void loopX() {
#ifdef _FAST_READ_
		int data = ~PIND;
#else
		int data = 0;
		for (int i = 0; i < 8; i++) {
			data = data << 1;
			if (digitalRead(firstDataPin + i) == LOW) {
				data |= 1;
			}
		}
#endif
#ifdef _DEBUG_
	if (col == 0) {
		Serial << col << " " << row << " " << _BIN(data) << endl;
	}
#endif
	delay(100);
}
