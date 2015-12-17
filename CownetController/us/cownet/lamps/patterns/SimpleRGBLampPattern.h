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

	SimpleRGBLampPattern(Color* patternIn, int patternSize)
	: pattern(patternIn), lampCount(patternSize)
	{
	}

	template <int patternSize>
	SimpleRGBLampPattern(Color (&patternIn)[patternSize])
	: pattern(patternIn), lampCount(patternSize)
//	: SimpleRGBLampPattern(newPattern, patternSize)
	{
	}

	virtual ~SimpleRGBLampPattern();

	virtual int getLampCount() {
		return lampCount;
	}

	virtual Color getLamp(int index) {
		return pattern[index];
	}

	template <int patternSize>
	void setPattern(Color (&newPattern)[patternSize])  {
		setPattern(newPattern, patternSize);
	}

	virtual void setPattern(Color* patternIn, int patternSize) {
		lampCount = patternSize;
		pattern = patternIn;
	}

private:
	Color* pattern;
	int lampCount;
};

} /* namespace us_cownet_lamps_patterns */

#endif /* SIMPLERGBLAMPPATTERN_H_ */
