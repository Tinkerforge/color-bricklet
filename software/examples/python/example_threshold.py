#!/usr/bin/env python
# -*- coding: utf-8 -*-  

import sys
sys.path.append('./tinkerforge')

HOST = "localhost"
PORT = 4223
UID = "abc" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_color import Color

# Callback function for color callback (in RGBC)
def cb_reached(r, g, b, c):
    print('Color reached...')
    print('Color(R): ' + str(r))
    print('Color(G): ' + str(g))
    print('Color(B): ' + str(b))
    print('Color(C): ' + str(c))
    print('')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    c = Color(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.set_debounce_period(10000)

    # Register threshold reached callback to function cb_reached
    c.register_callback(c.CALLBACK_COLOR_REACHED, cb_reached)

    # Configure threshold
    c.set_color_callback_threshold('>', 255, 255, 255, 255, 255, 255, 255, 255)
    
    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
