#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Color Bricklet

# Handle incoming color callbacks
tinkerforge dispatch color-bricklet $uid color &

# Set period for color callback to 1s (1000ms)
# Note: The color callback is only called every second
#       if the color has changed since the last call!
tinkerforge call color-bricklet $uid set-color-callback-period 1000

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
