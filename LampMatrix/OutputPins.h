/*
 * OutputPins.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#ifndef OUTPUTPINS_H_
#define OUTPUTPINS_H_

#include <Arduino.h>

/*
 * A set of pins with particular values.  Pin values
 * are cached and only sent to the output pins
 * when latch() is called.  Subclasses should optimize
 * for latch() speed rather than pin update speed.
 */
class OutputPins {
public:
	OutputPins();
	virtual ~OutputPins() {}
	virtual void initPins() const = 0;
    virtual bool getPin(byte pinNdx) const = 0;
    bool operator[](byte pinNdx) const;
    virtual void setPin(byte pinNdx, bool value) = 0;
    virtual void setPins(bool* values);
    virtual void setAllPins(long value);
    virtual byte getPinCount() const = 0;
    virtual void latch() = 0;
    bool getAutoLatch() const;
    void setAutoLatch(bool latchOnEveryChange);

    void debug();
    virtual void debug(const char* pre, const char* post);

private:
    bool autoLatch;
};

inline bool OutputPins::operator[](byte pinNdx) const {
	return getPin(pinNdx);
}

inline bool OutputPins::getAutoLatch() const {
	return autoLatch;
}

inline void OutputPins::setAutoLatch(bool latchOnEveryChange) {
	autoLatch = latchOnEveryChange;
}



#endif /* OUTPUTPINS_H_ */
