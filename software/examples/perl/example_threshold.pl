#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletColor;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

# Callback subroutine for color reached callback
sub cb_color_reached
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

# Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$c->set_debounce_period(10000);

# Register color reached callback to subroutine cb_color_reached
$c->register_callback($c->CALLBACK_COLOR_REACHED, 'cb_color_reached');

# Configure threshold for color "greater than 100, 200, 300, 400"
$c->set_color_callback_threshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
