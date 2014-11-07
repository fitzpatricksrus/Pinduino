/*
 * SPIOutputPins.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_SPIOUTPUTPINS_H_
#define SCRATCHPINS_SPIOUTPUTPINS_H_

#include "OutputPins.h"

namespace pins {

class SPIOutputPins : public OutputPins {
public:
	SPIOutputPins(byte valueCount, byte slaveSelectPin_ST_CP = 10);
	virtual ~SPIOutputPins();
	virtual void initPins() const;
    virtual void setPinPattern(PinPattern* pattern);
    virtual void latch();

    SPIOutputPins& slaveSelectPin(byte pinNumber);
    byte getSlavePin() const;

private:
    byte valueCount;
    byte encodedByteCount;
    byte* encodedBytes;
    byte SSPin;
};

} /* namespace pins */

#endif /* SCRATCHPINS_SPIOUTPUTPINS_H_ */
