#include "us/cownet/lamps/wpc/tests/WpcOutputControllerTest.h"
#include "us/cownet/testing/Test.h"

using namespace us_cownet_testing;
using namespace us_cownet_lamps_wpc_tests;

static byte dataOutputPins[] = { 22, 23, 24, 25, 26, 27, 28, 29 };
static byte signalOutputPins[] = { 52, 53 };

static WpcOutputController controller(dataOutputPins, signalOutputPins);
static WpcOutputControllerTest test(&controller);
//static SimpleLampMatrixTest test;

static Test &currentTest = test;


void setup()
{
	currentTest.setup();
}

void loop()
{
	currentTest.loop();
}
