/*
 * WpcOutputController.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#include "WpcOutputController.h"

namespace us_cownet_lamps_wpc {

static const int MASK[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

WpcOutputController::WpcOutputController(byte* dataPinsIn, byte* signalPinsIn)
: dataPin(dataPinsIn), signalPin(signalPinsIn)
{
	for (int i = 0; i < 8; i++) {
		pinMode(dataPin[i], OUTPUT);
	}
	for (int i = 0; i < PinballOutputController::SIGNAL_COUNT; i++) {
		pinMode(signalPin[i], OUTPUT);
	}
}

WpcOutputController::~WpcOutputController() {
}

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
