# GoPlus2 ESPHome External Component

This component provides servo control for the M5Stack GoPlus2 module.

Structure matches the `m5paper_esphome` repository style:
- Python codegen (`__init__.py`, `output.py`)
- C++ implementation (`goplus2.h`, `goplus2.cpp`)
- Optional YAML example

Protocol assumptions:
- I2C address: 0x38
- Command format: [0x00, channel, angle]
- Angle: 0–180 degrees

Adjust as needed based on real GoPlus2 behavior.
