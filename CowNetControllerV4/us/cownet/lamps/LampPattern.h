/*
 * LampPattern.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_LAMPPATTERN_H_
#define US_COWNET_LAMPS_LAMPPATTERN_H_

#include <Arduino.h>

namespace us_cownet_lamps {

class LampPattern {
public:
	LampPattern();
	virtual ~LampPattern();

	virtual byte* getPattern() = 0;
	virtual bool getLamp(int x, int y) = 0;
	virtual byte getColCount() = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_LAMPPATTERN_H_ */
