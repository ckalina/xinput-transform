# xutils


## xinput-transform

Automatic calibration of input devices (e.g. stylus) for multi-monitor
setups.

You may either invoke the calibration script `script/xinput-transform`
manually, or you can use a background service `xinput-transformd`.

### Supported use-cases

Any rotation and offset should be supported. Screen and monitor both
have defaults that may be changed using args or env variables; see
`script/xinput-transform --help` for more details.

Scaled, panned, or transformed setups were not tested.

See `script/xinput-transform --help` for more details.

## xcnd - X Configure Notify Daemon

The executable expects path to a "callback", e.g., a path to wherever
`script/xinput-transform` is located, followed by optional arguments
for the "callback" itself.

## xrandr-virt

Helper utility to setup a grid of virtual monitors on a specific
monitor.

See `script/script/xrandr-virt --help` for more details.
