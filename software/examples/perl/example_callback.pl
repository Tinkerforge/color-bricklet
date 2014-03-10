#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletColor;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'abc'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $c = Tinkerforge::BrickletColor->new(&UID, $ipcon); # Create device object

# Callback function for color callback
sub cb_color
{
    my ($r, $g, $b, $C) = @_;
    print "\nColor(R): ".$r."\n";
    print "\nColor(G): ".$g."\n";
    print "\nColor(B): ".$b."\n";
    print "\nColor(C): ".$C."\n";
    print "\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Set Period for color callback to 1s (1000ms)
# Note: The callback is only called every second if the 
#       color has changed since the last call!
$c->set_color_callback_period(1000);

# Register color callback to function cb_color
$c->register_callback($c->CALLBACK_COLOR, 'cb_color');

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

