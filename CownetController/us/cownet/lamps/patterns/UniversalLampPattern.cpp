/*
 * UniversalLampPattern.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#include "UniversalLampPattern.h"

namespace us_cownet_lamps_patterns {

UniversalLampPattern::UniversalLampPattern() {
}

UniversalLampPattern::~UniversalLampPattern() {
}

int UniversalLampPattern::getLampBankCount() {
	return (getLampCount() + 7) / 8;
}

byte UniversalLampPattern::getLampBank(int bankIndex) {
	byte result = 0;
	int bankBase = bankIndex << 3;
	for (int i = 7; i >= 0; i--) {
		result <<= 1;
		if (getLamp(bankBase + i)) {
			result |= 1;
		}
	}
	return result;
}

} /* namespace us_cownet_lamps */

