#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Color Bricklet

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
tinkerforge call color-bricklet $uid set-debounce-period 10000

# Handle incoming color reached callbacks
tinkerforge dispatch color-bricklet $uid color-reached &

# Configure threshold for color "greater than 100, 200, 300, 400"
tinkerforge call color-bricklet $uid set-color-callback-threshold threshold-option-greater 100 0 200 0 300 0 400 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
