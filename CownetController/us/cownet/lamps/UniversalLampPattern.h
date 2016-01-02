/*
 * UniversalLampPattern.h
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_UNIVERSALLAMPPATTERN_H_
#define US_COWNET_LAMPS_UNIVERSALLAMPPATTERN_H_

#include "../color/RGBColor.h"

namespace us_cownet_lamps {

using us_cownet_color::RGBColor;

class UniversalLampPattern {
public:
	UniversalLampPattern();
	virtual ~UniversalLampPattern();

	virtual int getLampCount() = 0;

	virtual bool getLamp(int index);

	virtual int getGrayLamp(int index);

	virtual RGBColor getRGBLamp(int index) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_UNIVERSALLAMPPATTERN_H_ */
