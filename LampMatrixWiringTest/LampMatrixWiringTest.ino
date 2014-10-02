#include <Arduino.h>

//-------------------------------------------------
// The actual output pins we will use
static int xROW_PIN_NUMBERS[] = { 2,3,4,5,6,7,8, -1  };
static int xCOL_PIN_NUMBERS[] = { 9,12,10,11,13, -1 };
static int ROW_PIN_NUMBERS[] = { 3,4, -1  };
static int COL_PIN_NUMBERS[] = { 5,6, -1 };


//-------------------------------------------------

void setup() {
   Serial.begin(115200);
   for (int i = 0; COL_PIN_NUMBERS[i] >= 0; i++ ) {
     pinMode(COL_PIN_NUMBERS[i], OUTPUT);
     digitalWrite(COL_PIN_NUMBERS[i], LOW);
   }
   for (int i = 0; ROW_PIN_NUMBERS[i] >= 0; i++ ) {
     pinMode(ROW_PIN_NUMBERS[i], OUTPUT);
     digitalWrite(ROW_PIN_NUMBERS[i], LOW);
   }
}


static unsigned long lastRefreshTime = 0;
static const unsigned int REFRESH_DELAY = 1000;
void loop() {
  unsigned long now = millis();
  if (now - lastRefreshTime >= REFRESH_DELAY) {
   for (int col = 0; COL_PIN_NUMBERS[col] >= 0; col++ ) {
     for (int row = 0; ROW_PIN_NUMBERS[row] >= 0; row++ ) {
       digitalWrite(ROW_PIN_NUMBERS[row], HIGH);
       digitalWrite(COL_PIN_NUMBERS[col], HIGH);
      String s = "(";
      s = s + col + "," + row + ")";
       Serial.println(s);
       delay(1500);
       digitalWrite(ROW_PIN_NUMBERS[row], LOW);
       digitalWrite(COL_PIN_NUMBERS[col], LOW);
     }
   }
   lastRefreshTime = now;
  }
}
