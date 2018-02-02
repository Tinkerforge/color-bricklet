var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Color Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var c = new Tinkerforge.BrickletColor(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Get threshold callbacks with a debounce time of 10 seconds (10000ms)
        c.setDebouncePeriod(10000);

        // Configure threshold for color "greater than 100, 200, 300, 400"
        c.setColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);
    }
);

// Register color reached callback
c.on(Tinkerforge.BrickletColor.CALLBACK_COLOR_REACHED,
    // Callback function for color reached callback
    function (r, g, b, c) {
        console.log('Color [R]: ' + r);
        console.log('Color [G]: ' + g);
        console.log('Color [B]: ' + b);
        console.log('Color [C]: ' + c);
        console.log();
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
