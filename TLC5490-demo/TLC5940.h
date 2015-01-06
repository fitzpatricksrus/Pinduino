/*
 * TLC5940.h
 *
 *  Created on: Jan 5, 2015
 *      Author: Dad
 */

#ifndef TLC5940_H_
#define TLC5940_H_

#include <Arduino.h>

#define ENABLE_MY_TLC

class TLC5940 {
public:
	TLC5940();
	virtual ~TLC5940();

	static void setup();
	static void setPixel(byte channel, int value);

private:
	static void DotCorrection();
};

#endif /* TLC5940_H_ */
