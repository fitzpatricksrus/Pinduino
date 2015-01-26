/*
 * LampMatrix.cpp
 *
 *  Created on: Jan 24, 2015
 *      Author: Dad
 */

#include <Arduino.h>
#include <Max7221.h>
#include "LampMatrix7221.h"

LampMatrix7221::LampMatrix7221()
: max7221(NULL)
{
}

LampMatrix7221::~LampMatrix7221() {
}

void LampMatrix7221::setColumn(byte column, byte values) {
	if (max7221 == NULL) {
		max7221 = new Max7221(10);
		max7221->init();
	}
	max7221->setColumn(column, values);
}
