<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletColor.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletColor;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change to your UID

// Callback function for color callback
function cb_color($r, $g, $b, $c)
{
    echo "Color[R]: $r\n";
    echo "Color[G]: $g\n";
    echo "Color[B]: $b\n";
    echo "Color[C]: $c\n";
    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$c = new BrickletColor(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register color callback to function cb_color
$c->registerCallback(BrickletColor::CALLBACK_COLOR, 'cb_color');

// Set period for color callback to 1s (1000ms)
// Note: The color callback is only called every second
//       if the color has changed since the last call!
$c->setColorCallbackPeriod(1000);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
