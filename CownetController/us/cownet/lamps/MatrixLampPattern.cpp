/*
 * MatrixLampPattern.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: jfitzpatrick
 */

#include "MatrixLampPattern.h"

namespace us_cownet_lamps {

MatrixLampPattern::MatrixLampPattern() {

}

MatrixLampPattern::~MatrixLampPattern() {
}

byte MatrixLampPattern::getColumn(int x) {
	byte result = 0;
	for (int row = 0; row < 8; row++) {
		result <<= 1;
		if (getLamp(x, row)) {
			result |= 1;
		}
	}
	return result;
}

int MatrixLampPattern::getLampCount() {
	return (getColCount() + 7) / 8;
}

bool MatrixLampPattern::getLamp(int index) {
	return getLamp(index >> 3 & 0b000111111, index & 0b00000111);
}

} /* namespace us_cownet_lamps */
