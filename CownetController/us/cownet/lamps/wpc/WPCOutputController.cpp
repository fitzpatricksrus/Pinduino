/*
 * WPCOutputController.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#include "WPCOutputController.h"

namespace us_cownet_lamps_wpc {

static const int MASK[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

WPCOutputController::WPCOutputController(int dataPinsIn[], int signalPinsIn[])
: dataPins(dataPinsIn), signalPins(signalPinsIn)
{
	for (int i = 0; i < PinballOutputController::REGISTER_COUNT; i++) {
		write((PinballOutputController::Register)i, 0);
	}
}

WPCOutputController::~WPCOutputController() {
}

int WPCOutputController::getColumnCount() {
	return 8;
}

void WPCOutputController::write(Register signal, byte value) {
//  if (value == cachedData[signal.ordinal()]) {
//  	return;
//  }
//  cachedData[signal.ordinal()] = value;
	for (int i = 0; i < 8; i++) {
		// signals on the data lines are inverted on WPC so we convert
		// ON to low
		if ((value & MASK[i]) == 0) {
			digitalWrite(dataPins[i], HIGH);
		} else {
			digitalWrite(dataPins[i], LOW);
		}
	}
	digitalWrite(signalPins[signal], LOW);
	digitalWrite(signalPins[signal], HIGH);
}
} /* namespace us_cownet_lamps_wpc */
