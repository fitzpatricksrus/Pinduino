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

	virtual void attachController(HardwareController* controller) = 0;

	virtual void latchDataInput() = 0;
	virtual void latchDataOutput()= 0;
	virtual byte readData() = 0;
	virtual void writeData(byte data) = 0;
	virtual void pulse(HardwareSignal pin) = 0;
	virtual bool getBlanking() const = 0;

	static HardwareController& defaultController;
	static Hardware& defaultHardware;
};

#endif /* HARDWARE_H_ */
