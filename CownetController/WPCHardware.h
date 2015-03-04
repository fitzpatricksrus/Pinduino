/*
 * Hardware.h
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#ifndef WPCHARDWARE_H_
#define WPCHARDWARE_H_

#include <Arduino.h>

class WPCHardware {
public:
	WPCHardware();
	virtual ~WPCHardware();

	typedef enum WPCHardwareSignal { 
		COL, ROW, TRIAC, 
		SOL1, SOL2, SOL3, SOL4, 
		ZERO_CROSS, BLANKING } HardwareSignal;

	class WPCHardwareController {
	public:
		WPCHardwareController();
		virtual ~WPCHardwareController();
		virtual void handleRowInterrupt(WPCHardware& hardware);
		virtual void handleColInterrupt(WPCHardware& hardware);
		virtual void handleTriacInterrupt(WPCHardware& hardware);
		virtual void handleSol1Interrupt(WPCHardware& hardware);
		virtual void handleSol2Interrupt(WPCHardware& hardware);
		virtual void handleSol3Interrupt(WPCHardware& hardware);
		virtual void handleSol4Interrupt(WPCHardware& hardware);
		virtual void handleZeroCrossInterrupt(WPCHardware& hardware);
		virtual void handleBlanking(WPCHardware& hardware);
	};

	virtual void attachController(WPCHardwareController* controller);
	virtual WPCHardwareController* getController() const;

	virtual void latchDataInput();
	virtual void latchDataOutput();
	virtual byte readData();
	virtual void writeData(byte data);
	virtual void pulse(WPCHardwareSignal pin);
	virtual bool getBlanking() const;

	static WPCHardware& INSTANCE;

private:
	WPCHardwareController* controller;
};

#endif /* HARDWARE_H_ */
