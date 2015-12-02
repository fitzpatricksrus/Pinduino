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
	};

	class RGB : public Color {
	public:
		RGB() : R(0), G(0), B(0) {}
		RGB(const RGB& other) : R(other.R), G(other.G), B(other.B) {}
		RGB(RGB&& other) : R(other.R), G(other.G), B(other.B) {}
		RGB(byte r, byte g, byte b) : R(r), G(g), B(b) {}
		RGB& operator=(const RGB& other) {
			if (other != *this) {
				R = other.R;
				G = other.G;
				B = other.B;
			}
			return *this;
		}

		RGB(const Color& other) : R(0), G(0), B(0) { toRGB(other); }

		byte R, G, B;

	private:
		void toRGB(const Color& other);
	};

	class HSV : public Color {
	public:
		HSV() : H(0), S(0), V(0) {}
		HSV(const HSV& other) : H(other.H), S(other.S), V(other.V) {}
		HSV(HSV&& other) : H(other.H), S(other.S), V(other.V) {}
		HSV(byte r, byte g, byte b) : H(r), S(g), V(b) {}
		HSV& operator=(const HSV& other) {
			if (other != *this) {
				H = other.H;
				S = other.S;
				V = other.V;
			}
			return *this;
		}

		HSV(const Color& other) : H(0), S(0), V(0) { toHSV(other); }

		byte H, S, V;
	private:
		void toHSV(const Color& other);
	};

	RGBLampPattern();
	virtual ~RGBLampPattern();

	virtual void attached();

	virtual int getLampCount() = 0;

	virtual void getLamp(int index, Color& lampColor) = 0;

	virtual RGB getLampRGB(int index) = 0;

	virtual HSV getLampHSV(int index) = 0;

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
