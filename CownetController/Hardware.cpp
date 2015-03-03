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
static Hardware::HardwareController defaultHardwareControllerInstance;

static const byte INPUT_PIN_COUNT = 9;
static byte inputPins[INPUT_PIN_COUNT] = {
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
static const byte OUTPUT_PIN_COUNT = 7;
static byte outputPins[OUTPUT_PIN_COUNT] = {
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
	Hardware::INSTANCE.getController()->handleRowInterrupt(Hardware::INSTANCE);
}
static void handleColInterrupt() {
	Hardware::INSTANCE.getController()->handleColInterrupt(Hardware::INSTANCE);
}
static void handleTriacInterrupt() {
	Hardware::INSTANCE.getController()->handleTriacInterrupt(Hardware::INSTANCE);
}
static void handleSol1Interrupt() {
	Hardware::INSTANCE.getController()->handleSol1Interrupt(Hardware::INSTANCE);
}
static void handleSol2Interrupt() {
	Hardware::INSTANCE.getController()->handleSol2Interrupt(Hardware::INSTANCE);
}
static void handleSol3Interrupt() {
	Hardware::INSTANCE.getController()->handleSol3Interrupt(Hardware::INSTANCE);
}
static void handleSol4Interrupt() {
	Hardware::INSTANCE.getController()->handleSol4Interrupt(Hardware::INSTANCE);
}
static void handleZeroCrossInterrupt() {
	Hardware::INSTANCE.getController()->handleZeroCrossInterrupt(Hardware::INSTANCE);
}

void Hardware::attachController(HardwareController* controllerIn) {
	if (controller == NULL) {
		// first time initialization
		for (byte i = 0; i < INPUT_PIN_COUNT; i++) {
			pinMode(inputPins[i], INPUT);
		}
		for (byte i = 0; i < OUTPUT_PIN_COUNT; i++) {
			pinMode(outputPins[i], OUTPUT);
		}
		attachPinChangeInterrupt(inputPins[ROW],handleRowInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[COL],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[TRIAC],handleTriacInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL1],handleSol1Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL2],handleSol2Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL3],handleSol3Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL4],handleSol4Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[ZERO_CROSS],handleZeroCrossInterrupt,RISING);
	}
	
	controller = controllerIn;
}

Hardware::HardwareController* Hardware::getController() const {
	return (controller) ? controller : &defaultHardwareControllerInstance;
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

// ------------------------------------------------------------------------------


