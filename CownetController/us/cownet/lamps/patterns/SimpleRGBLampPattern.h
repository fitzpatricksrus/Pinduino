/*
 * SimpleRGBLampPattern.h
 *
 *  Created on: Nov 18, 2015
 *      Author: jfitzpatrick
 */

#ifndef SIMPLERGBLAMPPATTERN_H_
#define SIMPLERGBLAMPPATTERN_H_

#include "../RGBLampPattern.h"

namespace us_cownet_lamps_patterns {

using us_cownet_lamps::RGBLampPattern;

class SimpleRGBLampPattern: public RGBLampPattern {
public:
	SimpleRGBLampPattern();

	SimpleRGBLampPattern(RGB* patternIn, int patternSize)
	: lampCount(patternSize), pattern(patternIn)
	{
	}

	template <int patternSize>
	SimpleRGBLampPattern(RGB (&newPattern)[patternSize])
	: SimpleRGBLampPattern(newPattern, patternSize)
	{
	}

	virtual ~SimpleRGBLampPattern();

	virtual int getLampCount() {
		return lampCount;
	}

	virtual RGB getLamp(int index) {
		return pattern[index];
	}

	template <int patternSize>
	void setPattern(RGB (&newPattern)[patternSize])  {
		setPattern(newPattern, patternSize);
	}

	virtual void setPattern(RGB* patternIn, int patternSize) {
		lampCount = patternSize;
		pattern = patternIn;
	}

private:
	int lampCount;
	RGB* pattern;
};

} /* namespace us_cownet_lamps_patterns */

#endif /* SIMPLERGBLAMPPATTERN_H_ */
