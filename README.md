# arduino-mbed-encoder

Yet another arduino encoder lib as I could not find one that used interrupts on both pins,
support for callback functions and had some form of debounce logic for cheap, low quality encoders.

## Usage

platformio.ini:

```ini
[env]
framework = arduino
lib_deps =
    tvidal-net/arduino-mbed-encoder

[env:pico]
board = pico
platform = raspberrypi
monitor_speed = 115200
```

## Examples

* [read](examples/read/main.cpp)
* [read-debounce](examples/read-debounce/main.cpp)
* [callback](examples/callback/main.cpp)

### Source code

* [Encoder.hpp](include/Encoder.hpp)
* [Encoder.cpp](src/Encoder.cpp)
