/*
 * DebugLampController.cpp
 *
 *  Created on: Jan 10, 2016
 *      Author: Dad
 */

#include "DebugLampController.h"

#include <debug.h>

namespace us_cownet_lamps_controllers {

DebugLampController::DebugLampController()
: pattern(NULL)
{
}

DebugLampController::~DebugLampController() {
}

void DebugLampController::setPattern(UniversalLampPattern* patternIn) {
	pattern = patternIn;

	Serial << "Pattern::getLampBankCount = " << patternIn->getLampBankCount() << endl;
	Serial << "Pattern::lampBankData = {" << endl;
	for (int i = 0; i < patternIn->getLampBankCount(); i++) {
		Serial << _BIN(patternIn->getLampBank(i)) << endl;
	}
	Serial << "}" << endl;

	Serial << "Pattern::getLampCount = " << patternIn->getLampCount() << endl;
	Serial << "Pattern::lampData = {";
	for (int i = 0; i < patternIn->getLampCount(); i++) {
		if (i%8 == 0) Serial << endl;
		Serial << (patternIn->getLamp(i) ? "*" : "-") << ",";
	}
	Serial << "}" << endl;

	Serial << "Pattern::greyLampData = {";
	for (int i = 0; i < patternIn->getLampCount(); i++) {
		if (i%8 == 0) Serial << endl;
		Serial << patternIn->getGreyLamp(i) << ",";
	}
	Serial << "}" << endl;

}

} /* namespace us_cownet_lamps_controllers */
