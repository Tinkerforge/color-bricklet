#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=abc

# set period for color callback to 1s (1000ms)
# note: the color callback is only called every second if the
#       color has changed since the last call!
tinkerforge call color-bricklet $uid set-color-callback-period 1000

# handle incoming color callbacks
tinkerforge dispatch color-bricklet $uid color
