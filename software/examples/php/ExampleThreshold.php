<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletColor.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletColor;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'abc'; // Change to your UID

// Callback for color threshold reached
function cb_reached($r, $g, $b, $C)
{
    echo "Color(R): " . $r ."\n";
    echo "Color(G): " . $g ."\n";
    echo "Color(B): " . $b ."\n";
    echo "Color(C): " . $C ."\n";
    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$c = new BrickletColor(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
$c->setDebouncePeriod(10000);

// Register threshold reached callback to function cb_reached
$c->registerCallback(BrickletColor::CALLBACK_COLOR_REACHED, 'cb_reached');

// Configure threshold for color values,
// RED   greater than 100
// GREEN greater than 200
// BLUE  greater than 300
// CLEAR greater than 400
$c->setColorCallbackThreshold('>', 0, 100, 0, 200, 0, 300, 0, 400);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
