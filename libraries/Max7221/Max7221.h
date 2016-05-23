/*
 * Max7221.h
 *
 *  Created on: Jan 21, 2015
 *      Author: Dad
 */

#ifndef MAX7221_H_
#define MAX7221_H_

#include <Arduino.h>

class Max7221 {
public:
	Max7221(byte selectPin);
	virtual ~Max7221();

	void init();
	void init(byte selectPin);
	void setIntensity(byte value0_15);
	void setScanLimit(byte lines0_7);
	void setEnabled(bool on);
	void setTest(bool on);
	void setColumn(byte column, byte values);

private:
	void send7221Command(byte command, byte value);
	byte selectPin;
};

#endif /* MAX7221_H_ */
