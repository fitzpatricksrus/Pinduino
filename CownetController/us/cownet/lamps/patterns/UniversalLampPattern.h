/*
 * UniversalLampPattern.h
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PATTERNS_UNIVERSALLAMPPATTERN_H_
#define US_COWNET_LAMPS_PATTERNS_UNIVERSALLAMPPATTERN_H_

#include "../../color/RGBColor.h"

namespace us_cownet_lamps_patterns {

using us_cownet_color::RGBColor;

class UniversalLampPattern {
public:
	UniversalLampPattern();
	virtual ~UniversalLampPattern();

	virtual int getLampCount() = 0;

	virtual bool getLamp(int index) = 0;
	virtual byte getLampBank(int bankIndex);

	virtual byte getGreyLamp(int index) = 0;

	virtual RGBColor getRGBLamp(int index) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_PATTERNS_UNIVERSALLAMPPATTERN_H_ */
