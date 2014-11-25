/*
 * BitUtils.h
 *
 *  Created on: Nov 25, 2014
 *      Author: jfitzpatrick
 */

#ifndef BITUTILS_H_
#define BITUTILS_H_

#include <Arduino.h>
namespace utils {

class BitUtils {
public:
	static void compressBits(byte bitCount, bool* bitsIn, byte* bytesOut);
	static void decompressBits(byte bitCount, byte* bytesIn, bool* bitsOut);

	static bool read(byte bite, byte bit);
	static byte set(byte bite, byte bit);
	static byte clear(byte bite, byte bit);
	static byte write(byte bite, byte bit, bool value);

private:
	static byte masks[8];
	static byte notMasks[8];
};



inline bool BitUtils::read(byte bite, byte bit) {
	return bite & masks[bit];
}

inline byte BitUtils::set(byte bite, byte bit) {
	return bite | masks[bit];
}

inline byte BitUtils::clear(byte bite, byte bit) {
	return bite & notMasks[bit];
}

inline byte BitUtils::write(byte bite, byte bit, bool value) {
	if (value) {
		return set(bite, bit);
	} else {
		return clear(bite, bit);
	}
}

} //namespace

#endif /* BITUTILS_H_ */
