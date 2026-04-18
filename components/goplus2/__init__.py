# components/goplus2/__init__.py
# Mark this package as a platform component so ESPHome treats it as an output platform.
IS_PLATFORM_COMPONENT = True

# Import the platform implementation and re-export the module-level symbols ESPHome expects.
from . import output as output_mod

# Expose the expected names at package level
CONFIG_SCHEMA = output_mod.CONFIG_SCHEMA
PLATFORM_SCHEMA = output_mod.PLATFORM_SCHEMA
to_code = output_mod.to_code
