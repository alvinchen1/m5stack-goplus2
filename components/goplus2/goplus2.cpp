// components/goplus2/goplus2.cpp
#include "goplus2.h"
#include "esphome/core/log.h"

namespace esphome {
namespace goplus2 {

static const char *const TAG = "goplus2";

void GoPlus2Component::setup() {
  ESP_LOGI(TAG, "GoPlus2 component setup");
  // Optional: probe device here if you want to log presence
}

void GoPlus2Component::dump_config() {
  ESP_LOGCONFIG(TAG, "GoPlus2:");
  LOG_I2C_DEVICE(this);
}

bool GoPlus2Component::write_servo_raw(uint8_t channel, uint8_t angle) {
  uint8_t buf[3] = {CMD_SERVO_WRITE, channel, angle};
  auto err = this->write(buf, sizeof(buf));
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C write failed for channel %u, error: %d", channel, err);
    return false;
  }
  return true;
}

void GoPlus2Component::write_servo(uint8_t channel, float level) {
  float clamped = level;
  if (clamped < -1.0f) clamped = -1.0f;
  if (clamped > 1.0f) clamped = 1.0f;
  // Map -1..1 to 0..180
  float normalized = (clamped + 1.0f) * 0.5f;
  uint8_t angle = static_cast<uint8_t>(normalized * 180.0f);
  ESP_LOGV(TAG, "Write servo channel %u level %.3f -> angle %u", channel, level, angle);
  this->write_servo_raw(channel, angle);
}

void GoPlus2ServoOutput::write_state(float state) {
  if (this->parent_ == nullptr) {
    ESP_LOGW(TAG, "Parent not set for GoPlus2ServoOutput");
    return;
  }
  this->parent_->write_servo(this->channel_, state);
}

}  // namespace goplus2
}  // namespace esphome
