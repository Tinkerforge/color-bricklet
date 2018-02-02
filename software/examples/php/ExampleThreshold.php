<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletColor.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletColor;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Color Bricklet

// Callback function for color reached callback
function cb_colorReached($r, $g, $b, $c)
{
    echo "Color [R]: $r\n";
    echo "Color [G]: $g\n";
    echo "Color [B]: $b\n";
    echo "Color [C]: $c\n";
    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$c = new BrickletColor(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$c->setDebouncePeriod(10000);

// Register color reached callback to function cb_colorReached
$c->registerCallback(BrickletColor::CALLBACK_COLOR_REACHED, 'cb_colorReached');

// Configure threshold for color "greater than 100, 200, 300, 400"
$c->setColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
