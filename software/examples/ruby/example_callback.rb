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

# Set Period for color callback to 1s (1000ms)
# Note: The callback is only called every second if the
#       color has changed since the last call!
c.set_color_callback_period 1000

# Register color callback
c.register_callback(BrickletColor::CALLBACK_COLOR) do |r, g, b, cl|
  puts "Color(R): #{r}"
  puts "Color(G): #{g}"
  puts "Color(B): #{b}"
  puts "Color(C): #{cl}"
  puts ''
end

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
