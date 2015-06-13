/*
 * WpcOutputController.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#include "WpcOutputController.h"

#include <Debug.h>

namespace us_cownet_lamps_wpc {

WpcOutputController::WpcOutputController(byte* dataPinsIn, byte* signalPinsIn)
: dataPin(dataPinsIn), signalPin(signalPinsIn)
{
	// initialize all the pins to output
	for (int i = 0; i < 8; i++) {
		pinMode(dataPin[i], OUTPUT);
		digitalWrite(dataPin[i], HIGH);
	}
	// turn all data latches off for all signals
	for (int i = PinballOutputController::LAMP_ROW;
			i < PinballOutputController::SIGNAL_COUNT; i++) {
		pinMode(signalPin[i], OUTPUT);
		digitalWrite(signalPin[i], HIGH);
		// Note that the write() method will convert this to the
		// proper inverted value to turn things off/low
		write(static_cast<PinballOutputController::Register>(i), (byte)0);
	}
}

WpcOutputController::~WpcOutputController() {
}

static const int MASK[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void WpcOutputController::write(PinballOutputController::Register signal,
		byte value) {

	//        if (value == cachedData[signal.ordinal()]) {
	//            return;
	//        }
	//        cachedData[signal.ordinal()] = value;
	for (int i = 0; i < 8; i++) {
		// signals on the data lines are inverted on WPC so we convert
		// ON to low
		if ((value & MASK[i]) == 0) {
			digitalWrite(dataPin[i], HIGH);
		} else {
			digitalWrite(dataPin[i], LOW);
		}
	}
	// pulses are read on the rising edge, so bring it low and high again.
	digitalWrite(signalPin[signal], LOW);
	digitalWrite(signalPin[signal], HIGH);
}

} /* namespace us_cownet_lamps */
