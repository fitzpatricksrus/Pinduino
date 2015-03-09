/*
 * Hardware.cpp
 */

#include "WPCHardware.h"
#include <PinChangeInt.h>
#include <Debug.h>


// ------------------------------------------------------------------------------
// The singleton hardware instance.
static WPCHardware defaultHardwareInstance;
WPCHardware& WPCHardware::INSTANCE = defaultHardwareInstance;

// Controller instance that simply passes data through when signaled
static WPCHardware::WPCPassthroughController passthroughControllerInstance;
WPCHardware::WPCController& WPCHardware::PASSTHROUGH_CONTROLLER_INSTANCE = passthroughControllerInstance;

// Controller instance that does nothing.  Data does not pass from input to output.
// This is the default controller if no other controller is set.
static WPCHardware::WPCController nullHardwareController;

// Mapping of all the pins to the board, both input and output.  These pins
// are them associated with the signal names in the interface.
enum {
	COL_IN_PIN = A14,
	ROW_IN_PIN = A15,
	TRIAC_IN = A13,
	SOL1_IN = A12,
	SOL2_IN = A11,
	SOL3_IN = A10,
	SOL4_IN = A9,
	ZERO_CROSS_IN = A8,
	BLANKING_IN = A7,
	
	TRIAC_OUT_PIN = 22,
	SOL1_OUT_PIN = 23,
	SOL2_OUT_PIN = 24,
	SOL3_OUT_PIN = 25,
	SOL4_OUT_PIN = 26,

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

// the pins that correspond to the input for a given signal.  This array
// is indexed using the HardwareSignal enum in the interface.
static byte arduinoInputPins[WPCHardware::SIGNAL_COUNT] = {
	COL_IN_PIN,		//COL
	ROW_IN_PIN,		//ROW
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
	WPCHardware::INVALID_PIN,	// LATCH_IN
	WPCHardware::INVALID_PIN,	// LATCH_OUT
};

// the pins that correspond to the output for a given signal.  This array
// is indexed using the HardwareSignal enum in the interface.
byte arduinoOutputPins[WPCHardware::SIGNAL_COUNT] = {
	COL_OUT_PIN,	//COL
	ROW_OUT_PIN,	//ROW
	TRIAC_OUT_PIN,	//TRIAC
	SOL1_OUT_PIN,	//SOL1
	SOL2_OUT_PIN,	//SOL2
	SOL3_OUT_PIN,	//SOL3
	SOL4_OUT_PIN,	//SOL4
	WPCHardware::INVALID_PIN,	//ZERO_CROSS
	WPCHardware::INVALID_PIN,	//BLANK
	D0_OUT_PIN,
	D1_OUT_PIN,
	D2_OUT_PIN,
	D3_OUT_PIN,
	D4_OUT_PIN,
	D5_OUT_PIN,
	D6_OUT_PIN,
	D7_OUT_PIN,
	CLK_DATA_IN,
	CLK_DATA_OUT,
};

WPCHardware::WPCHardware()
: controller(NULL), inputPins(arduinoInputPins), outputPins(arduinoOutputPins)
{
}

WPCHardware::~WPCHardware() {
}

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

void WPCHardware::attachController(WPCController* controllerIn) {
	if (controller == NULL) {
		Serial.println("Init hardware");
		// first time initialization
		for (byte i = 0; i < SIGNAL_COUNT; i++) {
			if (inputPins[i] != INVALID_PIN) {
				pinMode(inputPins[i], INPUT);
				Serial << inputPins[i] << "  ";
			}
		}
		Serial << endl;
		for (byte i = 0; i < SIGNAL_COUNT; i++) {
			if (outputPins[i] != INVALID_PIN) {
				pinMode(outputPins[i], OUTPUT);
			}
		}
		for (byte i = 0; i <= SIGNAL_COUNT; i++) {
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

WPCHardware::WPCController* WPCHardware::getController() const {
	return (controller != NULL) ? controller : &nullHardwareController;
}

/*
void WPCHardware::latchDataInput() {
	pulse(LATCH_IN);
}

void WPCHardware::latchDataOutput() {
	pulse(LATCH_OUT);
}

byte WPCHardware::readData(bool autoLatch) {
	if (autoLatch) latchDataInput();
	return PINL;
}

void WPCHardware::writeData(byte data, bool autoLatch) {
	PORTC = data;
	if (autoLatch) latchDataOutput();
}

void WPCHardware::pulse(WPCHardwareSignal pin) {
	pulsePin(outputPins[pin]);
}
*/

bool WPCHardware::getBlanking() const {
	return digitalRead(inputPins[BLANKING]);
}

// ------------------------------------------------------------------------------
// the default hardware controller does nothing.
WPCHardware::WPCController::WPCController() {
}

WPCHardware::WPCController::~WPCController() {
}

void WPCHardware::WPCController::handleRowInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleColInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleTriacInterrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleSol1Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleSol2Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleSol3Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleSol4Interrupt(WPCHardware& hardware) {
}

void WPCHardware::WPCController::handleZeroCrossInterrupt(WPCHardware& hardware) {
}

// ------------------------------------------------------------------------------
// the passthrough controller copies the data lines and echos the signal to output

//static char printVal2[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

WPCHardware::WPCPassthroughController::WPCPassthroughController() {
}

WPCHardware::WPCPassthroughController::~WPCPassthroughController() {
}

static inline void echoData(WPCHardware& hardware, WPCHardware::WPCHardwareSignal signal) {
	byte data = hardware.readData();
	hardware.writeData(data);
	hardware.pulse(signal);
//	data = ~data;
//	DebugSerial::INSTANCE << printVal2[ (data>>4) & 0x0F];
//	DebugSerial::INSTANCE << printVal2[ data & 0x0F];
}

void WPCHardware::WPCPassthroughController::handleRowInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::ROW);
//	DebugSerial::INSTANCE << "r" << endl;
}

void WPCHardware::WPCPassthroughController::handleColInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::COL);
//	DebugSerial::INSTANCE << "c" << endl;
}

void WPCHardware::WPCPassthroughController::handleTriacInterrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::TRIAC);
}

void WPCHardware::WPCPassthroughController::handleSol1Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL1);
}

void WPCHardware::WPCPassthroughController::handleSol2Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL2);
}

void WPCHardware::WPCPassthroughController::handleSol3Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL3);
}

void WPCHardware::WPCPassthroughController::handleSol4Interrupt(WPCHardware& hardware) {
	echoData(hardware, WPCHardware::SOL4);
}

void WPCHardware::WPCPassthroughController::handleZeroCrossInterrupt(WPCHardware& hardware) {
	hardware.pulse(WPCHardware::ZERO_CROSS);
}
