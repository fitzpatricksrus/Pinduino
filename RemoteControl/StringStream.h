/*
 * StringStream.h
 *
 *  Created on: Jan 19, 2015
 *      Author: Dad
 */

#ifndef STRINGSTREAM_H_
#define STRINGSTREAM_H_

#include <Arduino.h>
#include <Stream.h>

class StringStream : public Stream {
public:
	StringStream(char* buffer, byte length);
	virtual ~StringStream();

	void setInput(char* buffer, byte length);
    void skipSpaces();

	virtual int available();
	virtual int read();
	virtual int peek();
	virtual void flush();

    virtual size_t write(uint8_t);

private:
	char* buffer;
	byte length;
	byte pos;
};

#endif /* STRINGSTREAM_H_ */
