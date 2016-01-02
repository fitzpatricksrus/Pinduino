/*
 * HSVColor.h
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_COLOR_HSVCOLOR_H_
#define US_COWNET_COLOR_HSVCOLOR_H_

#include <arduino.h>

namespace us_cownet_color {

class RGBColor;

class HSVColor {
public:
	/// Pre-defined hue values for HSV objects
	typedef enum {
	    HUE_RED = 0,
	    HUE_ORANGE = 32,
	    HUE_YELLOW = 64,
	    HUE_GREEN = 96,
	    HUE_AQUA = 128,
	    HUE_BLUE = 160,
	    HUE_PURPLE = 192,
	    HUE_PINK = 224
	} HSVHue;

	inline ~HSVColor() {};

	inline HSVColor()
	: h(0), s(0), v(0)
	{
	}

	inline HSVColor( byte ih, byte is, byte iv)
	: h(ih), s(is), v(iv)
	{
	}

	inline HSVColor(const HSVColor& rhs)
	: h(rhs.h), s(rhs.s), v(rhs.v)
	{
	}

	inline HSVColor(const RGBColor& other)
	: h(0), s(0), v(0)
	{
	}

	inline HSVColor& operator= (const HSVColor& rhs)
	{
		h = rhs.h;
		s = rhs.s;
		v = rhs.v;
		return *this;
	}

	inline HSVColor& setHSV(byte ih, byte is, byte iv)
	{
		h = ih;
		s = is;
		v = iv;
		return *this;
	}

	union {
		struct {
			union {
				byte hue;
				byte h; };
			union {
				byte saturation;
				byte sat;
				byte s; };
			union {
				byte value;
				byte val;
				byte v; };
		};
		byte raw[3];
	};
};

} /* namespace us_cownet_color */

#endif /* US_COWNET_COLOR_HSVCOLOR_H_ */
