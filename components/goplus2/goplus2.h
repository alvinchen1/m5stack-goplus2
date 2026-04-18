#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/float_output.h"

namespace esphome {
namespace goplus2 {

static const uint8_t GOPLUS2_I2C_ADDR = 0x38;
static const uint8_t CMD_SERVO_WRITE = 0x00;

class GoPlus2Component : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;

  void write_servo(uint8_t channel, float level);

 protected:
  bool write_servo_raw(uint8_t channel, uint8_t angle);
};

class GoPlus2ServoOutput : public output::FloatOutput {
 public:
  void set_parent(GoPlus2Component *parent) { parent_ = parent; }
  void set_channel(uint8_t channel) { channel_ = channel; }

 protected:
  void write_state(float state) override;

  GoPlus2Component *parent_{nullptr};
  uint8_t channel_{0};
};

}  // namespace goplus2
}  // namespace esphome
