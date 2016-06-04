#include "RGB4Test.h"

//The setup function is called once at startup of the sketch
static byte data[] = {
//		255, 0, 255, 255, 255, 255, 255, 255,

		128, 1, 32, 4, 8, 2, 64, 255
};

static RGBTest4 testData(data, 8);

void setup()
{
	testData.setup();
}

// The loop function is called in an endless loop
void loop()
{
	testData.loop();
//	if (testData.cyclePosition == 0) {
//		for (int i = 0; i < 8; i++) {
//			data[i] = (data[i] + 1) % 256;
//		}
//	}
//Add your repeated code here
}
