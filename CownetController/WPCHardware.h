/*
 * Hardware.h
 */

#ifndef WPCHARDWARE_H_
#define WPCHARDWARE_H_

#include <Arduino.h>

class WPCHardware {
public:
	WPCHardware();
	virtual ~WPCHardware();

	typedef enum WPCHardwareSignal { 
		COL,
		ROW,
		TRIAC,
		SOL1,
		SOL2,
		SOL3,
		SOL4,
		ZERO_CROSS,
		BLANKING,
		D0,
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		LATCH_IN,
		LATCH_OUT,
		
		SIGNAL_COUNT
	} WPCHardwareSignal;

	// ------------------------------------------------------------------------------
	// default controller does nothing.
	class WPCController {
	public:
		WPCController();
		virtual ~WPCController();
		virtual void handleRowInterrupt(WPCHardware& hardware);
		virtual void handleColInterrupt(WPCHardware& hardware);
		virtual void handleTriacInterrupt(WPCHardware& hardware);
		virtual void handleSol1Interrupt(WPCHardware& hardware);
		virtual void handleSol2Interrupt(WPCHardware& hardware);
		virtual void handleSol3Interrupt(WPCHardware& hardware);
		virtual void handleSol4Interrupt(WPCHardware& hardware);
		virtual void handleZeroCrossInterrupt(WPCHardware& hardware);
	};

	// ------------------------------------------------------------------------------
	// The passthrough controller copies data from input to output and propagates
	// the signal pulse to the output bus.
	class WPCPassthroughController : public WPCController {
	public:
		WPCPassthroughController();
		virtual ~WPCPassthroughController();
		virtual void handleRowInterrupt(WPCHardware& hardware);
		virtual void handleColInterrupt(WPCHardware& hardware);
		virtual void handleTriacInterrupt(WPCHardware& hardware);
		virtual void handleSol1Interrupt(WPCHardware& hardware);
		virtual void handleSol2Interrupt(WPCHardware& hardware);
		virtual void handleSol3Interrupt(WPCHardware& hardware);
		virtual void handleSol4Interrupt(WPCHardware& hardware);
		virtual void handleZeroCrossInterrupt(WPCHardware& hardware);
	};

	// ------------------------------------------------------------------------------
	// Hardware methods
	void attachController(WPCController* controller);
	WPCController* getController() const;

	void latchDataInput();
	void latchDataOutput();
	byte readData(bool autoLatch = true);
	void writeData(byte data, bool autoLatch = true);
	void pulse(WPCHardwareSignal pin) ;
	bool getBlanking() const;
	bool readPin(WPCHardwareSignal pin);
	void writePin(WPCHardwareSignal pin, bool high);

	long counts[SIGNAL_COUNT+1];

	static WPCHardware& INSTANCE;
	static WPCController& PASSTHROUGH_CONTROLLER_INSTANCE;

	static const byte INVALID_PIN = 255;

private:
	void pulsePin(byte pin);
	WPCController* controller;
	byte* inputPins;
	byte* outputPins;
};

inline void WPCHardware::latchDataInput() {
	pulse(LATCH_IN);
}
inline void WPCHardware::latchDataOutput() {
	pulse(LATCH_OUT);
}
inline byte WPCHardware::readData(bool autoLatch) {
	if (autoLatch) latchDataInput();
	return PINL;
}
inline void WPCHardware::writeData(byte data, bool autoLatch) {
	PORTC = data;
	if (autoLatch) latchDataOutput();
}
inline void WPCHardware::pulse(WPCHardwareSignal pin) {
	pulsePin(outputPins[pin]);
}

inline bool WPCHardware::readPin(WPCHardwareSignal pin) {
	if (inputPins[pin] != INVALID_PIN) {
		return digitalRead(outputPins[pin]);
	} else {
		return HIGH;
	}
}
inline void WPCHardware::writePin(WPCHardwareSignal pin, bool high) {
	if (outputPins[pin] != INVALID_PIN) {
		digitalWrite(outputPins[pin], high);
	}
}


inline void WPCHardware::pulsePin(byte pin) {
	if (pin != INVALID_PIN) {
		digitalWrite(pin, LOW);
		digitalWrite(pin, HIGH);
	}
}


#endif /* HARDWARE_H_ */
