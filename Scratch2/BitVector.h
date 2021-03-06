/*
 * BitVector.h
 *
 *  Created on: Apr 2, 2016
 *      Author: Dad
 */

#ifndef BITVECTOR_H_
#define BITVECTOR_H_

#include <Arduino.h>

class BitVector {
private:
	static const int mask[];
public:
	BitVector(byte valueIn) : value(valueIn) {}
	bool operator[](int ndx) {
		return value & mask[ndx];
	}
	int size() {
		return 8;
	}
	void set(int ndx, bool valueIn) {
		if (valueIn) {
			value |= mask[ndx];
		} else {
			value &= ~mask[ndx];
		}
	}

private:
	byte value;
};

#endif /* BITVECTOR_H_ */
