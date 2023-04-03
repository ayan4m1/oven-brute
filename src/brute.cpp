#include <Arduino.h>

#define PIN_TX 12
#define PIN_RX 14

#define BAUD_RATES 7
#define RETRIES 10

const uint32_t baudRates[] = {4800, 9600, 14400, 19200, 38400, 57600, 115200};

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println(F("Starting!"));

  for (uint8_t i = 0; i < BAUD_RATES; i++) {
    Serial.printf("Trying %d baud", baudRates[i]);

    Serial1.begin(baudRates[i], SERIAL_8N1, PIN_RX, PIN_TX);

    uint8_t retriesLeft = RETRIES;
    while (!Serial1 && --retriesLeft > 0) {
      Serial.print('.');
      delay(100);
    }

    if (!Serial1) {
      Serial.println(F(" Failed!"));
      Serial1.end();
      continue;
    }

    Serial.println();
    Serial.println("Probing");

    Serial1.write('?');

    retriesLeft = RETRIES;
    while (!Serial1.available() && --retriesLeft > 0) {
      delay(100);
    }

    if (!Serial1.available()) {
      Serial.println(F(" Failed!"));
      Serial1.end();
      continue;
    }

    if (Serial1.read() == 'S') {
      Serial.println(F(" Success!"));
      Serial1.end();
      break;
    }

    Serial.end();
  }
}

void loop() {
  delay(10000);
}
