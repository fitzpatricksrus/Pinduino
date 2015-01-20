/*
 * StringStream.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: Dad
 */

#include "StringStream.h"

StringStream::StringStream(char* buf, byte len)
: buffer(buf), length(len), pos(0)
{
}

StringStream::~StringStream() {
}

void StringStream::skipSpaces() {
  while (peek() == ' ') {
    pos++;
  }
}

int StringStream::available() {
	return length - pos;
}

int StringStream::read() {
	if (available()) {
		return buffer[pos++];
	} else {
		return -1;
	}
}

int StringStream::peek() {
	if (available()) {
		return buffer[pos];
	} else {
		return -1;
	}
}

void StringStream::flush() {
}

size_t StringStream::write(uint8_t) {
	return -1;
}

void StringStream::setInput(char* buf, byte len) {
	buffer = buf;
	length = len;
	pos = 0;
}


