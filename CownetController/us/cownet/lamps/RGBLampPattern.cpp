/*
 * RGBLampPattern.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: jfitzpatrick
 */

#include "RGBLampPattern.h"

namespace us_cownet_lamps {

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

byte RGBLampPattern::Color::getHue() {
    byte rgbMax = getValue();

    if (rgbMax == 0) {
        return 0;
    }

    byte rgbMin = R < G ? (R < B ? R : B) : (G < B ? G : B);

    byte s = 255 * ((long)(rgbMax - rgbMin)) / rgbMax;
    if (s == 0) {
        return 0;
    }

    if (rgbMax == R)
        return 0 + 43 * (G - B) / (rgbMax - rgbMin);
    else if (rgbMax == G)
        return 85 + 43 * (B - R) / (rgbMax - rgbMin);
    else
        return 171 + 43 * (R - G) / (rgbMax - rgbMin);
}

byte RGBLampPattern::Color::getSaturation() {
    byte rgbMax = getValue();

    if (rgbMax == 0) {
        return 0;
    }

    byte rgbMin = R < G ? (R < B ? R : B) : (G < B ? G : B);

    return 255 * ((long)(rgbMax - rgbMin)) / rgbMax;
}

byte RGBLampPattern::Color::getValue() {
    return R > G ? (R > B ? R : B) : (G > B ? G : B);
}

void RGBLampPattern::Color::setHSV(byte hue, byte saturation, byte value) {
    if (saturation == 0) {
        R = value;
        G = value;
        B = value;
    } else {
		// converting to 16 bit to prevent overflow
		unsigned int h = hue;
		unsigned int s = saturation;
		unsigned int v = value;

		byte region = h / 43;
		unsigned int remainder = (h - (region * 43)) * 6;

		byte p = (v * (255 - s)) >> 8;
		byte q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		byte t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

		switch (region) {
		case 0:
			R = v;
			G = t;
			B = p;
			break;
		case 1:
			R = q;
			G = v;
			B = p;
			break;
		case 2:
			R = p;
			G = v;
			B = t;
			break;
		case 3:
			R = p;
			G = q;
			B = v;
			break;
		case 4:
			R = t;
			G = p;
			B = v;
			break;
		default:
			R = v;
			G = p;
			B = q;
			break;
		}
    }
}

RGBLampPattern::RGBLampPattern() {
}

RGBLampPattern::~RGBLampPattern() {
}

void RGBLampPattern::attached() {
}

void RGBLampPattern::endOfMatrixSync() {
}

bool RGBLampPattern::isDone() {
	return true;
}

void RGBLampPattern::reset() {
}

void RGBLampPattern::detached() {
}

} /* namespace us_cownet_lamps */

/*

typedef struct RgbColor
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RgbColor;

typedef struct HsvColor
{
    unsigned char h;
    unsigned char s;
    unsigned char v;
} HsvColor;

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, p, q, t;
    unsigned int h, s, v, remainder;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    // converting to 16 bit to prevent overflow
    h = hsv.h;
    s = hsv.s;
    v = hsv.v;

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = v;
            rgb.g = t;
            rgb.b = p;
            break;
        case 1:
            rgb.r = q;
            rgb.g = v;
            rgb.b = p;
            break;
        case 2:
            rgb.r = p;
            rgb.g = v;
            rgb.b = t;
            break;
        case 3:
            rgb.r = p;
            rgb.g = q;
            rgb.b = v;
            break;
        case 4:
            rgb.r = t;
            rgb.g = p;
            rgb.b = v;
            break;
        default:
            rgb.r = v;
            rgb.g = p;
            rgb.b = q;
            break;
    }

    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * ((long)(rgbMax - rgbMin)) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}

 */
