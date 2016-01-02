/*
 * UniversalLampPattern.cpp
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#include "UniversalLampPattern.h"

namespace us_cownet_lamps {

UniversalLampPattern::UniversalLampPattern() {
}

UniversalLampPattern::~UniversalLampPattern() {
}

bool UniversalLampPattern::getLamp(int index) {
	return getRGBLamp(index).toOnOffValue();
}

int UniversalLampPattern::getGrayLamp(int index) {
	return getRGBLamp(index).toGreyValue();
}

} /* namespace us_cownet_lamps */
