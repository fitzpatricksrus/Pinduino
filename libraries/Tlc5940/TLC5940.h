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
	typedef void (*Callback)();

	TLC5940();
	virtual ~TLC5940();

	void setup();
	static void setCallback(Callback callback);
	static void setPixel(byte channel, int value, byte* storage);
	void setPixel(byte channel, int value);
	void setPixels(byte* pixelStorage);

	static TLC5940& instance;


private:
	void DotCorrection();
};

#endif /* TLC5940_H_ */
