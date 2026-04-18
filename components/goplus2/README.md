# GoPlus2 ESPHome external component

Place this folder under `components/goplus2/` in the repository root.

Assumptions:
- I2C address: 0x38 (adjust in YAML if your device scans at a different address)
- Protocol (initial guess): write [CMD_SERVO_WRITE, channel, angle]
  - CMD_SERVO_WRITE = 0x00
  - channel = 0 or 1
  - angle = 0..180

Files:
- __init__.py: exposes CONFIG_SCHEMA
- output.py: Python codegen and schema
- goplus2.h / goplus2.cpp: C++ implementation

If servos do not move, enable I2C scan and check logs; we will adjust protocol accordingly.
