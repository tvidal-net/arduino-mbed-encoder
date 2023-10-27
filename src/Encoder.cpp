#include "Encoder.hpp"

Encoder::Encoder(PinName clockPin,
                 PinName dataPin,
                 PinMode pinMode,
                 EncoderCallback onChangeCallback)
    : clockPin(clockPin, pinMode), dataPin(dataPin, pinMode) {
  this->clockPin.rise([&] { ClockChanged(Add); });
  this->clockPin.fall([&] { ClockChanged(Sub); });

  this->dataPin.rise([&] { DataChanged(Add); });
  this->dataPin.fall([&] { DataChanged(Sub); });

  OnChange(onChangeCallback);
}

void Encoder::OnChange(EncoderCallback onChangeCallback) {
  this->onChangeCallback = onChangeCallback;
}

int8_t Encoder::ReadAndReset(uint32_t debounceTimeMillis) {
  if (ElapsedMillis() >= debounceTimeMillis) {
    int8_t value = Read();
    Reset();
    return value;
  }
  return 0;
}

void Encoder::Reset() {
  startTimeMillis = ticks = 0;
}

void Encoder::ClockChanged(int8_t delta) {
  if (DataHasChanged()) {
    if (ReadData()) {
      ticks -= delta;
    } else {
      ticks += delta;
    }
    clockHasChanged = true;
    Changed();
  }
}

void Encoder::DataChanged(int8_t delta) {
  if (ClockHasChanged()) {
    if (ReadClock()) {
      ticks += delta;
    } else {
      ticks -= delta;
    }
    clockHasChanged = false;
    Changed();
  }
}

void Encoder::Changed() {
  if (!startTimeMillis) {
    startTimeMillis = millis();
  }
  if (onChangeCallback && onChangeCallback(ticks)) {
    Reset();
  }
}
