/*
 * LampPattern.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: Dad
 */

#include "LampPattern.h"

namespace us_cownet_lamps {

LampPattern::LampPattern() {
}

LampPattern::~LampPattern() {
}

void LampPattern::attached() {
}

void LampPattern::endOfMatrixSync() {
}

void LampPattern::detached() {
}

int LampPattern::getLampBankCount() {
	return (getLampCount() + 7) / 8;
}

byte LampPattern::getLampBank(int x) {
	int colBase = x * 8;
	byte result = 0;
	for (int row = 0; row < 8; row++) {
		result <<= 1;
		if (getLamp(colBase + row)) {
			result |= 1;
		}
	}
	return result;
}

bool LampPattern::isDone() {
	return false;
}

void LampPattern::reset() {
}

} /* namespace us_cownet_lamps */

