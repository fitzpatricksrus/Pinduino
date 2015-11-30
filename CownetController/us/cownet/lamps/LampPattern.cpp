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

byte LampPattern::getColumn(int x) {
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

int LampPattern::getColCount() {
	return (getLampCount() + 7) / 8;
}

void LampPattern::attached() {
}

void LampPattern::endOfMatrixSync() {
}

bool LampPattern::isDone() {
	return false;
}

void LampPattern::reset() {
}

void LampPattern::detached() {
}

} /* namespace us_cownet_lamps */

