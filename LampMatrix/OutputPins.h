/*
 * OutputPins.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#ifndef OUTPUTPINS_H_
#define OUTPUTPINS_H_

#include <Arduino.h>

class OutputPins {
public:
	virtual ~OutputPins() {}
    virtual bool getPin(byte pinNdx) const = 0;
    virtual bool operator[](byte pinNdx) const;
    virtual void setPin(byte pinNdx, bool value) = 0;
    virtual void setPins(bool* values);
    virtual void setAllPins(bool value);
    virtual byte getPinCount() const = 0;
    virtual void latch() = 0;

    void debug();
    virtual void debug(const char* pre, const char* post);
};

#endif /* OUTPUTPINS_H_ */
