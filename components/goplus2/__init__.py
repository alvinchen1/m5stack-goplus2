# components/goplus2/__init__.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ID

# Import platform support
from . import output

goplus2_ns = cg.esphome_ns.namespace("goplus2")
GoPlus2Component = goplus2_ns.class_("GoPlus2Component", cg.Component, i2c.I2CDevice)

# Component-level schema (top-level `goplus2:` block)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(GoPlus2Component),
}).extend(i2c.i2c_device_schema(0x38))

# Component codegen (creates the I2C device / component)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)
