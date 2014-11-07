/*
 * MatrixPattern.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#include "MatrixPattern.h"

namespace pins {

MatrixPattern::MatrixPattern() {
}

MatrixPattern::~MatrixPattern() {
}

bool MatrixPattern::getPinValue(byte col, byte row) const {
	return (*this)[col][row];
}

} /* namespace pins */
