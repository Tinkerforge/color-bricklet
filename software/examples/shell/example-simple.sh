#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Color Bricklet

# Get current color
tinkerforge call color-bricklet $uid get-color
