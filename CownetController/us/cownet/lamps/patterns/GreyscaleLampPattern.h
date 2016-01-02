/*
 * GreyscaleLampPattern.h
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PATTERNS_GREYSCALELAMPPATTERN_H_
#define US_COWNET_LAMPS_PATTERNS_GREYSCALELAMPPATTERN_H_

#include "UniversalLampPattern.h"

namespace us_cownet_lamps_patterns {

class GreyscaleLampPattern: public UniversalLampPattern {
public:
	GreyscaleLampPattern();
	template <int lampCount> GreyscaleLampPattern(byte lampData[lampCount]);
	GreyscaleLampPattern(byte* lampData, int lampCount);
	virtual ~GreyscaleLampPattern();

	virtual int getLampCount();

	virtual bool getLamp(int index);

	virtual byte getGreyLamp(int index);
	virtual void setGreyLamp(int index, byte value);

	virtual byte* getLampData();
	template <int lampCount> void setLampData(byte lampData[lampCount]);
	virtual void setLampData(byte* lampData, int lampCount);

	virtual RGBColor getRGBLamp(int index);

private:
	int lampCount;
	byte* lampData;
};

} /* namespace us_cownet_lamps_patterns */

template<int lampCountIn>
inline us_cownet_lamps_patterns::GreyscaleLampPattern::GreyscaleLampPattern(byte lampDataIn[lampCountIn]) {
	setLampData(lampDataIn, lampCountIn);
}

template<int lampCountIn>
inline void us_cownet_lamps_patterns::GreyscaleLampPattern::setLampData(byte lampDataIn[lampCountIn]) {
	setLampData(lampDataIn, lampCountIn);
}

#endif /* US_COWNET_LAMPS_PATTERNS_GREYSCALELAMPPATTERN_H_ */
