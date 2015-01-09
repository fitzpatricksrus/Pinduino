/*
 * TLC5940.cpp
 *
 *  Created on: Jan 5, 2015
 *      Author: Dad
 */

#include "TLC5940.h"
#include "SPI.h"

static const byte XLAT_PIN = 2;  //XLAT
static const byte GSCLK_PIN = 3;  //OSC2B GSCLK
static const byte VPRG_PIN = 4;  //VPRG
static const byte BLANK_PIN = 5;  //VPRG


static byte pixelStorage[48]; // bytes that are sent out to the tlc5940 via SPI
static byte* transferbyte = pixelStorage;
static byte DCvalue[32];  //0-63, 6 bit DOT Correction Bytes
static TLC5940::Callback callback = 0;

#ifdef ENABLE_MY_TLC
//ISR(TIMER1_OVF_vect){}// Over Limit Flag Interrupt  you need this even if you don't use it
//ISR(TIMER1_COMPB_vect) {
//}  // Compare B - Not Used
ISR(TIMER1_COMPA_vect) { // Interrupt to count 4096 Pulses on GSLCK
	PORTD |= 1 << BLANK_PIN; // write blank HIGH to reset the 4096 counter in the TLC
	PORTD |= 1 << XLAT_PIN; // write XLAT HIGH to latch in data from the last data stream
	PORTD &= ~(1 << XLAT_PIN);  //XLAT can go low now
	PORTD &= ~(1 << BLANK_PIN);  //Blank goes LOW to start the next cycle
	SPI.end();  //end the SPI so we can write to the clock pin
	PORTB |= 1 << BLANK_PIN;  // SPI Clock pin to give it the extra count
	PORTB &= ~(1 << BLANK_PIN);  // The data sheet says you need this for some reason?
	SPI.begin();  // start the SPI back up
	for (int SINData = 47; SINData >= 0; SINData--)  // send the data out!
		SPI.transfer(transferbyte[SINData]); // The SPI port only understands bytes-8 bits wide
	// The TLC needs 12 bits for each channel, so 12bits times 32 channels gives 384 bits
	// 384/8=48 bytes, 0-47
	if (callback != 0) {
		(*callback)();
	}
}
#endif

static TLC5940 instance_instance;
TLC5940& TLC5940::instance = instance_instance;

void TLC5940::setCallback(Callback callbackIn) {
	callback = callbackIn;
}

TLC5940::TLC5940() {
	callback = 0;
}

TLC5940::~TLC5940() {
}

void TLC5940::setup() {
	pinMode(XLAT_PIN, OUTPUT);  //XLAT
	pinMode(GSCLK_PIN, OUTPUT);  //OSC2B GSCLK
	pinMode(VPRG_PIN, OUTPUT);  //VPRG
	pinMode(11, OUTPUT);  //MOSI DATA
	pinMode(13, OUTPUT);  //SPI Clock

	//Set up the SPI
	SPI.setBitOrder(MSBFIRST);  //Most Significant Bit First
	SPI.setDataMode(SPI_MODE0);  // Mode 0 Rising edge of data, keep clock low
	SPI.setClockDivider(SPI_CLOCK_DIV2);  //Run the data in at 16MHz/4 - 4MHz

	for (byte i = 0; i < 48; i++)  //clear out Gray Scale Data
		transferbyte[i] = 0;

	for (byte i = 0; i < 32; i++) //set Dot Correction data to max (63 decimal for 6 bit)
		DCvalue[i] = 63;

	//set up DOT Correction
	DotCorrection();  // sub routine helps

	noInterrupts();
	// set up the counters, so don't go into interrupts
	TCCR2A = B00010010; //Timer 2 set to Compare Mode Toggling pin 5 @ 8MHz, Arduino Digital 3
	// TIMER 2 IS GSCLCK
	//Timer 2 prescaler set to 1, 16/1=16 MHz, but toggles pin 5 every other cycle, 8MHz
	TCCR2B = B00000001;

	TCCR1A = B00000000;  //Timer 1 doesn't toggle anything, used for counting
	//Timer 1 prescaler set to Fclk/256
	//Why? We need to count 4096 pulses out of Timer 2 - pin 5
	//8 MHz = 1 pulse every 125ns - - 4096 pulses would need 512us
	//Timer 1 runs at 16MHz/256=62.5kHz, we need a match at every 512us
	//Basically, I can get an interrupt to get called every 512us, so...
	// I need to run Timer 2 @ 8MHz for 512us to get 4096 pulses
	// I can't count those pulses directy (too fast) , so
	// I'll count using Timer 1, which makes a count every 16us
	// The counter starts at 0, so we'll set it to 31 to get an interrupt after 512us
	TCCR1B = B00001100;  //Mode=CTC with OSCR1A = TOP and 256 as the prescaler
	// Mask set up, will call ISR (Inerrupt Service Routine) for Compare match on A
	TIMSK1 = B00000010;
	//These are the match values for the counters
	// 0 here means it will match on one cycle of the clock/prescaler
	OCR1A = 31;  //to get our 512us Interrupt
	interrupts();
	// kick off the timers!
	for (byte i = 0; i < 32; i++)  //wipe out the data in tlc
		setPixel(i, 0); // This is how you update the LEDs, tlc is a subroutine with two inputs
	// tlc(Channel, Value)  Channel in this case is 0-32 and value is 0-4095 duty cycle
	//4095 is 100% ON
	pinMode(BLANK_PIN, OUTPUT); //BLANK  We set this pin up here, so it remains in a high impedance
	// state throughout the setup, otherwise the LEDs go crazy!  even if you write this HIGH
}

void TLC5940::setPixel(byte channel, int value, byte* storage) {
	// This routine needs to happen as fast as possible!!!
	//Limit check
		if (value > 4095) {
			value = 4095;
		}
		if (value < 0) {
			value = 0;
		}

		// We need to convert the 12 bit value into an 8 bit BYTE, the SPI can't write 12bits

		//We figure out where in all of the bytes to write to, so we don't have to waste time
		// updating everything

		//12 bits into bytes, a start of 12 bits will either at 0 or 4 in a byte
		byte spibit = 0;
		if (bitRead(channel, 0)) { //if the read of the value is ODD, the start is at a 4
			spibit = 4;
		}

		//This is a simplification of channel * 12 bits / 8 bits
		byte spibyte = int(channel * 3 / 2); //this assigns which byte the 12 bit value starts in

		for (byte chbit = 0; chbit < 12; chbit++, spibit++) { // start right at where the update will go
			if (spibit == 8) { //during the 12 bit cycle, the limit of byte will be reached
				spibyte++;   //roll into the next byte
				spibit = 0;   //reset the bit count in the byte
			}
			if (bitRead(value, chbit)) {  //check the value for 1's and 0's
				bitSet(storage[spibyte], spibit);
			} else {
				bitClear(storage[spibyte], spibit);
			}
		}   //0-12 bit loop
}

void TLC5940::setPixel(byte channel, int value) {
	setPixel(channel, value, transferbyte);
}

void TLC5940::setPixels(byte* pixelStorageIn) {
	if (pixelStorageIn != 0) {
		transferbyte = pixelStorageIn;
	} else {
		transferbyte = pixelStorage;
	}
}

void TLC5940::DotCorrection() {
	PORTD |= 1 << VPRG_PIN;  //VPRG to DC Mode HIGH
	byte spibyte = 0;  //reset our variables
	byte spibit = 0;
	for (byte ch = 0; ch < 32; ch++) {  // 6 bit a piece x 32 Outputs
		for (byte chbit = 0; chbit < 6; chbit++) {
			if (spibit == 8) {
				spibyte++;
				spibit = 0;
			}
			if (bitRead(DCvalue[ch], chbit))  //all 6 bits
				bitSet(transferbyte[spibyte], spibit); //setting bit 7 of transfer byte
			else
				bitClear(transferbyte[spibyte], spibit);
			spibit++;
		}  //i
	}  //j
	SPI.begin();
	for (int j = spibyte; j >= 0; j--) {
		SPI.transfer(transferbyte[j]);
	}
	PORTD |= 1 << XLAT_PIN;  //XLAT the data in
	PORTD &= ~(1 << XLAT_PIN);  //XLAT data is in now
	PORTD &= ~(1 << VPRG_PIN);  //VPRG is good to go into normal mode LOW
}

