/*
 * Max7221LampController.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: Dad
 */

#include "Max7221LampController.h"

namespace us_cownet_lamps_controllers {

Max7221LampController::Max7221LampController(int selectPin)
: max7221(selectPin), pattern(NULL) {
}

Max7221LampController::~Max7221LampController() {
}

void Max7221LampController::setPattern(UniversalLampPattern* patternIn) {
	pattern = patternIn;
	int bankCount = (pattern->getLampCount() + 7) / 8;
	for (int i = 0; i < bankCount; i += 8) {
		max7221.setColumn(i, pattern->getLampBank(i));
	}
}

} /* namespace us_cownet_lamps */
