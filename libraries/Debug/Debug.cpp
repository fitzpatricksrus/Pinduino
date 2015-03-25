/*
 * Debug.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: Dad
 */

#include "Debug.h"
#include <Arduino.h>

namespace Tests {

DebugCounter::DebugCounter()
: count(0), lastPrint(0) {

}

void DebugCounter::ping() {
	count++;
}

void DebugCounter::print(Print &obj) {
	if (millis() - lastPrint > 1000) {
		obj.print(count);
		count = 0;
		lastPrint = millis();
	}
}

DebugCounter::operator bool() {
	return millis() - lastPrint > 1000;
}

int DebugScopeImpl::nesting = 0;
bool DebugScopeImpl::needsIndent = true;

void DebugScopeImpl::indent() {
	if (needsIndent) {
		for (int i = 0; i < nesting; i++) {
			if (Serial) Serial.print(F("    "));
		}
		needsIndent = false;
	}
}

void DebugScopeImpl::print(const char* msg) {
	indent();
	if (Serial) Serial.print(msg);
}

void DebugScopeImpl::println(const char* msg) {
	indent();
	if (Serial) Serial.println(msg);
	needsIndent = true;
}

void DebugScopeImpl::print(const __FlashStringHelper* messageIn) {
	indent();
	if (Serial) Serial.print(messageIn);
}

void DebugScopeImpl::println(const __FlashStringHelper* messageIn) {
	indent();
	if (Serial) Serial.println(messageIn);
	needsIndent = true;
}

DebugScopeImpl::DebugScopeImpl(const char* messageIn)
: message(messageIn), fMessage(0) {
	print(F(">"));
	println(message);
	nesting++;
}

DebugScopeImpl::DebugScopeImpl(const __FlashStringHelper* messageIn)
: message(0), fMessage(messageIn)
{
	print(F(">"));
	println(fMessage);
	nesting++;
}


DebugScopeImpl::~DebugScopeImpl() {
	nesting--;
	print(F("<"));
	if (message == 0) {
		println(fMessage);
	} else {
		println(message);
	}
}

} /* namespace Tests */



extern unsigned int __heap_start;
extern void *__brkval;

/*
 * The free list structure as maintained by the
 * avr-libc memory allocation routines.
 */
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

/* Calculates the size of the free list */
int freeListSize() {
  struct __freelist* current;
  int total = 0;
  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (int) current->sz;
  }
  return total;
}


int availableMemory() {
  int free_memory;
  if ((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__heap_start);
  } else {
    free_memory = ((int)&free_memory) - ((int)__brkval);
    free_memory += freeListSize();
  }
  return free_memory;
}

int availableRam () {
//  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

bool interruptsAreEnabled() {
    if (bit_is_clear(SREG, SREG_I)) {
    	return false;
    } else {
    	return true;
    }
}

size_t DebugSerial::write(uint8_t c) {
	buffer[pos++] = c;
	return 1;
}

byte DebugSerial::getContents(char* buf) {
	byte bufPos = 0;
	while (start != pos) {
		buf[bufPos++] = buffer[start++];
	}
	buf[bufPos++] = '\0';
	return bufPos;
}

static DebugSerial DEBUG_SERIAL_INSTANCE;
DebugSerial& DebugSerial::INSTANCE = DEBUG_SERIAL_INSTANCE;

char DebugSerial::strings[16][5] = {
		"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
		"1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
};
