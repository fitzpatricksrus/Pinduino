/*
 * Hardware.h
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <Arduino.h>

class Hardware {
public:
	Hardware();
	virtual ~Hardware();

	typedef enum HardwareSignal { COL, ROW, TRIAC, SOL1, SOL2, SOL3, SOL4, ZERO_CROSS, BLANKING } HardwareSignal;

	class HardwareController {
	public:
		HardwareController();
		virtual ~HardwareController();
		virtual void handleInterrupt(Hardware& hardware, HardwareSignal signal);
		virtual void handleRowInterrupt(Hardware& hardware);
		virtual void handleColInterrupt(Hardware& hardware);
		virtual void handleTriacInterrupt(Hardware& hardware);
		virtual void handleSol1Interrupt(Hardware& hardware);
		virtual void handleSol2Interrupt(Hardware& hardware);
		virtual void handleSol3Interrupt(Hardware& hardware);
		virtual void handleSol4Interrupt(Hardware& hardware);
		virtual void handleZeroCrossInterrupt(Hardware& hardware);
		virtual void handleBlanking(Hardware& hardware);
	};

	virtual void attachController(HardwareController* controller);
	virtual HardwareController* getController() const;

	virtual void latchDataInput();
	virtual void latchDataOutput();
	virtual byte readData();
	virtual void writeData(byte data);
	virtual void pulse(HardwareSignal pin);
	virtual bool getBlanking() const;

	static HardwareController& passThroughController;
	static Hardware& INSTANCE;

private:
	HardwareController* controller;
};

#endif /* HARDWARE_H_ */
