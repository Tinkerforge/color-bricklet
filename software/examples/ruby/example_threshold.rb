#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_color'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change to your UID

ipcon = IPConnection.new # Create IP connection
c = BrickletColor.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
c.set_debounce_period 10000

# Register color reached callback
c.register_callback(BrickletColor::CALLBACK_COLOR_REACHED) do |r, g, b, c_|
  puts "Color[R]: #{r}"
  puts "Color[G]: #{g}"
  puts "Color[B]: #{b}"
  puts "Color[C]: #{c_}"
  puts ''
end

# Configure threshold for color "greater than 100, 200, 300, 400"
c.set_color_callback_threshold '>', 100, 0, 200, 0, 300, 0, 400, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
