/*
 * RGB4Test.h
 *
 *  Created on: Apr 3, 2016
 *      Author: Dad
 */

#ifndef RGB4TEST_H_
#define RGB4TEST_H_


#include <Arduino.h>

class RGBTest4 {
public:
	RGBTest4(byte* data, int dataSize = 64);
	virtual ~RGBTest4();

	void setup();
	void loop();

private:
	void refreshOneRGBColumn(int mask, int col, byte* values);
	void refreshOneRGBColumn();

	int cyclePosition;
	int columnPosition;

	byte* data;
	int dataSize;
};

#endif /* RGB4TEST_H_ */
