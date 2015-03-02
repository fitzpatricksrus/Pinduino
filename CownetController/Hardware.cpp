/*
 * Hardware.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#include "Hardware.h"
#include <PinChangeInt.h>

Hardware::Hardware() {
}

Hardware::~Hardware() {
}

// ------------------------------------------------------------------------------
Hardware::HardwareController::HardwareController() {
}

Hardware::HardwareController::~HardwareController() {
}

void Hardware::HardwareController::handleInterrupt(Hardware& hardware, HardwareSignal signal) {
	switch (signal) {
	case ROW:
		handleRowInterrupt(hardware);
		break;
	case COL:
		handleColInterrupt(hardware);
		break;
	case TRIAC:
		handleTriacInterrupt(hardware);
		break;
	case SOL1:
		handleSol1Interrupt(hardware);
		break;
	case SOL2:
		handleSol2Interrupt(hardware);
		break;
	case SOL3:
		handleSol3Interrupt(hardware);
		break;
	case SOL4:
		handleSol4Interrupt(hardware);
		break;
	case ZERO_CROSS:
		handleZeroCrossInterrupt(hardware);
		break;
	case BLANKING:
		handleBlanking(hardware);
		break;
	default:
		break;
	};
}

static inline void echoData(Hardware& hardware, Hardware::HardwareSignal signal) {
	hardware.latchDataInput();
	hardware.writeData(hardware.readData());
	hardware.latchDataOutput();
	hardware.pulse(signal);
}

void Hardware::HardwareController::handleRowInterrupt(Hardware& hardware) {
	echoData(hardware, ROW);
}

void Hardware::HardwareController::handleColInterrupt(Hardware& hardware) {
	echoData(hardware, COL);
}

void Hardware::HardwareController::handleTriacInterrupt(Hardware& hardware) {
	echoData(hardware, TRIAC);
}

void Hardware::HardwareController::handleSol1Interrupt(Hardware& hardware) {
	echoData(hardware, SOL1);
}

void Hardware::HardwareController::handleSol2Interrupt(Hardware& hardware) {
	echoData(hardware, SOL2);
}

void Hardware::HardwareController::handleSol3Interrupt(Hardware& hardware) {
	echoData(hardware, SOL3);
}

void Hardware::HardwareController::handleSol4Interrupt(Hardware& hardware) {
	echoData(hardware, SOL4);
}

void Hardware::HardwareController::handleZeroCrossInterrupt(Hardware& hardware) {
}

void Hardware::HardwareController::handleBlanking(Hardware& hardware) {
}

static Hardware::HardwareController defaultHardwareControllerInstance;
Hardware::HardwareController& Hardware::defaultController = defaultHardwareControllerInstance;

// ------------------------------------------------------------------------------

class DefaultHardware : public Hardware {
public:
	DefaultHardware();
	virtual ~DefaultHardware();

	virtual void attachController(HardwareController* controller);

	virtual void latchDataInput();
	virtual void latchDataOutput();
	virtual byte readData();
	virtual void writeData(byte data);
	virtual void pulse(HardwareSignal pin);
	virtual bool getBlanking() const;

	HardwareController* controller;
};

static DefaultHardware defaultHardwareInstance;
Hardware& Hardware::defaultHardware = defaultHardwareInstance;
static byte inputPins[9] = {
	A14,	//COL
	A15,	//ROW
	A13,	//TRIAC
	A12,	//SOL1
	A11,	//SOL2
	A10,	//SOL3
	A9,		//SOL4
	A8,		//ZERO_CROSS
	A7,		//BLANK
};
static byte outputPins[7] = {
	22,		//COL
	31,		//ROW
	0,		//TRIAC
	0,		//SOL1
	0,		//SOL2
	0,		//SOL3
	0,		//SOL4
};
// control bus
static const byte CLK_DATA_OUT = 38;	//PD7
//static const byte EN_DATA_OUT = 39;	//PG2
static const byte CLK_DATA_IN = 40;		//PG1
//static const byte EN_DATA_IN = 41;	//PG0

static inline void pulsePin(byte pin) {
	digitalWrite(pin, LOW);
	digitalWrite(pin, HIGH);
}

DefaultHardware::DefaultHardware() {
	controller = &Hardware::defaultController;
}

DefaultHardware::~DefaultHardware() {
}

void DefaultHardware::attachController(HardwareController* controllerIn) {
	controller = controllerIn;
}

void DefaultHardware::latchDataInput() {
	pulsePin(CLK_DATA_IN);
}

void DefaultHardware::latchDataOutput() {
	pulsePin(CLK_DATA_OUT);
}

byte DefaultHardware::readData() {
	return PINL;
}

void DefaultHardware::writeData(byte data) {
	PORTC = data;
}

void DefaultHardware::pulse(HardwareSignal pin) {
	pulsePin(outputPins[pin]);
}

bool DefaultHardware::getBlanking() const {
	return digitalRead(inputPins[BLANKING]);
}


//attachPinChangeInterrupt(ROW_SEL_IN,handleRowInterrupt,RISING);
//attachPinChangeInterrupt(COL_SEL_IN,handleColInterrupt,RISING);


