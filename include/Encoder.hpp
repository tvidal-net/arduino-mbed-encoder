#ifndef HELLO_PICO_INCLUDE_ENCODER_HPP_
#define HELLO_PICO_INCLUDE_ENCODER_HPP_

#include <mbed.h>

using namespace mbed;

typedef bool (*EncoderCallback)(int8_t);

class Encoder {
 public:
  Encoder(PinName clockPin,
          PinName dataPin,
          PinMode pinMode = PinMode::PullUp,
          EncoderCallback onChangeCallback = nullptr);

  void OnChange(EncoderCallback onChangeCallback);

  int8_t ReadAndReset(uint32_t debounceTimeMillis = 0);

  void Reset();

  inline
  int8_t Read() const { return ticks; }

  inline
  bool ReadClock() { return clockPin.read(); }

  inline
  bool ReadData() { return dataPin.read(); }

  inline
  uint32_t ElapsedMillis() const { return millis() - startTimeMillis; }

  inline
  bool ClockHasChanged() const { return clockHasChanged; }

  inline
  bool DataHasChanged() const { return !clockHasChanged; }

 private:
  bool clockHasChanged;
  int8_t ticks;
  uint32_t startTimeMillis;

  InterruptIn clockPin;
  InterruptIn dataPin;

  EncoderCallback onChangeCallback;

  void ClockChanged(int8_t delta);
  void DataChanged(int8_t delta);

  void Changed();

  enum { Add = 1, Sub = -1 };
};

#endif //HELLO_PICO_INCLUDE_ENCODER_HPP_
