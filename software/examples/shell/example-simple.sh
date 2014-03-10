#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=abc

# get current color (in RGBC)
tinkerforge call color-bricklet $uid get-color
