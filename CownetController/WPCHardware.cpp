/*
 * Hardware.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#include "WPCHardware.h"
#include <PinChangeInt.h>

static WPCHardware defaultHardwareInstance;
WPCHardware& WPCHardware::INSTANCE = defaultHardwareInstance;
static WPCHardware::WPCHardwareController passthroughControllerInstance;
WPCHardware::WPCHardwareController& PASSTHROUGH_CONTROLLER_INSTANCE = passthroughControllerInstance;
static WPCHardware::WPCHardwareController nullHardwareController;

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
	-1,		//TRIAC
	-1,		//SOL1
	-1,		//SOL2
	-1,		//SOL3
	-1,		//SOL4
	-1,		//ZERO_CROSS
	-1		//BLANK
};
// control bus
static const byte CLK_DATA_OUT = 38;	//PD7
static const byte CLK_DATA_IN = 40;		//PG1

static inline void pulsePin(byte pin) {
	if (pin != -1) {
		digitalWrite(pin, LOW);
		digitalWrite(pin, HIGH);
	}
}

WPCHardware::WPCHardware()
: controller(&nullHardwareController)
{
}

WPCHardware::~WPCHardware() {
}
typedef enum WPCHardwareSignal { 
		COL, ROW, TRIAC, 
		SOL1, SOL2, SOL3, SOL4, 
		ZERO_CROSS, BLANKING } WPCHardwareSignal;

static void handleRowInterrupt() {
	WPCHardware::INSTANCE.getController()->handleRowInterrupt()
}
static void handleColIterrupt() {
	WPCHardware::INSTANCE.getController()->handleColInterrupt()
}
static void handleTriacInterrupt() {
	WPCHardware::INSTANCE.getController()->handleTriacInterrupt()
}
static void handleSol1Interrupt() {
	WPCHardware::INSTANCE.getController()->handleSol1Interrupt()
}
static void handleSol2Interrupt() {
	WPCHardware::INSTANCE.getController()->handleSol2Interrupt()
}
static void handleSol3Interrupt() {
	WPCHardware::INSTANCE.getController()->handleSol3Interrupt()
}
static void handleSol4Interrupt() {
	WPCHardware::INSTANCE.getController()->handleSol4Interrupt()
}
static void handleZeroCrossInterrupt() {
	WPCHardware::INSTANCE.getController()->handleZeroCrossInterrupt()
}

void WPCHardware::attachController(WPCHardwareController* controllerIn) {
	if (controller == NULL) {
		// first time initialization
		for (byte i = 0; i < INPUT_PIN_COUNT; i++) {
			pinMode(inputPins[i], INPUT);
		}
		for (byte i = 0; i < OUTPUT_PIN_COUNT; i++) {
			pinMode(outputPins[i], OUTPUT);
		}
		attachPinChangeInterrupt(inputPins[ROW],handleRowInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[COL],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[TRIAC],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[SOL1],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[SOL2],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[SOL3],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[SOL4],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPIns[ZERO_CROSS],handleColInterrupt,RISING);
	}
	
	controller = controllerIn;
}

WPCHardwareController* WPCHardware::getController() const {
	return (controller) ? controller : &nullHardwareController;
}

void WPCHardware::latchDataInput() {
	pulsePin(CLK_DATA_IN);
}

void WPCHardware::latchDataOutput() {
	pulsePin(CLK_DATA_OUT);
}

byte WPCHardware::readData() {
	return PINL;
}

void WPCHardware::writeData(byte data) {
	PORTC = data;
}

void WPCHardware::pulse(WPCHardwareSignal pin) {
	pulsePin(outputPins[pin]);
}

bool WPCHardware::getBlanking() const {
	return digitalRead(inputPins[BLANKING]);
}

// ------------------------------------------------------------------------------
WPCHardware::WPCHardwareController::WPCHardwareController() {
}

WPCHardware::WPCHardwareController::~WPCHardwareController() {
}

void WPCHardware::WPCHardwareController::handleRowInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleColInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleTriacInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleSol1Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleSol2Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleSol3Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleSol4Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleZeroCrossInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCHardwareController::handleBlanking(WPCHardware& hardware) {
}


// ------------------------------------------------------------------------------
class WPCPassthroughHardwareController : public WPCHardwareController {
public:
	WPCPassthroughHardwareController();
	virtual ~WPCPassthroughHardwareController();
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

WPCPassthroughHardwareController::WPCHardwareController() {
}

WPCPassthroughHardwareController::~WPCHardwareController() {
}

static inline void echoData(WPCHardware& hardware, WPCHardware::WPCHardwareSignal signal) {
	hardware.latchDataInput();
	hardware.writeData(hardware.readData());
	hardware.latchDataOutput();
	hardware.pulse(signal);
}

void WPCPassthroughHardwareController::handleRowInterrupt(WPCHardware& hardware) {
	echoData(hardware, ROW);
}

void WPCPassthroughHardwareController::handleColInterrupt(WPCHardware& hardware) {
	echoData(hardware, COL);
}

void WPCPassthroughHardwareController::handleTriacInterrupt(WPCHardware& hardware) {
	echoData(hardware, TRIAC);
}

void WPCPassthroughHardwareController::handleSol1Interrupt(WPCHardware& hardware) {
	echoData(hardware, SOL1);
}

void WPCPassthroughHardwareController::handleSol2Interrupt(WPCHardware& hardware) {
	echoData(hardware, SOL2);
}

void WPCPassthroughHardwareController::handleSol3Interrupt(WPCHardware& hardware) {
	echoData(hardware, SOL3);
}

void WPCPassthroughHardwareController::handleSol4Interrupt(WPCHardware& hardware) {
	echoData(hardware, SOL4);
}

void WPCPassthroughHardwareController::handleZeroCrossInterrupt(WPCHardware& hardware) {
}

void WPCPassthroughHardwareController::handleBlanking(WPCHardware& hardware) {
}

