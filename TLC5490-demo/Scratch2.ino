//Texas Instruments TLC 5940 with Arduino
//www.kevindarrah.com
//V7 Update - I did not test this yet, but the bitwise operation
//to set pins LOW was incorrect.  This code fixes that.
#include <Arduino.h>
//#include "SPI.h"//Serial Peripheral Interface Library
#include "../../libraries/SPI/SPI.h"
#include "TLC5940.h"

static int green, oldgreen = 2048; //for random animation
static int red, oldred = 2048; //for random animation
static int blue, oldblue = 2048; //for random animation
static int comeback = 0;
static int pick_color = 0; //for random animation

static const int NUM_CHANNELS = 32;

//#define columnOn(x) pinMode(x, OUTPUT); digitalWrite(x, LOW)
//#define columnOff(x) pinMode(x, INPUT)
//#define columnWrite(x, v) { if (v) { columnOn(x); } else { columnOff(x); } }
static void enableColumn(byte x) {
	digitalWrite(A0, (x & 01) ? HIGH : LOW);
	digitalWrite(A1, (x & 02) ? HIGH : LOW);
	digitalWrite(A2, (x & 04) ? HIGH : LOW);
}


//*******************************************************************************************

static int dc[8] = {
		0, 16, 56, 192, 512, 1024, 2048, 4095
};
static byte pixelStorage[8][48]; // bytes that are sent out to the tlc5940 via SPI
void setup() { //   MAIN SETUP   MAIN SETUP   MAIN SETUP   MAIN SETUP   MAIN SETUP
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	enableColumn(0);

	TLC5940::instance.setup();

	for (byte color = 0; color < 8; color++) {
		for (byte l = 0; l <= 24; l += 3) {
			TLC5940::setPixel(l, dc[(color+l)%8], &pixelStorage[color][0]);
		}
	}


//	Serial.begin(57600);

} // END OF SETUP END OF SETUP END OF SETUP END OF SETUP END OF SETUP END OF SETUP END OF SETUP

//*******************************************************************************************
void loop() { //   MAIN LOOP   MAIN LOOP   MAIN LOOP   MAIN LOOP   MAIN LOOP   MAIN LOOP

	//all_RED(4095);
	//all_GREEN(4095);
	//all_BLUE(4095);
//	lamp_test();
//	lamp_test2();
//	lamp_test3();
	lamp_test4();
	//random_animation();
	//random_animation2();
	//random_animation3();
	//random_animation4();
} //      loop close      loop close      loop close      loop close

//*******************************************************************************************
static void lamp_test() {  //           lamp_test
	for (int l = 0; l < NUM_CHANNELS; l++) {
		for (int k = 0; k < 4096; k++) {
			tlc(l, k);
			delayMicroseconds(250);
		}
		for (int k = 4095; k >= 0; k--) {
			tlc(l, k);
			delayMicroseconds(250);
		}
	}  //l
}  //lamp_test

static void lamp_test2() {
	all_RED(4095);
	all_GREEN(4095);
	all_BLUE(4095);
}

static void lamp_test3() {
	const byte step = 5;
	for (int l = 0; l <= 36; l = l + 1) {
		tlc(l, 0);
	}

	for (int i = 0; i < 8; i++) {
		enableColumn(i);
		for (int l = 0; l <= 24; l = l + 1) {
			tlc(l, 0);
		}
		for (int l = 0; l < 24; l = l + 1) {
			for (int duty = 0; duty < 4096; duty += step) {
				tlc(l, duty);
//				delayMicroseconds(100);
			}
			for (int duty = 0; duty < 4096; duty += step) {
				tlc(l, 4095 - duty);
//				delayMicroseconds(100);
			}
			tlc(l, 0);
		}
	}
}
static byte col = 0;
void nextRow() {
//	long time = millis();
	long time = micros() >> 11;
//	long time = col++;
	int col = time % 8;

	TLC5940::instance.setPixels(&pixelStorage[col][0]);
	enableColumn(col);
}  // cycle through columns

static void lamp_test4() {
	for (byte color = 0; color < 8; color++) {
		for (byte l = 0; l <= 24; l += 3) {
			TLC5940::setPixel(l, dc[(color+l)%8], &pixelStorage[color][0]);
//			TLC5940::instance.setPixel(l, (int)color*512);
		}
	}
//	TLC5940::instance.setPixels(&pixelStorage[0][0]);
	TLC5940::setCallback(nextRow);
}

static void all_RED(int duty) {  //      all red
	all_LIGHTS(duty, 1);
}  //allred
static void all_BLUE(int duty) {  //      all blue
	all_LIGHTS(duty, 2);
}  //allred
static void all_GREEN(int duty) {  //      all GREEN
	all_LIGHTS(duty, 0);
}  //allred

static void all_LIGHTS(int duty, byte color) {  //      all blue
	for (int k = 0; k < duty; k = k + 1)
		for (int l = color; l <= 36; l = l + 3)
			tlc(l, k);
	for (int k = duty - 1; k > 0; k = k - 1)
		for (int l = color; l <= 36; l = l + 3)
			tlc(l, k);

}  //allred


//*******************************************************************************************

static void random_animation3() {
  int swipe_Delay = 15000;
  for (uint16_t j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
	for (byte i=0; i < 24; i += 3) {
		  uint16_t WheelPos = (j + i) % 384;
		  byte r, g, b;
		  switch(WheelPos / 128)
		  {
		    case 0:
		      r = 127 - WheelPos % 128;   //Red down
		      g = WheelPos % 128;      // Green up
		      b = 0;                  //blue off
		      break;
		    case 1:
		      g = 127 - WheelPos % 128;  //green down
		      b = WheelPos % 128;      //blue up
		      r = 0;                  //red off
		      break;
		    case 2:
		      b = 127 - WheelPos % 128;  //blue down
		      r = WheelPos % 128;      //red up
		      g = 0;                  //green off
		      break;
		  }
		  tlc(i, r);
		  tlc(i+1, g);
		  tlc(i+2, b);
	}
	delayMicroseconds(swipe_Delay);
  }
}

static void random_animation4() {
  int swipe_Delay = 15000;
  for (uint16_t j=0; j < 384; j++) {     // 3 cycles of all 384 colors in the wheel
	for (byte i=0; i < 24; i += 3) {
		  uint16_t WheelPos = (j + i) % 384;
		  byte r, g, b;
		  switch(WheelPos / 128)
		  {
		    case 0:
		      r = 127 - WheelPos % 128;   //Red down
		      g = WheelPos % 128;      // Green up
		      b = 0;                  //blue off
		      break;
		    case 1:
		      g = 127 - WheelPos % 128;  //green down
		      b = WheelPos % 128;      //blue up
		      r = 0;                  //red off
		      break;
		    case 2:
		      b = 127 - WheelPos % 128;  //blue down
		      r = WheelPos % 128;      //red up
		      g = 0;                  //green off
		      break;
		  }
		  tlc(i, r);
		  tlc(i+1, g);
		  tlc(i+2, b);
	}
	delayMicroseconds(swipe_Delay);
  }
}

static int rgb[3] = { 0,0,0 };
static void random_animation2() {
	int speed_swipe = 1;  //random(1, 200);
	int swipe_Delay = 60;

	byte color = random(0, 3);
	int pick_max = random(0, 4096);
	int value = random(0, pick_max);

	while (abs(rgb[color]-value) < 100) {
		value = random(0, pick_max);
	}

	if (value > rgb[color]) {
		for (int k = rgb[color]; k <= value; k = k + speed_swipe) {
			for (int l = 0; l < NUM_CHANNELS; l = l + 3) {
				tlc(l+color, k);  //R
			}
			delayMicroseconds(swipe_Delay); // was commented out.
		}       //for
	}       //>oldred
	else if (value < rgb[color]) {
		for (int k = rgb[color]; k >= value; k = k - speed_swipe) {
			for (int l = 0; l < NUM_CHANNELS; l = l + 3) {
				tlc(l+color, k);       //R
			}
			delayMicroseconds(swipe_Delay);
		}       //for
	}       //>oldred
	rgb[color] = value;
}

static void random_animation() { //  random animation  random animation  random animation

	pick_color++;
	int speed_swipe = 1;  //random(1, 200);
	int swipe_Delay = 2;

	if (pick_color > 3) {
		pick_color = 1;
	}

	int pick_max = random(100, 4096);
	//int pick_max = 3000;

	if (pick_color == 1) {
		while (abs(oldred-red) < 100) {
			red = random(0, pick_max);
		}
	}
	if (pick_color == 2) {
		while (abs(oldblue-blue) < 100) {
			blue = random(0, pick_max);
		}
	}
	if (pick_color == 3) {
		while (abs(oldgreen-green) < 100) {
			green = random(0, pick_max);
		}
	}

//	delay(100);

	if (comeback == 0)
		for (int l = 1; l <= 28; l = l + 3) {
			if (pick_color == 1) {
				if (red > oldred) {
					for (int k = oldred; k <= red; k = k + speed_swipe) {
						tlc(l, k);  //R
						delayMicroseconds(swipe_Delay); // was commented out.
					}       //for
				}       //>oldred
				else if (red < oldred) {
					for (int k = oldred; k >= red; k = k - speed_swipe) {
						tlc(l, k);       //R
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldred
			}       //pick

			if (pick_color == 2) {
				if (blue > oldblue) {
					for (int k = oldblue; k <= blue; k = k + speed_swipe) {
						tlc(l + 1, k);       //B
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldblue
				else if (blue < oldblue) {
					for (int k = oldblue; k >= blue; k = k - speed_swipe) {
						tlc(l + 1, k);       //B
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldblue
			}       //pick

			if (pick_color == 3) {
				if (green > oldgreen) {
					for (int k = oldgreen; k <= green; k = k + speed_swipe) {
						tlc(l + 2, k);       //G
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldgreen
				else if (green < oldgreen) {
					for (int k = oldgreen; k >= green; k = k - speed_swipe) {
						tlc(l + 2, k);       //G
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldgreen
			}       //pick
			comeback = 1;
		}       //l channel
	else
		for (int l = 28; l >= 1; l = l - 3) {       //         2nd sweep
			if (pick_color == 1) {
				if (red > oldred) {
					for (int k = oldred; k <= red; k = k + speed_swipe) {
						tlc(l, k);       //R
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldred
				else if (red < oldred) {
					for (int k = oldred; k >= red; k = k - speed_swipe) {
						tlc(l, k);       //R
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldred
			}       //pick

			if (pick_color == 2) {
				if (blue > oldblue) {
					for (int k = oldblue; k <= blue; k = k + speed_swipe) {
						tlc(l + 1, k);       //B
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldblue
				else if (blue < oldblue) {
					for (int k = oldblue; k >= blue; k = k - speed_swipe) {
						tlc(l + 1, k);       //B
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldblue
			}       //pick

			if (pick_color == 3) {
				if (green > oldgreen) {
					for (int k = oldgreen; k <= green; k = k + speed_swipe) {
						tlc(l + 2, k);       //G
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldgreen
				else if (green < oldgreen) {
					for (int k = oldgreen; k >= green; k = k - speed_swipe) {
						tlc(l + 2, k);       //G
						delayMicroseconds(swipe_Delay);
					}       //for
				}       //>oldgreen
			}       //pick
			comeback = 0;
		}       //l channel 2nd

	oldgreen = green;
	oldblue = blue;
	oldred = red;

}

//  random animation end  random animation end  random animation end  random animation end
//*******************************************************************************************
static void tlc(int channel, int value) { // TLC to UPDATE TLC to UPDATE TLC to UPDATE TLC to UPDATE
	TLC5940::instance.setPixel(channel, value);
} //  END OF TLC WRITE  END OF TLC WRITE  END OF TLC WRITE  END OF TLC WRITE  END OF TLC WRITE

