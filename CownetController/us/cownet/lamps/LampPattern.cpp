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
	byte result = 0;
	for (int i = 0; i < getColCount(); i++) {
		result <<= 1;
		if (getLamp(x, i)) {
			result |= 1;
		}
	}
	return result;
}

bool LampPattern::getLamp(int x, int y) {
	return (getColumn(x) & (1 << y)) != 0;
}

bool LampPattern::getLamp(int index) {
	// hey jf - this assumes an 8 light row size.
	return getLamp((index >> 3) & 0b00011111, index & 0b00000111);
}

/*
 Used only by pattern containers.  isDone() should return true when the
 pattern has displayed its entire state sequence once.  This has no affect
 on the lamp matrix, which will continue to cycle through columns.  Containers
 can decide how to proceed and may reset() the pattern, replace it, or
 continue to refresh the matrix with it.
 */
bool LampPattern::isDone() {
	return false;
}

/*
 Start the refresh sequence from the beginning.
 */
void LampPattern::reset() {
}

void LampPattern::detached() {
}

} /* namespace us_cownet_lamps */

