/*
 * Ticker.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TESTING_TICKER_H_
#define US_COWNET_TESTING_TICKER_H_

namespace us_cownet_timers {

class Ticker {
public:
	Ticker(unsigned long periodTicksIn);
	~Ticker();

	void setPeriod(unsigned long periodInTicksIn);
	unsigned long getPeriod();
	bool isTime();

private:
	unsigned long periodTicks;
	unsigned long lastTick;
};

} /* namespace us_cownet_testing */

#endif /* US_COWNET_TESTING_TICKER_H_ */
