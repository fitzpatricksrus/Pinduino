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
		SOL1,
		SOL2,
		SOL3,
		SOL4,
		LAMP_ROW,
		LAMP_COL,
		TRIAC,
		SWITCH_ROW,
		SWITCH_COL,
		SWITCH_DEDICATED,

		SIGNAL_COUNT
	};

	byte read(Signal signal);
	void write(Signal signal, byte value);

	static CowZoneHardware& INSTANCE;

private:
	void selectSignal(Signal signal);

	static const byte signalSelectorBit0Pin = 8;
	static const byte signalSelectorBit1Pin = 9;
	static const byte signalSelectorBit2Pin = 10;
	static const byte signalSelectorBit3Pin = 11;
	static const byte inputSelectorPin = 12;
	static const byte outputSelectorPin = 13;
	static const byte outputLatchPin = A0;
};

inline void CowZoneHardware::selectSignal(Signal signal) {
	int sig = signal;
	for (byte i = signalSelectorBit0Pin; i <= signalSelectorBit3Pin;i++) {
		digitalWrite(i, (sig & 0x01));
		sig = sig >> 1;
	}
}

inline byte CowZoneHardware::read(Signal signal) {
	DDRC = 0;								// controller pins as input
	selectSignal(signal);					// select the desired signal
	digitalWrite(inputSelectorPin, LOW);	// ensure we're in input mode
	return PINC;							// return databus value
}

inline void CowZoneHardware::write(Signal signal, byte value) {
	digitalWrite(inputSelectorPin, HIGH);	// turn off input
	selectSignal(signal);					// select the desired signal
	DDRC = -1;								// controller pins as output
	PORTC = value;							// write to the data bus
	digitalWrite(outputLatchPin, LOW);		// latch data onto output bus
	digitalWrite(outputLatchPin, HIGH);
	digitalWrite(outputSelectorPin, LOW);	// pulse the output signal
	digitalWrite(outputSelectorPin, HIGH);
}

#endif /* COWZONEHARDWARE_H_ */
