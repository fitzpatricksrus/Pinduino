/*
 * Ticker.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TESTING_TICKER_H_
#define US_COWNET_TESTING_TICKER_H_

#include "PeriodicEvent.h"

namespace us_cownet_timers {

class Ticker : public PeriodicEvent {
public:
	Ticker(unsigned long periodTicksIn) : PeriodicEvent(true, periodTicksIn) {}
	~Ticker() {}
};

} /* namespace us_cownet_testing */

#endif /* US_COWNET_TESTING_TICKER_H_ */
