//**************************************************************//
//  Name    : shiftOutCode, Hello World
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis
//  Date    : 25 Oct, 2006
//  Modified: 23 Mar 2010
//  Version : 2.0
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255
//****************************************************************

#include <Arduino.h>

#define USE_SPI
#ifdef USE_SPI
#include "SPI.h"

#endif


int SSPin = 10;
int SCKPin = 13;
// int MISOPin = 12;
int MOSIPin = 11;
int MRPin = 2;
int OEPin = 5;


//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

/*
 * 1. Connect SCK (SCKPin #13) to SRCK (SHCP #11) (shift register clock)
 * 2. Connect MOSI (MOSIPin #11) to serial data in (DS #14).
 * 3. Connect SS (SSPin #10) to RCK (output register clock) (STCP #12)
 */

void setup() {
  //set pins to output so you can control the shift register
	  pinMode(SSPin, OUTPUT);
	  pinMode(SCKPin, OUTPUT);
	  pinMode(MOSIPin, OUTPUT);
	  Serial.begin(9600);

#ifdef USE_SPI
  SPI.begin();
//  SPI.setDataMode(SPI_MODE0);
//  SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV128);
//    SPI.setClockDivider(SPI_CLOCK_DIV2);
#endif
}

long count = 0;
long lastStart = 0;
void loop() {
  //count up routine
  for (int j = 0; j <256; j++) {
	for (int i = 0; i < 256; i++) {

		digitalWrite(SSPin, LOW);
//		delay(10);
#ifdef USE_SPI
		SPI.transfer(0);
		SPI.transfer(j);
		SPI.transfer(i);
#else
		//ground latchPin and hold low for as long as you are transmitting
		shiftOut(MOSIPin, SCKPin, MSBFIRST, 0);
		//count up on GREEN LEDs
		shiftOut(MOSIPin, SCKPin, MSBFIRST, j);
		//count down on RED LEDs
		shiftOut(MOSIPin, SCKPin, MSBFIRST, i);
		//return the latch pin high to signal chip that it
		//no longer needs to listen for information
#endif
		digitalWrite(SSPin, HIGH);
		//Serial.print("("); Serial.print(i);Serial.print(",");Serial.print(j);Serial.println(")");

		count++;
		if (millis() - lastStart > 2000) {
			Serial.println(count/2);
			count = 0;
			lastStart = millis();
		}
		delay(40);
	}
  }
}
