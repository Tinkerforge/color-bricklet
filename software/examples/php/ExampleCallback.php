<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletColor.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletColor;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'abc'; // Change to your UID

// Callback function for color
function cb_color($r, $g, $b, $cl)
{
    echo "Color(R): " . $r ."\n";
    echo "Color(G): " . $g ."\n";
    echo "Color(B): " . $b ."\n";
    echo "Color(C): " . $cl ."\n";
    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$c = new BrickletColor(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Set Period for color callback to 1s (1000ms)
// Note: The callback is only called every second if the 
//       color has changed since the last call!
$c->setColorCallbackPeriod(1000);

// Register color callback to function cb_color
$c->registerCallback(BrickletColor::CALLBACK_COLOR, 'cb_color');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
