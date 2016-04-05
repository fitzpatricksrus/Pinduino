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
	RGBTest4(byte* data, int colCount = 8, int greyBits = 4);
	virtual ~RGBTest4();

	void setup();
	void loop();

private:
	void refreshOneRGBColumn(int col, byte* values);
	void refreshOneRGBComlumn();

	int cycleSize;
	int position;

	byte* data;
	int columnCount;
	int greyBits;
};

#endif /* RGB4TEST_H_ */
