/*
 * Arduino pins 0-7 are used for the data bus.  Connected to the data base are
 * several latched buffers (ex. 74x374) for input.  A single buffer is used
 * for output, also on the shared data bus.  For input, the signals select the
 * correct buffer to put data on the data bus.  For output, the signals pulse
 * the proper output signal, expecting proper data to be on the data bus.  The
 * input and output buses can not be active simultaneously.  Output signals
 * are selected using a 4->16 bit demux like 74x154.
 */

#ifndef COWZONEHARDWARE_H_
#define COWZONEHARDWARE_H_

#include <Arduino.h>

class CowZoneHardware {
public:
	CowZoneHardware();
	virtual ~CowZoneHardware();

	enum Signal {
		LAMP_ROW = 0,
		LAMP_COL = 1,
		SOL1 =     2,
		SOL2 =     3,
		SOL3 =     4,
		SOL4 =     5,
		TRIAC =    6,
		SWITCH_ROW = 7,
		SWITCH_COL = 8,
		SWITCH_DEDICATED = 9,

		SIGNAL_COUNT = 10
	};


	void init();

	byte read(Signal signal);
	void write(Signal signal, byte value);
	void selfTest();

	static CowZoneHardware& INSTANCE;

private:
	void selectSignal(Signal signal);

	static const byte firstDataPin = 22;
	static const byte lastDataPin = 29;
	static const byte firstOutputPin = 30;
	static const byte lastOutputPin = 53;

	static const byte signalSelectorBit0Pin = 40;
	static const byte signalSelectorBit1Pin = 42;
	static const byte signalSelectorBit2Pin = 44;
//	static const byte signalSelectorBit3Pin = 0;	// not in use

	static const byte inputEnablePin = 38;
	static const byte outputEnablePin = 36;
	static const byte outputLatchPin = 34;
};

inline void CowZoneHardware::init() {
	for (byte i = firstDataPin; i <= lastDataPin; i++) {
		pinMode(i, INPUT);
	}
	for (byte i = firstOutputPin; i <= lastOutputPin; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
}

inline void CowZoneHardware::selectSignal(Signal signal) {
	int sig = signal;
	for (byte i = signalSelectorBit0Pin; i <= signalSelectorBit2Pin; i++) {
		digitalWrite(i, (sig & 0x01) != 0);
		sig = sig >> 1;
	}
}

static inline void toggle(byte pin) {
	digitalWrite(pin, LOW);
//	delayMicroseconds(20);
	digitalWrite(pin, HIGH);
}

inline byte CowZoneHardware::read(Signal signal) {
	DDRA = 0;								// controller pins as input
	selectSignal(signal);					// select the desired signal
	digitalWrite(inputEnablePin, LOW);		// input owns the data bus
	byte result = PINA;						// return data bus value
	digitalWrite(inputEnablePin, HIGH);		// release the bus
	return result;
}

inline void CowZoneHardware::write(Signal signal, byte value) {
	// write output to the data bus
	DDRA = -1;
	PORTA = value;
	// latch the output data
	toggle(outputLatchPin);
	selectSignal(signal);
	toggle(outputEnablePin);
}

#endif /* COWZONEHARDWARE_H_ */
