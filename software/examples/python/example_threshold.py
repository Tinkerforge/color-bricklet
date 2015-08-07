#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_color import BrickletColor

# Callback function for color callback
def cb_reached(r, g, b, cl):
    print('Color(R): ' + str(r))
    print('Color(G): ' + str(g))
    print('Color(B): ' + str(b))
    print('Color(C): ' + str(cl))
    print('')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    c = BrickletColor(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.set_debounce_period(10000)

    # Register threshold reached callback to function cb_reached
    c.register_callback(c.CALLBACK_COLOR_REACHED, cb_reached)

    # Configure threshold for color values,
    # RED   greater than 100
    # GREEN greater than 200
    # BLUE  greater than 300
    # CLEAR greater than 400
    c.set_color_callback_threshold('>', 100, 0, 200, 0, 300, 0, 400, 0)
    
    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
