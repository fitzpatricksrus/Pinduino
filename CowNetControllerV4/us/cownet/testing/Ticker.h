/*
 * Ticker.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TESTING_TICKER_H_
#define US_COWNET_TESTING_TICKER_H_

namespace us_cownet_testing {

class Ticker {
public:
	Ticker(unsigned long periodMicrosIn);
	~Ticker();

	void setPeriod(unsigned long periodInMicrosIn);
	bool isTime();

private:
	unsigned long periodMicros;
	unsigned long lastTick;
};

} /* namespace us_cownet_testing */

#endif /* US_COWNET_TESTING_TICKER_H_ */
