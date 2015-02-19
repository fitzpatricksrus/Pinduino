//The setup function is called once at startup of the sketch

#include <Arduino.h>
//#include <Debug.h>

static const byte colInterruptPin = 20;	//int.2
static const byte rowInterruptPin = 21;	//int.3
static const byte colOutputLatch = 16;
static const byte rowOutputLatch = 17;
static const byte colOutputSelect = 14;
static const byte rowOutputSelect = 15;

// MPU -> 240 -> 374
// pin x goes high
// read data from chip
// disable output
// write data to outputs
// latch data into appropriate output
// set output enable on chip
// outputs -> 244 -> 374(2)

void handleChange(byte enablePin, byte latchPin) {
	digitalWrite(enablePin, HIGH);	//turn off col output
	PORTC = PINA;
	digitalWrite(latchPin, LOW);		//latch in data
	digitalWrite(latchPin, HIGH);
	digitalWrite(enablePin, LOW);		//turn col output on
}

void colsChanged() {
	handleChange(colOutputSelect, colOutputLatch);
}

void rowsChanged() {
	handleChange(rowOutputSelect, rowOutputLatch);
}

void setup()
{
	DDRA = 0b00000000;	//all input
	DDRC = 0b11111111;	//all output
	attachInterrupt(2, colsChanged, RISING);
	attachInterrupt(3, rowsChanged, RISING);
}

void loop()
{
}
