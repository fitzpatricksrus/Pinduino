/*
 * Hardware.cpp
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#include "WPCHardware.h"
#include <PinChangeInt.h>
#include <Debug.h>

// ------------------------------------------------------------------------------
class WPCPassthroughHardwareController : public WPCHardware::WPCHardwareController {
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
// ------------------------------------------------------------------------------

static WPCHardware defaultHardwareInstance;
WPCHardware& WPCHardware::INSTANCE = defaultHardwareInstance;
static WPCPassthroughHardwareController passthroughControllerInstance;
WPCHardware::WPCHardwareController& WPCHardware::PASSTHROUGH_CONTROLLER_INSTANCE = passthroughControllerInstance;
static WPCHardware::WPCHardwareController nullHardwareController;

enum {
	COL_SEL_IN = A14,
	ROW_SEL_IN = A15,
	TRIAC_IN = A13,
	SOL1_IN = A12,
	SOL2_IN = A11,
	SOL3_IN = A10,
	SOL4_IN = A9,
	ZERO_CROSS_IN = A8,
	BLANKING_IN = A7,

	D7_OUT_PIN = 30,
	D6_OUT_PIN = 31,
	D5_OUT_PIN = 32,
	D4_OUT_PIN = 33,
	D3_OUT_PIN = 34,
	D2_OUT_PIN = 35,
	D1_OUT_PIN = 36,
	D0_OUT_PIN = 37,
	CLK_DATA_OUT = 38,
	//39
	CLK_DATA_IN = 40,
	//41
	D0_IN_PIN = 42,
	D1_IN_PIN = 43,
	D2_IN_PIN = 44,
	D3_IN_PIN = 45,
	D4_IN_PIN = 46,
	D5_IN_PIN = 47,
	D6_IN_PIN = 48,
	D7_IN_PIN = 49,
	COL_OUT_PIN = 50,
	ROW_OUT_PIN = 51,
};

static const byte INPUT_PIN_COUNT = 17;
static byte inputPins[INPUT_PIN_COUNT] = {
	COL_SEL_IN,		//COL
	ROW_SEL_IN,		//ROW
	TRIAC_IN,		//TRIAC
	SOL1_IN,		//SOL1
	SOL2_IN,		//SOL2
	SOL3_IN,		//SOL3
	SOL4_IN,		//SOL4
	ZERO_CROSS_IN,	//ZERO_CROSS
	BLANKING_IN,	//BLANK
	D0_IN_PIN,
	D1_IN_PIN,
	D2_IN_PIN,
	D3_IN_PIN,
	D4_IN_PIN,
	D5_IN_PIN,
	D6_IN_PIN,
	D7_IN_PIN,
};
static const byte OUTPUT_PIN_COUNT = 19;
static byte outputPins[OUTPUT_PIN_COUNT] = {
	COL_OUT_PIN,		//COL
	ROW_OUT_PIN,		//ROW
	255,	//TRIAC
	255,	//SOL1
	255,	//SOL2
	255,	//SOL3
	255,	//SOL4
	255,	//ZERO_CROSS
	255,	//BLANK
	CLK_DATA_OUT,
	CLK_DATA_IN,
	D0_OUT_PIN,
	D1_OUT_PIN,
	D2_OUT_PIN,
	D3_OUT_PIN,
	D4_OUT_PIN,
	D5_OUT_PIN,
	D6_OUT_PIN,
	D7_OUT_PIN,
};

static inline void pulsePin(byte pin) {
	if (pin != 255) {
		digitalWrite(pin, LOW);
		digitalWrite(pin, HIGH);
	}
}

WPCHardware::WPCHardware()
: controller(NULL)
{
}

WPCHardware::~WPCHardware() {
}

typedef enum WPCHardwareSignal { 
		COL, ROW, TRIAC, 
		SOL1, SOL2, SOL3, SOL4, 
		ZERO_CROSS, BLANKING } WPCHardwareSignal;

static void handleRowInterrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::ROW]++;
	WPCHardware::INSTANCE.getController()->handleRowInterrupt(WPCHardware::INSTANCE);
}
static void handleColInterrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::COL]++;
	WPCHardware::INSTANCE.getController()->handleColInterrupt(WPCHardware::INSTANCE);
}
static void handleTriacInterrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::TRIAC]++;
	WPCHardware::INSTANCE.getController()->handleTriacInterrupt(WPCHardware::INSTANCE);
}
static void handleSol1Interrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::SOL1]++;
	WPCHardware::INSTANCE.getController()->handleSol1Interrupt(WPCHardware::INSTANCE);
}
static void handleSol2Interrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::SOL2]++;
	WPCHardware::INSTANCE.getController()->handleSol2Interrupt(WPCHardware::INSTANCE);
}
static void handleSol3Interrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::SOL3]++;
	WPCHardware::INSTANCE.getController()->handleSol3Interrupt(WPCHardware::INSTANCE);
}
static void handleSol4Interrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::SOL4]++;
	WPCHardware::INSTANCE.getController()->handleSol4Interrupt(WPCHardware::INSTANCE);
}
static void handleZeroCrossInterrupt() {
	WPCHardware::INSTANCE.counts[WPCHardware::ZERO_CROSS]++;
	WPCHardware::INSTANCE.getController()->handleZeroCrossInterrupt(WPCHardware::INSTANCE);
}

void WPCHardware::attachController(WPCHardwareController* controllerIn) {
	if (controller == NULL) {
		Serial.println("Init hardware");
		// first time initialization
		for (byte i = 0; i < INPUT_PIN_COUNT; i++) {
			pinMode(inputPins[i], INPUT);
			Serial << inputPins[i] << "  ";
		}
		Serial << endl;
		for (byte i = 0; i < OUTPUT_PIN_COUNT; i++) {
			pinMode(outputPins[i], OUTPUT);
		}
		for (byte i = 0; i <= BLANKING; i++) {
			counts[i] = 0;
		}
		DDRL = 0; // data INPUT
		DDRC = -1; // data OUTPUT
		controller = controllerIn;
		attachPinChangeInterrupt(inputPins[ROW],handleRowInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[COL],handleColInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[TRIAC],handleTriacInterrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL1],handleSol1Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL2],handleSol2Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL3],handleSol3Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[SOL4],handleSol4Interrupt,RISING);
		attachPinChangeInterrupt(inputPins[ZERO_CROSS],handleZeroCrossInterrupt,RISING);
	} else {
		controller = controllerIn;
	}
}

WPCHardware::WPCHardwareController* WPCHardware::getController() const {
	return (controller != NULL) ? controller : &nullHardwareController;
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

WPCPassthroughHardwareController::WPCPassthroughHardwareController() {
}

WPCPassthroughHardwareController::~WPCPassthroughHardwareController() {
}

static inline void echoData(WPCHardware& hardware, WPCHardware::WPCHardwareSignal signal) {
	hardware.latchDataInput();
	hardware.writeData(hardware.readData());
	hardware.latchDataOutput();
	hardware.pulse(signal);
}

void WPCPassthroughHardwareController::handleRowInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::ROW);
}

void WPCPassthroughHardwareController::handleColInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::COL);
}

void WPCPassthroughHardwareController::handleTriacInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::TRIAC);
}

void WPCPassthroughHardwareController::handleSol1Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL1);
}

void WPCPassthroughHardwareController::handleSol2Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL2);
}

void WPCPassthroughHardwareController::handleSol3Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL3);
}

void WPCPassthroughHardwareController::handleSol4Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL4);
}

void WPCPassthroughHardwareController::handleZeroCrossInterrupt(WPCHardware& hardware) {
	hardware.pulse(WPCHardware::ZERO_CROSS);
}

void WPCPassthroughHardwareController::handleBlanking(WPCHardware& hardware) {
}

