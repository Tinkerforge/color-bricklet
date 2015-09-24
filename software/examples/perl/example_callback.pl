#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletColor;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

# Callback subroutine for color callback
sub cb_color
{
    my ($r, $g, $b, $c) = @_;

    print "Color[R]: $r\n";
    print "Color[G]: $g\n";
    print "Color[B]: $b\n";
    print "Color[C]: $c\n";
    print "\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $c = Tinkerforge::BrickletColor->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register color callback to subroutine cb_color
$c->register_callback($c->CALLBACK_COLOR, 'cb_color');

# Set period for color callback to 1s (1000ms)
# Note: The color callback is only called every second
#       if the color has changed since the last call!
$c->set_color_callback_period(1000);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
