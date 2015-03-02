/*
 * Hardware.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#include "Hardware.h"
#include <PinChangeInt.h>

static Hardware defaultHardwareInstance;
Hardware& Hardware::INSTANCE = defaultHardwareInstance;

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
static const byte CLK_DATA_IN = 40;		//PG1

static inline void pulsePin(byte pin) {
	digitalWrite(pin, LOW);
	digitalWrite(pin, HIGH);
}

Hardware::Hardware()
: controller(NULL)
{
}

Hardware::~Hardware() {
}
typedef enum HardwareSignal { COL, ROW, TRIAC, SOL1, SOL2, SOL3, SOL4, ZERO_CROSS, BLANKING } HardwareSignal;

static void handleRowInterrupt() {
	Hardware::INSTANCE.getController()->handleInterrupt()
}
static void handleColIterrupt() {
}
static void handleTriacInterrupt() {
}
static void handleSol1Interrupt() {
}
static void handleSol2Interrupt() {
}
static void handleSol3Interrupt() {
}
static void handleSol4Interrupt() {
}
static void handleZeroCrossInterrupt() {
}

void Hardware::attachController(HardwareController* controllerIn) {
	controller = controllerIn;
	attachPinChangeInterrupt(inputPins[ROW],handleRowInterrupt,RISING);
	attachPinChangeInterrupt(inputPIns[COL],handleColInterrupt,RISING);
}

void Hardware::latchDataInput() {
	pulsePin(CLK_DATA_IN);
}

void Hardware::latchDataOutput() {
	pulsePin(CLK_DATA_OUT);
}

byte Hardware::readData() {
	return PINL;
}

void Hardware::writeData(byte data) {
	PORTC = data;
}

void Hardware::pulse(HardwareSignal pin) {
	pulsePin(outputPins[pin]);
}

bool Hardware::getBlanking() const {
	return digitalRead(inputPins[BLANKING]);
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


