/*
 * LinearLampPattern.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: jfitzpatrick
 */

#include "LinearLampPattern.h"

namespace us_cownet_lamps {

LinearLampPattern::LinearLampPattern() {
	// TODO Auto-generated constructor stub

}

LinearLampPattern::~LinearLampPattern() {
	// TODO Auto-generated destructor stub
}

byte LinearLampPattern::getColumn(int x) {
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

int LinearLampPattern::getColCount() {
	return (getLampCount() + 7) / 8;
}

bool LinearLampPattern::getLamp(int x, int y) {
	return getLamp((x << 3) + y);
}

} /* namespace us_cownet_lamps */
