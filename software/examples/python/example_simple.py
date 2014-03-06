#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "abc" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_color import Color

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    c = Color(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current color(in RGBC)
    color = c.get_color()

    print('Color(R): ' + str(color.r))
    print('Color(G): ' + str(color.g))
    print('Color(B): ' + str(color.b))
    print('Color(C): ' + str(color.c))
    print('')

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
