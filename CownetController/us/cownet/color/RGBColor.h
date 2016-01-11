/*
 * RGBColor.h
 *
 *  Created on: Dec 24, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_COLOR_RGBCOLOR_H_
#define US_COWNET_COLOR_RGBCOLOR_H_

#include <arduino.h>

namespace us_cownet_color {

class RGBColor {
public:
	RGBColor();
	RGBColor(bool onOff);
	RGBColor(int greyValue);
	RGBColor(const RGBColor& other);
	~RGBColor();

	RGBColor& operator=(const RGBColor& other);

	bool asBoolean();
	byte asGreyscale();

	byte r;
	byte g;
	byte b;
};

inline RGBColor::RGBColor()
: r(0), g(0), b(0) {
}

inline RGBColor::RGBColor(const RGBColor& other)
: r(other.r), g(other.g), b(other.b) {
}

inline RGBColor::~RGBColor() {
}

inline RGBColor::RGBColor(bool onOff) {
	if (onOff) {
		r = 255;
		g = 255;
		b = 255;
	} else {
		r = 0;
		g = 0;
		b = 0;
	}
}

inline RGBColor::RGBColor(int greyValue) {
	r = greyValue;
	g = greyValue;
	b = greyValue;
}

inline RGBColor& RGBColor::operator=(const RGBColor& other) {
	r = other.r;
	g = other.g;
	b = other.b;
	return *this;
}

inline bool RGBColor::asBoolean() {
	return 0 < (r + g + b);
}

inline byte RGBColor::asGreyscale() {
	// the real formula is 0.2989R+0.5870G+.1140B
	// quick and dirty, slightly dark is  0.25R + 0.5G + 0.25B

	//going with (3R + 6G + B) / 10

	return ((int)(3*r + 6*g + b)) / 10;
}

} /* namespace us_cownet_color */

#endif /* US_COWNET_COLOR_RGBCOLOR_H_ */
