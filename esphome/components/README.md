# ESPHome Local Components

This directory contains local ESPHome component overrides used by the EBMC
hardware configs.

`pn532` and `pn532_spi` are copied from ESPHome 2026.5.0 with one local helper
on the base component: `PN532::clear_current_uid()`. The album tag programmer
calls that helper after an NDEF write before switching back to read mode so it
can verify the same tag without requiring the tag to be lifted away and tapped
again.
