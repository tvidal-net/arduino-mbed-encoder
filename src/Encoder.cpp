#include "Encoder.hpp"

Encoder::Encoder(PinName clockPin,
				 PinName dataPin,
				 PinMode pinMode,
				 EncoderCallback onChangeCallback)
	: clockPin(clockPin, pinMode), dataPin(dataPin, pinMode) {
  this->clockPin.rise([&] { ClockChanged(1); });
  this->clockPin.fall([&] { ClockChanged(-1); });

  this->dataPin.rise([&] { DataChanged(1); });
  this->dataPin.fall([&] { DataChanged(-1); });

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
