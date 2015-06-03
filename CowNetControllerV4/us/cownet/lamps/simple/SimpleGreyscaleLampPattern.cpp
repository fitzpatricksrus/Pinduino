/*
 * SimpleGreyscaleLampPattern.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleGreyscaleLampPattern.h"

namespace us_cownet_lamps_simple {

SimpleGreyscaleLampPattern::SimpleGreyscaleLampPattern() {
}

SimpleGreyscaleLampPattern::~SimpleGreyscaleLampPattern() {
}

byte** SimpleGreyscaleLampPattern::getPattern() {
	return pattern;
}

void SimpleGreyscaleLampPattern::setPattern(byte** patternIn) {
	pattern = patternIn;
}

byte SimpleGreyscaleLampPattern::getLamp(int col, int row) {
	if (pattern) {
		return pattern[col][row];
	} else {
		return 0;
	}
}

void SimpleGreyscaleLampPattern::setLamp(int col, int row, byte value) {
	if (pattern) {
		pattern[col][row] = value;
	}
}

} /* namespace us_cownet_lamps_simple */
