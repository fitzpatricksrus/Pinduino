#include "us/cownet/lamps/tests/PinballOutputControllerTest.h"
#include "us/cownet/lamps/wpc/WpcOutputController.h"
#include "us/cownet/lamps/simple/tests/SimpleLampMatrixTest.h"
#include "us/cownet/testing/Test.h"
#include "us/cownet/timers/Ticker.h"

#include <Debug.h>

using namespace us_cownet_testing;
using namespace us_cownet_timers;
using namespace us_cownet_lamps_tests;
using namespace us_cownet_lamps_wpc;

static byte dataOutputPins[] = { 22, 23, 24, 25, 26, 27, 28, 29 };
static byte signalOutputPins[] = { 52, 53 };

static WpcOutputController controller(dataOutputPins, signalOutputPins);
//static PinballOutputControllerTest test(&controller);
static SimpleLampMatrixTest test(&controller, 2L * 1000L / 4);

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
