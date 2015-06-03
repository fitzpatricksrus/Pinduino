/*
 * SimpleGreyscaleLampMatrix.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleGreyscaleLampMatrix.h"

namespace us_cownet_lamps_simple {

SimpleGreyscaleLampMatrix::SimpleGreyscaleLampMatrix()
: pattern(0), callback(0)
{
}

SimpleGreyscaleLampMatrix::~SimpleGreyscaleLampMatrix() {
}

GreyscaleLampPattern* SimpleGreyscaleLampMatrix::getPattern() {
	return pattern;
}

void SimpleGreyscaleLampMatrix::setPattern(GreyscaleLampPattern* lamps) {
	pattern = lamps;
}

void SimpleGreyscaleLampMatrix::setSyncCallback(Callback* callbackIn) {
	callback = callbackIn;
}

} /* namespace us_cownet_lamps_simple */
