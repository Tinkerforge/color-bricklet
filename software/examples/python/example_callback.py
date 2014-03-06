#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "abc" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_color import Color

# Callback function for color callback (in RGBC)
def cb_color(r, g, b, c):
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
    # Set Period for color callback to 1s (1000ms)
    # Note: The callback is only called every second if the 
    #       temperature has changed since the last call!
    c.set_color_callback_period(1000)

    # Register temperature callback to function cb_temperature
    c.register_callback(c.CALLBACK_COLOR, cb_color)
    
    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
