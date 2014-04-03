#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=abc

# get threshold callbacks with a debounce time of 10 seconds (10000ms)
tinkerforge call color-bricklet $uid set-debounce-period 10000

# Configure threshold for color values,
# RED   greater than 100
# GREEN greater than 200
# BLUE  greater than 300
# CLEAR greater than 400
tinkerforge call color-bricklet $uid set-color-callback-threshold greater 0 100 0 200 0 300 0 400

# handle incoming color-reached callbacks
tinkerforge dispatch color-bricklet $uid color-reached\
 --execute "echo 'Color(R): {r}';
            echo 'Color(G): {g}';
            echo 'Color(B): {b}';
            echo 'Color(C): {c}';
            echo '';"
