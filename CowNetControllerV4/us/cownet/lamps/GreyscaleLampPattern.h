/*
 * GreyscaleLampPattern.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_GREYSCALELAMPPATTERN_H_
#define US_COWNET_LAMPS_GREYSCALELAMPPATTERN_H_

#include <Arduino.h>

namespace us_cownet_lamps {

class GreyscaleLampPattern {
public:
	GreyscaleLampPattern();
	virtual ~GreyscaleLampPattern();

	virtual byte** getPattern() = 0;

	virtual byte getLamp(int col, int row) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_GREYSCALELAMPPATTERN_H_ */
