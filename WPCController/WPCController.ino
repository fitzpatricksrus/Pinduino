#include <Arduino.h>
#include <PinChangeInt.h>


// PORTC
static const byte ROW_OUT = 30;
static const byte COL_OUT = 31;
static const byte TRIAC_OUT = 32;
static const byte SOL1_OUT = 33;
static const byte SOL2_OUT = 34;
static const byte SOL3_OUT = 35;
static const byte SOL4_OUT = 36;
static const byte UNUSED = 37;

static const byte CLK_DATA_OUT = 38;
static const byte EN_DATA_OUT = 39;
static const byte CLK_DATA_IN = 40;
static const byte EN_DATA_IN = 41;

// INPUT
static const byte ROW_SEL_IN = 22;
static const byte COL_SEL_IN = 23;

#define toggle(pin) { digitalWrite(pin, LOW); digitalWrite(pin, HIGH); }

void setDataDirection(bool read) {
	if (read) {
		// arduino pins are in read mode
		DDRL = 0;
		// input latch output enabled
		digitalWrite(EN_DATA_IN, LOW);
	} else {
		// input latch output disabled
		digitalWrite(EN_DATA_IN, HIGH);
		// arduino pins are in write mode
		DDRL = -1;
	}
}

static void handleRowInterrupt() {
	// move data onto data bus from input latch
	toggle(CLK_DATA_IN);

	// clock data from data bus into output latch
	toggle(CLK_DATA_OUT);

	// set output selector signal to OUT1 only, and blip clients to read output data lines
	toggle(ROW_OUT);
}

static void handleColInterrupt() {
	// move data onto data bus from input latch
	toggle(CLK_DATA_IN);

	// clock data from data bus into output latch
	toggle(CLK_DATA_OUT);

	// set output selector signal to OUT1 only, and blip clients to read output data lines
	toggle(COL_OUT);
}


void setup() {
	// set control pins to OUTPUT mode
	for (byte i = ROW_OUT; i <= EN_DATA_IN; i++) {
		digitalWrite(i, HIGH);
		pinMode(i, OUTPUT);
	}

	// set trigger pins to input
	pinMode(ROW_SEL_IN, INPUT);
	pinMode(COL_SEL_IN, INPUT);

	// allow input data latch to write to data bus
	setDataDirection(true);

	//TODO you should write to the output latch to clear crud before you enable it.
	// allow output latch to write to output lines
	digitalWrite(EN_DATA_OUT, LOW);

	attachPinChangeInterrupt(ROW_SEL_IN,handleRowInterrupt,RISING);
	attachPinChangeInterrupt(COL_SEL_IN,handleColInterrupt,RISING);

}

void loop() {
}
