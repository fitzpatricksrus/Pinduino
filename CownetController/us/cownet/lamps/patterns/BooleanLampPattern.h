/*
 * BooleanLampPattern.h
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_
#define US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_

#include "UniversalLampPattern.h"

namespace us_cownet_lamps_patterns {

class BooleanLampPattern : public UniversalLampPattern {
public:
	BooleanLampPattern();
	template <int lampCount> BooleanLampPattern(byte lampData[lampCount]);
	virtual ~BooleanLampPattern();

	virtual int getLampCount();

	virtual bool getLamp(int index);
	virtual void setLamp(int index, bool on);

	virtual byte* getLampData();
	template <int lampCount> void setLampData(byte lampData[lampCount]);

	virtual byte getGreyLamp(int index);

	virtual RGBColor getRGBLamp(int index);

private:
	int lampCount;
	byte *lampData;
};

} /* namespace us_cownet_lamps_patterns */

template<int lampCountIn>
inline us_cownet_lamps_patterns::BooleanLampPattern::BooleanLampPattern(byte lampDataIn[lampCountIn]) {
	lampCount = lampCountIn << 3;
	lampData = lampDataIn;
}

template<int lampCountIn>
inline void us_cownet_lamps_patterns::BooleanLampPattern::setLampData(byte lampDataIn[lampCountIn]) {
	lampCount = lampCountIn << 3;
	lampData = lampDataIn;
}

#endif /* US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_ */
