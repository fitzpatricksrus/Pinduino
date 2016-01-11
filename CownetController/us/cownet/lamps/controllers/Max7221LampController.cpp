/*
 * Max7221LampController.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: Dad
 */

#include "Max7221LampController.h"
#include <debug.h>

namespace us_cownet_lamps_controllers {

Max7221LampController::Max7221LampController(int selectPin)
: max7221(selectPin), pattern(NULL) {
	max7221.init();
}

Max7221LampController::~Max7221LampController() {
}

void Max7221LampController::setPattern(UniversalLampPattern* patternIn) {
	pattern = patternIn;
	int bankCount = pattern->getLampBankCount();
	for (int i = 0; i < bankCount; i++) {
		Serial << i << "  " << pattern->getLampBank(i) << endl;
		max7221.setColumn(i, pattern->getLampBank(i));
//		max7221.setColumn(i, 0);
	}
}

} /* namespace us_cownet_lamps */
