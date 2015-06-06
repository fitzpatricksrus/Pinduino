#include "us/cownet/lamps/wpc/tests/WpcOutputControllerTest.h"
#include "us/cownet/testing/Test.h"

using namespace us_cownet_testing;
using namespace us_cownet_lamps_wpc_tests;

static WpcOutputControllerTest test;
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
