#include <Arduino.h>
#include <PinChangeInt.h>

//#define JUST_ROW_COL_SIGNAL
#define DIRECT_DATA_PASSTHROUGH
//#define DIRECT_DATA_PASSTHROUGH2
//#define BUFFERED_DATA_PASSTHROUGH

// PORTC
static const byte ROW_OUT = 30;
static const byte COL_OUT = 31;
static const byte TRIAC_OUT = 32;
static const byte SOL1_OUT = 33;
static const byte SOL2_OUT = 34;
static const byte SOL3_OUT = 35;
static const byte SOL4_OUT = 36;
static const byte EN_ARDUINO_OUT = 37;

// control bus
static const byte CLK_DATA_OUT = 38;	//PD7
static const byte EN_DATA_OUT = 39;	//PG2
static const byte CLK_DATA_IN = 40;	//PG1
static const byte EN_DATA_IN = 41;	//PG0

// input identifier pulses
static const byte ROW_SEL_IN = A10;
static volatile bool rowSelectCount = 0;
static const byte COL_SEL_IN = A15;
static volatile bool colSelectCount = 0;


typedef enum DataBusMaster { MPU, MICRO_CONTROLLER } DataBusMaster;

static int dummy = 0;

static void delay() {
	for (int i = 0; i < 7; i++) {
		dummy += i;
	}
}

static inline void toggle(byte pin) {
	digitalWrite(pin, LOW);
//	delay();
	digitalWrite(pin, HIGH);
}

static inline void setDataBusMaster(byte master) {
	if (master == MPU) {
		// arduino pins are in read mode
		DDRL = 0;
		// input latch output to data bus
		digitalWrite(EN_ARDUINO_OUT, HIGH);
		digitalWrite(EN_DATA_IN, LOW);
	} else {
		// input latch in high impedance
		digitalWrite(EN_DATA_IN, HIGH);
		digitalWrite(EN_ARDUINO_OUT, LOW);
		// arduino pins are in write mode
		DDRL = -1;
	}
	delay();
}

static inline byte readDataBus() {
	// make sure we're set to read the data bus
	setDataBusMaster(MPU);
	
	// read all of port L
	return PINL;
}

static inline void writeDataBus(byte value) {
	// make sure everything is set to let controller write data bus
	setDataBusMaster(MICRO_CONTROLLER);
	
	// write the entire data bus port
	PORTL = value;
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
#endif


#ifdef DIRECT_DATA_PASSTHROUGH
static void handleRowInterrupt() {
	// move data onto data bus from input latch
//	latchImport();
	toggle(CLK_DATA_IN);
	
	// ensure MPU input is on the data bus
//	setDataBusMaster(MPU);

	// clock data from data bus into output latch
//	latchExport();
	toggle(CLK_DATA_OUT);

	// signal to external client that row data is in output latch
//	signalExport(ROW_OUT);
	toggle(ROW_OUT);
}

static void handleColInterrupt() {
	//	latchImport();
		toggle(CLK_DATA_IN);

		// ensure MPU input is on the data bus
	//	setDataBusMaster(MPU);

		// clock data from data bus into output latch
	//	latchExport();
		toggle(CLK_DATA_OUT);

		// signal to external client that row data is in output latch
	//	signalExport(ROW_OUT);
		toggle(COL_OUT);
}
#endif

#ifdef DIRECT_DATA_PASSTHROUGH2

static void handleInterrupt() {
	// move data onto data bus from input latch
	latchImport();

	// ensure MPU input is on the data bus
	setDataBusMaster(MPU);

	// read data on data bus
	byte data = readDataBus();

	// take control of bus
	setDataBusMaster(MICRO_CONTROLLER);

	// write the data just read
	writeDataBus(data);

	// clock data from data bus into output latch
	latchExport();

	// signal to external client that column data is in output latch
}

static void handleRowInterrupt() {
	handleInterrupt();

	// signal to external client that row data is in output latch
	signalExport(ROW_OUT);
}

static void handleColInterrupt() {
	handleInterrupt();

	// signal to external client that column data is in output latch
	signalExport(COL_OUT);
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


static byte pendingRows;		// the current row values
static byte matrixLamps[8];

static void handleRowInterrupt() {
	// move data onto data bus from input latch
	latchImport();
	setDataBusMaster(MPU);
	// stash the row of data somewhere until a column is turned on.
	// this works because rows are only updated when all columns
	// are off on WPC.
	pendingRows = readDataBus();
}

static void handleColInterrupt() {
	// move data onto data bus from input latch
	latchImport();
	setDataBusMaster(MPU);
	byte column = readDataBus();
	for (byte i = 0; i < 8; i++) {
		if (column & 1) {
			matrixLamps[i] = pendingRows;
			return;
		} else {
			column = column >> 1;
		}
	}
}

#endif

void setup() {
	// set control pins to OUTPUT mode
	for (byte i = ROW_OUT; i <= EN_DATA_IN; i++) {
		digitalWrite(i, HIGH);
		pinMode(i, OUTPUT);
	}
	for (byte i = 42; i <= 49; i++) {
		pinMode(i, INPUT);
	}

	// set trigger pins to input
	pinMode(ROW_SEL_IN, INPUT);
	pinMode(COL_SEL_IN, INPUT);

	// allow input data latch to write to data bus
	setDataBusMaster(MPU);

	//TODO you should write to the output latch to clear crud before you enable it.
	// allow output latch to write to output lines
	digitalWrite(EN_DATA_OUT, LOW);

	attachPinChangeInterrupt(ROW_SEL_IN,handleRowInterrupt,RISING);
	attachPinChangeInterrupt(COL_SEL_IN,handleColInterrupt,RISING);

	Serial.begin(57600);
}

void loop() {
	if (rowSelectCount) {
		Serial.println("row");
		rowSelectCount = false;
	}
	if (colSelectCount) {
		Serial.println("col");
		colSelectCount = false;
	}
}
