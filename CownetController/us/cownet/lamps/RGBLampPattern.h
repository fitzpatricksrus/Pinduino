/*
 * RGBLampPattern.h
 *
 *  Created on: Nov 18, 2015
 *      Author: jfitzpatrick
 */

#ifndef RGBLAMPPATTERN_H_
#define RGBLAMPPATTERN_H_

#include <Arduino.h>

namespace us_cownet_lamps {

class RGBLampPattern {
public:

	class Color {
	public:
		Color() : R(0), G(0), B(0) {}
		Color(const Color& other) : R(other.R), G(other.G), B(other.B) {}
		Color(Color&& other) : R(other.R), G(other.G), B(other.B) {}
		Color(byte r, byte g, byte b) : R(r), G(g), B(b) {}
		Color& operator=(const Color& other) {
			if (&other != this) {
				R = other.R;
				G = other.G;
				B = other.B;
			}
			return *this;
		}

		byte getHue();
		byte getSaturation();
		byte getValue();
		void setHSV(byte hue, byte saturation, byte value);

		byte R, G, B;
	};

	RGBLampPattern();
	virtual ~RGBLampPattern();

	virtual void attached();

	virtual int getLampCount() = 0;

	virtual Color getLamp(int index) = 0;

	virtual void endOfMatrixSync();

	virtual void detached();

	/*
	 Used only by pattern containers.  isDone() should return true when the
	 pattern has displayed its entire state sequence once.  This has no affect
	 on the lamp matrix, which will continue to cycle through columns.  Containers
	 can decide how to proceed and may reset() the pattern, replace it, or
	 continue to refresh the matrix with it.
	 */
	virtual bool isDone();

	/*
	 Start the refresh sequence from the beginning.
	 */
	virtual void reset();

//	template <int size>
//	void setBuffer(int (&newBuffer)[size]);
};

} /* namespace us_cownet_lamps */

#endif /* RGBLAMPPATTERN_H_ */
