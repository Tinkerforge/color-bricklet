#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_color'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Color Bricklet

ipcon = IPConnection.new # Create IP connection
c = BrickletColor.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register color callback
c.register_callback(BrickletColor::CALLBACK_COLOR) do |r, g, b, c_|
  puts "Color[R]: #{r}"
  puts "Color[G]: #{g}"
  puts "Color[B]: #{b}"
  puts "Color[C]: #{c_}"
  puts ''
end

# Set period for color callback to 1s (1000ms)
# Note: The color callback is only called every second
#       if the color has changed since the last call!
c.set_color_callback_period 1000

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
