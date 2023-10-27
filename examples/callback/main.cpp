#include <Arduino.h>
#include "Encoder.hpp"

#define DEBOUNCE_TIME   55

bool encoder_changed(int8_t ticks);

Encoder e(PinName::p18, PinName::p19, PinMode::PullUp, encoder_changed);
int8_t encoder_ticks = 0;

bool encoder_changed(int8_t ticks) {
  if (e.ElapsedMillis() >= DEBOUNCE_TIME) {
    encoder_ticks += ticks;
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n\nencoder-callback-example");
}

void loop() {
  if (encoder_ticks) {
    Serial.print("ticks=");
    Serial.println(encoder_ticks);
    encoder_ticks = 0;
  }
}
