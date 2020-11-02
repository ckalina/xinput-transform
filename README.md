# xinput-transform

Automatic calibration of input devices (e.g. stylus) for multi-monitor
setups.

You may either invoke the calibration script `script/calibrate-tablet`
manually, or you can use a background service `xinput-transformd`.

## Supported use-cases

Any rotation and offset should be supported. Screen and monitor both
have defaults that may be changed using args or env variables; see
`script/calibrate-tablet --help` for more details.

Scaled, panned, or transformed setups were not tested.

## Manual use

See `script/calibrate-tablet --help` for more details.

## Background service

 - to compile: `make build`
 - to install to `/usr/local/bin`: `make install`

The executable expects path to a "callback", so for example a path
to wherever `script/calibrate-tablet` is located, followed by optional
arguments for the "callback" itself.
