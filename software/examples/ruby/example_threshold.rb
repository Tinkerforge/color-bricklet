#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_color'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'abc' # Change to your UID

ipcon = IPConnection.new # Create IP connection
c = BrickletColor.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
c.set_debounce_period 10000

# Register callback for color reached threshold
c.register_callback(BrickletColor::CALLBACK_COLOR_REACHED) do |r, g, b, cl|
  puts "Color(R): #{r}"
  puts "Color(G): #{g}"
  puts "Color(B): #{b}"
  puts "Color(C): #{cl}"
  puts ''
end

# Configure threshold for color values,
# RED   greater than 100
# GREEN greater than 200
# BLUE  greater than 300
# CLEAR greater than 400
c.set_color_callback_threshold '>', 100, 0, 200, 0, 300, 0, 400, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
