#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletColor;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Color Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $c = Tinkerforge::BrickletColor->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current color
my ($r, $g, $b, $c_) = $c->get_color();

print "Color [R]: $r\n";
print "Color [G]: $g\n";
print "Color [B]: $b\n";
print "Color [C]: $c_\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
