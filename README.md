# arduino-mbed-encoder

Yet another arduino encoder lib as I could not find one that used interrupts on both pins,
support for callback functions and had some form of debounce logic for cheap, low quality encoders.

## Usage

platformio.ini:

```ini
[env]
framework = arduino
lib_deps =
    tvidal-net/arduino-mbed-encoder @ ^1.0.1

[env:pico]
board = pico
platform = raspberrypi
monitor_speed = 115200
```

## Examples

* [read](examples/read.cpp)
* [read-debounce](examples/read-debounce.cpp)
* [callback](examples/callback/main.cpp)

### Source code

* [Encoder.hpp](include/Encoder.hpp)
* [Encoder.cpp](src/Encoder.cpp)
