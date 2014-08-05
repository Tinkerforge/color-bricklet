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
        // Get current color
        c.getColor(
            function(r, g, b, cl) {
                console.log('Color(R): '+r);
                console.log('Color(G): '+g);
                console.log('Color(B): '+b);
                console.log('Color(C): '+cl);
                console.log();
            },
            function(error) {
                console.log('Error: '+error);
            }
        );
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

