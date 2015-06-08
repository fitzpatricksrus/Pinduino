#include "us/cownet/lamps/wpc/tests/WpcOutputControllerTest.h"
#include "us/cownet/lamps/simple/tests/SimpleLampMatrixTest.h"
#include "us/cownet/testing/Test.h"

#include <Debug.h>

using namespace us_cownet_testing;
using namespace us_cownet_lamps_wpc_tests;
using namespace us_cownet_lamps_tests;

static byte dataOutputPins[] = { 22, 23, 24, 25, 26, 27, 28, 29 };
static byte signalOutputPins[] = { 52, 53 };

static WpcOutputController controller(dataOutputPins, signalOutputPins);
//static WpcOutputControllerTest test(&controller);
static SimpleLampMatrixTest test(&controller, 2000L * 1000L);

static Test &currentTest = test;

static Ticker ticks(1000L * 1000L);
static unsigned long count;
void setup()
{
	count = 0;
	Serial.begin(57600);
	Serial << "setup()" << endl;
	currentTest.setup();
}

void loop()
{
	currentTest.loop();
	count++;
	if (ticks.isTime()) {
		Serial << "Frequency: " << count << endl;
		count = 0;
	}
}
