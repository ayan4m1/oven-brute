#include <Arduino.h>

#define BAUD_RATE 14400
#define WAIT_FOR_CONNECTION

void setup() {
  Serial.begin(BAUD_RATE);
  Serial1.begin(BAUD_RATE);

#ifdef WAIT_FOR_CONNECTION
  while (!Serial1) {
    Serial.print('.');
    delay(100);
  }
#endif
}

void loop() {
  if (!Serial1.available()) {
    return delay(100);
  }

  Serial1.readStringUntil('?');
  Serial1.println("Synchronized");
}
