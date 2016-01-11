/*
 * BooleanLampPattern.h
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_
#define US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_

#include "UniversalLampPattern.h"
#include <debug.h>

namespace us_cownet_lamps_patterns {

class BooleanLampPattern : public UniversalLampPattern {
public:
	BooleanLampPattern();
	BooleanLampPattern(byte* lampData, int lampCount);
	template <int lampCount> BooleanLampPattern(byte (&lampData)[lampCount]);
	virtual ~BooleanLampPattern();

	virtual int getLampCount();

	virtual bool getLamp(int index);
	virtual byte getLampBank(int bankIndex);
	virtual void setLamp(int index, bool on);

	virtual byte* getLampData();
	void setLampData(byte* lampData, int lampCount);

	template <int lampCount> void setLampData(byte (&lampData)[lampCount]);

	virtual byte getGreyLamp(int index);

	virtual RGBColor getRGBLamp(int index);

	template <int lampCountIn> void dumpLampData(byte (&lampDataIn)[lampCountIn]);

private:
	int lampCount;
	byte *lampData;
};

template<int lampCountIn>
inline BooleanLampPattern::BooleanLampPattern(byte (&lampDataIn)[lampCountIn])
: BooleanLampPattern(lampDataIn, lampCountIn << 3)
{
}

template<int lampCountIn>
inline void BooleanLampPattern::setLampData(byte (&lampDataIn)[lampCountIn]) {
	setLampData(lampData, lampCountIn << 3);
}

template<int lampCountIn>
void BooleanLampPattern::dumpLampData(byte (&lampDataIn)[lampCountIn]) {
	Serial << "*dumpCountIn = "<<lampCountIn<<" dumpDataIn[] = {";
	for (int i = 0; i < lampCountIn; i++) {
		Serial << lampData[i] << ",";
	}
	Serial << "}" << endl;
}


} /* namespace us_cownet_lamps_patterns */

#endif /* US_COWNET_LAMPS_PATTERNS_BOOLEANLAMPPATTERN_H_ */
