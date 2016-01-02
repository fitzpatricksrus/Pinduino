/*
 * RGBLampPattern.h
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PATTERNS_RGBLAMPPATTERN_H_
#define US_COWNET_LAMPS_PATTERNS_RGBLAMPPATTERN_H_

#include "UniversalLampPattern.h"

namespace us_cownet_lamps_patterns {

class RGBLampPattern: public UniversalLampPattern {
public:
	RGBLampPattern();
	template <int lampCountIn> RGBLampPattern(RGBColor lampDataIn[lampCountIn]);
	RGBLampPattern(RGBColor* lampDataIn, int lampCountIn);
	virtual ~RGBLampPattern();

	virtual int getLampCount();
	virtual bool getLamp(int index);
	virtual byte getGreyLamp(int index);
	virtual RGBColor getRGBLamp(int index);
	virtual void setRGBLamp(int index, RGBColor color);

	virtual RGBColor* getLampData();
	template <int lampCountIn> void setLampData(RGBColor lampDataIn[lampCountIn]);
	virtual void setLampData(RGBColor* lampDataIn, int lampCountIn);

private:
	int lampCount;
	RGBColor* lampData;
};

} /* namespace us_cownet_lamps_patterns */

template<int lampCountIn>
inline us_cownet_lamps_patterns::RGBLampPattern::RGBLampPattern(RGBColor lampDataIn[lampCountIn]) {
	lampCount = lampCountIn;
	lampData = lampDataIn;
}

template<int lampCountIn>
inline void us_cownet_lamps_patterns::RGBLampPattern::setLampData(RGBColor lampDataIn[lampCountIn]) {
	lampCount = lampCountIn;
	lampData = lampDataIn;
}

#endif /* US_COWNET_LAMPS_PATTERNS_RGBLAMPPATTERN_H_ */
