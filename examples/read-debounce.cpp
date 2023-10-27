#include <Arduino.h>
#include "Encoder.hpp"

#define DEBOUNCE_TIME   55

Encoder e(PinName::p18, PinName::p19, PinMode::PullUp);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n\nencoder-read-debounce-example");
}

void loop() {
  int8_t ticks = e.ReadAndReset(DEBOUNCE_TIME);
  if (ticks) {
    Serial.print("ticks=");
    Serial.println(ticks);
  }
}
