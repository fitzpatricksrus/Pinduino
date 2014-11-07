/*
 * PinPattern.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#include "PinPattern.h"

namespace pins {

PinPattern::PinPattern() {
}

PinPattern::~PinPattern() {
}

bool PinPattern::operator [](byte ndx) const {
	return getPinValue(ndx);
}

} // namespace pins
