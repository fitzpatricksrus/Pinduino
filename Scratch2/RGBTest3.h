/*
 * RGBTest3.h
 *
 *  Created on: Apr 2, 2016
 *      Author: Dad
 */

#ifndef RGBTEST3_H_
#define RGBTEST3_H_

#include <Arduino.h>

class RGBTest3 {
public:
	RGBTest3(byte* data, int dataCount = 8, int colCount = 8);
	virtual ~RGBTest3();

	void setup();
	void loop();

private:
	void writeData(byte values);
	void refreshOneComlumn(int col, byte value);
	void refreshOneComlumn();

	int position;
	int columnCount;
	int dataCount;
	byte* data;
};

#endif /* RGBTEST3_H_ */
