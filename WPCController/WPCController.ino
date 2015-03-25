#include <Arduino.h>
#include <PinChangeInt.h>
#include <Debug.h>

//#define JUST_ROW_COL_SIGNAL
//#define DIRECT_DATA_PASSTHROUGH
#define DIRECT_DATA_PASSTHROUGH2
//#define DIRECT_DRIVE
//#define ASYNC_DATA_PASSTHROUGH
//#define BUFFERED_DATA_PASSTHROUGH

// PORTC
static const byte COL_OUT = 50; //22;
static const byte ROW_OUT = 51; //31;
static const byte TRIAC_OUT = 32;
static const byte SOL1_OUT = 33;
static const byte SOL2_OUT = 34;
static const byte SOL3_OUT = 35;
static const byte SOL4_OUT = 36;
static const byte EN_ARDUINO_OUT = 37;

// control bus
static const byte CLK_DATA_OUT = 38;	//PORTC 37..30
static const byte CLK_DATA_IN = 40;		//PORTL 49..42

// input identifier pulses
static const byte ROW_SEL_IN = A15;
static volatile long rowSelectCount = 0;
static const byte COL_SEL_IN = A14;
static volatile long colSelectCount = 0;
static volatile long matrixUpdateCount = 0;

static volatile long dummy = 0;
static inline void delay() {
/*	for (int i = 0; i < 2; i++) {
		dummy = i << i;
	} */
}

static inline void toggle(byte pin) {
	digitalWrite(pin, LOW);
//	delay();
	digitalWrite(pin, HIGH);
}

static inline byte readDataBus() {
	// read all of port L
	return PINL;
}

static inline void writeDataBus(byte value) {
	// write the entire data bus port
	PORTC = value;
}

static inline void latchImport() {
	// move data from client to input latch
	toggle(CLK_DATA_IN);
}

static inline void latchExport() {
	// move data from data bus to output latch
	toggle(CLK_DATA_OUT);
}

static inline void signalExport(byte pin) {
	toggle(pin);
}

#ifdef JUST_ROW_COL_SIGNAL
static void handleRowInterrupt() {
	// signal to external client that row data is in output latch
	signalExport(ROW_OUT);
}

static void handleColInterrupt() {
	signalExport(COL_OUT);
}

static inline void updateMatrix() {
	matrixUpdateCount++;
}

#endif

#ifdef DIRECT_DATA_PASSTHROUGH2

static inline byte handleInterrupt() {
	// move data onto data bus from input latch
	latchImport();

	// read data on data bus
	byte data = readDataBus();

	// write the data just read
	writeDataBus(data);

	// clock data from data bus into output latch
	latchExport();

	return data;
}

static char printVal2[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

static void handleRowInterrupt() {
	byte data = handleInterrupt();

	// signal to external client that row data is in output latch
	signalExport(ROW_OUT);
	rowSelectCount++;
//	DebugSerial::INSTANCE << "R ";
//	data = ~data;
//	DebugSerial::INSTANCE << printVal2[ (data>>4) & 0x0F];
//	DebugSerial::INSTANCE << printVal2[ data & 0x0F];
//	DebugSerial::INSTANCE << endl;
}

static void handleColInterrupt() {
	byte data = handleInterrupt();

	// signal to external client that column data is in output latch
	signalExport(COL_OUT);
	colSelectCount++;
//	DebugSerial::INSTANCE << "COL ";
//	data = ~data;
//	DebugSerial::INSTANCE << printVal2[ (data>>4) & 0x0F];
//	DebugSerial::INSTANCE << printVal2[ data & 0x0F];
//	DebugSerial::INSTANCE << endl;
}

static inline void updateMatrix() {
	matrixUpdateCount++;
}
#endif

#ifdef ASYNC_DATA_PASSTHROUGH

/*
 * this version moves a lot of the processing out of the interrupt service routine and essentially
 * queues it for consumption outside that routine.
 */

#include "CircularBuffer.h"
static const byte bufferSize = 50;
static int bufferStorage[bufferSize];
static volatile CircularBuffer<int> buffer(bufferStorage, bufferSize);
// the buffer values are of the form [byte col, byte row].  If the high byte
// is 0xFF then the buffer is empty.

static byte currentInputColumn = 0;
static void handleColInterrupt() {
	// move data onto data bus from input latch
	latchImport();

	// read data on data bus
	currentInputColumn = readDataBus();

	colSelectCount++;
}

static void handleRowInterrupt() {
	// move data onto data bus from input latch
	latchImport();

	// read data on data bus and push it into the buffer
	buffer.push(word(currentInputColumn, readDataBus()));

	rowSelectCount++;
}

static inline void updateMatrix() {
	while (buffer.isNotEmpty()) {
		int value = buffer.pop();
		byte col = highByte(value);
		byte row = lowByte(value);

		if (col == 0) {
			writeDataBus(col);
			signalExport(COL_OUT);
			writeDataBus(row);
			signalExport(ROW_OUT);
		} else {
			writeDataBus(row);
			signalExport(ROW_OUT);
			writeDataBus(col);
			signalExport(COL_OUT);
		}
	}


	matrixUpdateCount++;
}
#endif


#ifdef DIRECT_DRIVE

static byte matrixLamps[] = {
		0b01111110,
		0b10111101,
		0b11011011,
		0b11100111,
		0b11100111,
		0b11011011,
		0b10111101,
		0b01010101
};

static byte currentColumn = -1;

static void handleRowInterrupt() {
	rowSelectCount++;
}

static void handleColInterrupt() {
	colSelectCount++;
}

static inline void updateMatrix() {
	matrixUpdateCount++;

	// turn all (current) columns off
	writeDataBus(-1);
	latchExport();
	signalExport(COL_OUT);

	// update the rows for new column
	writeDataBus(matrixLamps[currentColumn]);
	latchExport();
	signalExport(ROW_OUT);

	// turn on new column
	writeDataBus(~(1 << currentColumn));
	latchExport();
	signalExport(COL_OUT);

    currentColumn = (currentColumn + 1) % 8;
}

#endif

#ifdef BUFFERED_DATA_PASSTHROUGH
/*
The scan makes buffering a little unobvious.  A WPC lamp refresh first turns off
all columns, then turns off all rows, waits 30ns, turns on a bunch of rows, and
then turns on a single column.  It is only at this point that something is
actually displayed.  So, we only refresh a row after a column is turned ON, 
meaning we want to buffer the last sent set of row values until the column
comes high.
*/


static byte pendingRowBits;
static bool pendingRows = false;

static byte matrixLamps[8] = { 0,0,0,0,0,0,0,0 };
static byte currentColBit = 0;

static byte bitToIndex(byte bit) {
	for (byte i = 0; i < 8; i++) {
		if (bit & 1) {
			return i;
		} else {
			bit = bit >> 1;
		}
	}
	return 0;
/*
	switch (bit) {
	case 0b00000001:
		return 0;
	case 0b00000010:
		return 1;
	case 0b00000100:
		return 2;
	case 0b00001000:
		return 3;
	case 0b00010000:
		return 4;
	case 0b00100000:
		return 5;
	case 0b01000000:
		return 6;
	case 0b10000000:
		return 7;
	default:
		return -1;
	} */
}

static void handleRowInterrupt() {
	// move data onto data bus from input latch
	rowSelectCount++;
	latchImport();
	if (currentColBit == 0) {
		// all the columns are off, so we don't know where this
		// row will eventually go.  Stash it somewhere until
		// a column gets turned on.
		pendingRowBits = readDataBus();
		pendingRows = true;
	} else {
		matrixLamps[bitToIndex(currentColBit)] = readDataBus();
		pendingRows = false;	//if there were pending updates, we just stomped on them.
	}
}

static void handleColInterrupt() {
	// move data onto data bus from input latch
	colSelectCount++;
	latchImport();
	currentColBit = readDataBus();
	byte currentColNdx = bitToIndex(currentColBit);

	if (pendingRows) {
		matrixLamps[currentColNdx] = pendingRowBits;
		pendingRows = false;
	}
}

static byte currentRefreshCol = 0;
static inline void updateMatrix() {

	writeDataBus(-1);
	latchExport();
	signalExport(COL_OUT);

	writeDataBus(matrixLamps[currentRefreshCol]);
	latchExport();
	signalExport(ROW_OUT);

	writeDataBus(1 << currentRefreshCol);
	latchExport();
	signalExport(COL_OUT);

	currentRefreshCol = (currentRefreshCol + 1) % 8;
	matrixUpdateCount++;
//	delay(2);
}

#endif



void setup() {
	// set control pins to OUTPUT mode
	for (byte i = 22; i <= 53; i++) {
		digitalWrite(i, HIGH);
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	for (byte i = 42; i <= 49; i++) {
		pinMode(i, INPUT);
	}

	// set trigger pins to input
	pinMode(ROW_SEL_IN, INPUT);
	pinMode(COL_SEL_IN, INPUT);

	DDRL = 0; // data INPUT
	DDRC = -1; // data OUTPUT

	attachPinChangeInterrupt(ROW_SEL_IN,handleRowInterrupt,RISING);
	attachPinChangeInterrupt(COL_SEL_IN,handleColInterrupt,RISING);

	Serial.begin(57600);
}

static long t = 0;
void loop() {
	updateMatrix();
	{
		char buf[256];
		if (DebugSerial::INSTANCE.getContents(buf) > 0) {
			Serial.print(buf);
		}

	}

	if (millis() - t > 1000) {
		Serial.print(rowSelectCount);
		Serial.print(", ");
		Serial.print(colSelectCount);
		Serial.print(", ");
		Serial.println(matrixUpdateCount);
		t = millis();
		rowSelectCount = 0;
		colSelectCount = 0;
		matrixUpdateCount = 0;

#ifdef BUFFERED_DATA_PASSTHROUGH
		for (byte i = 0; i < 8; i++) {
			Serial << _BIN(matrixLamps[i]) << ", ";
		}
		Serial << endl;
#endif
#ifdef DIRECT_DRIVE
		for (byte i = 0; i < 8; i++) {
			Serial << _BIN(matrixLamps[i]) << ", ";
		}
		Serial << endl;
#endif
	}
}
