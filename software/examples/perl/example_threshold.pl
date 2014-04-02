#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletColor;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'abc'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $col = Tinkerforge::BrickletColor->new(&UID, $ipcon); # Create device object

# Callback function for color callback
sub cb_reached
{
    my ($r, $g, $b, $c) = @_;

    print "Color(R): $r\n";
    print "Color(G): $g\n";
    print "Color(B): $b\n";
    print "Color(C): $c\n";
    print "\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$col->set_debounce_period(10000);

# Register threshold reached callback to function cb_reached
$col->register_callback($col->CALLBACK_COLOR_REACHED, 'cb_reached');

# Configure threshold for color values,
# RED   greater than 100
# GREEN greater than 200
# BLUE  greater than 300
# CLEAR greater than 400
$col->set_color_callback_threshold('>', 0, 100, 0, 200, 0, 300, 0, 400);

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();
