/*
 * PinPattern.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#include <scratchpins/PinPattern.h>

PinPattern::PinPattern() {
}

PinPattern::~PinPattern() {
}

bool PinPattern::operator [](byte ndx) const {
	return getPinValue(ndx);
}
