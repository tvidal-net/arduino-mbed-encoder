#include <Arduino.h>
#include "Encoder.hpp"

Encoder e(PinName::p18, PinName::p19);

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n\nencoder-read-example");
}

void loop() {
  int8_t ticks = e.Read();
  if (ticks) {
    Serial.print("ticks=");
    Serial.println(ticks);
    e.Reset();
  }
}
