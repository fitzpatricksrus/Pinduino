/*
 * SimpleRGBLampPattern.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleRGBLampPattern.h"

namespace us_cownet_lamps_patterns {

SimpleRGBLampPattern::SimpleRGBLampPattern()
: pattern(NULL), lampCount(0)
{
}

SimpleRGBLampPattern::~SimpleRGBLampPattern() {
}

static SimpleRGBLampPattern::RGB temp[100];
static SimpleRGBLampPattern testPattern(temp);

} /* namespace us_cownet_lamps_patterns */


