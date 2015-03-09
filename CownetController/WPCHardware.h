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
	virtual void attachController(WPCController* controller);
	virtual WPCController* getController() const;

	virtual void latchDataInput();
	virtual void latchDataOutput();
	virtual byte readData(bool autoLatch = true);
	virtual void writeData(byte data, bool autoLatch = true);
	virtual void pulse(WPCHardwareSignal pin);
	virtual bool getBlanking() const;

	long counts[SIGNAL_COUNT+1];

	static WPCHardware& INSTANCE;
	static WPCController& PASSTHROUGH_CONTROLLER_INSTANCE;

private:
	WPCController* controller;
};

#endif /* HARDWARE_H_ */
