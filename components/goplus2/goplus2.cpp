#include "goplus2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace goplus2 {

static const char *const TAG = "goplus2";

void GoPlus2Component::setup() {
  ESP_LOGI(TAG, "Setting up GoPlus2 component");
}

void GoPlus2Component::dump_config() {
  ESP_LOGCONFIG(TAG, "GoPlus2:");
  LOG_I2C_DEVICE(this);
}

bool GoPlus2Component::write_servo_raw(uint8_t channel, uint8_t angle) {
  uint8_t buf[3] = {CMD_SERVO_WRITE, channel, angle};
  auto err = this->write(buf, sizeof(buf));
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C write failed for channel %u", channel);
    return false;
  }
  return true;
}

void GoPlus2Component::write_servo(uint8_t channel, float level) {
  float clamped = std::max(-1.0f, std::min(1.0f, level));
  uint8_t angle = static_cast<uint8_t>((clamped + 1.0f) * 90.0f);
  this->write_servo_raw(channel, angle);
}

void GoPlus2ServoOutput::write_state(float state) {
  if (this->parent_ == nullptr) return;
  this->parent_->write_servo(this->channel_, state);
}

}  // namespace goplus2
}  // namespace esphome
