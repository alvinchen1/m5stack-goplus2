# components/goplus2/output.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output, i2c
from esphome.const import CONF_ID, CONF_CHANNEL

goplus2_ns = cg.esphome_ns.namespace("goplus2")
GoPlus2Component = goplus2_ns.class_("GoPlus2Component", cg.Component, i2c.I2CDevice)
GoPlus2ServoOutput = goplus2_ns.class_("GoPlus2ServoOutput", output.FloatOutput)

CONF_GOPLUS2_ID = "goplus2_id"

# Component-level schema (top-level `goplus2:` block)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(GoPlus2Component),
}).extend(i2c.i2c_device_schema(0x38))

# Platform schema for `output: - platform: goplus2`
PLATFORM_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(GoPlus2ServoOutput),
    cv.Required(CONF_GOPLUS2_ID): cv.use_id(GoPlus2Component),
    cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=1),
})

# Component codegen (creates the I2C device / component)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)

# Platform codegen (called for each `output:` entry)
async def to_code(config):
    parent = await cg.get_variable(config[CONF_GOPLUS2_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_parent(parent))
    cg.add(var.set_channel(config[CONF_CHANNEL]))
    await output.register_output(var, config)
