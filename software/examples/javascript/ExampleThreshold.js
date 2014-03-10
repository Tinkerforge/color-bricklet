var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'abc';// Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var c = new Tinkerforge.BrickletColor(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        // Set threshold callbacks with a debounce time of 10 seconds (10000ms)
        c.setDebouncePeriod(10000);
        // Configure threshold for color values,
        // RED  : greater than 100
        // GREEN: greater than 200
        // BLUE : greater than 300
        // CLEAR: greater than 400
        c.setColorCallbackThreshold('>', 0, 100, 0, 200, 0, 300, 0, 400);
    }
);

// Register threshold reached callback
c.on(Tinkerforge.BrickletColor.CALLBACK_COLOR_REACHED,
    // Callback for color threshold reached
    function(r, g, b, C) {
        console.log('Color(R): '+r);
        console.log('Color(G): '+g);
        console.log('Color(B): '+b);
        console.log('Color(C): '+C);
        console.log();
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

