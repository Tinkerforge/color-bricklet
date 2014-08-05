function octave_example_threshold()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    c = java_new("com.tinkerforge.BrickletColor", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.setDebouncePeriod(10000);

    % Configure threshold for color values,
    % RED   greater than 100
    % GREEN greater than 200
    % BLUE  greater than 300
    % CLEAR greater than 400
    c.setColorCallbackThreshold(c.THRESHOLD_OPTION_GREATER, 100, 0, 200, 0, 300, 0, 400, 0);
    
    % Register threshold reached callback to function cb_reached
    c.addColorReachedCallback(@cb_reached);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for color callback
function cb_reached(e)
    fprintf("Color(R): %g\n", e.r);
    fprintf("Color(G): %g\n", e.g);
    fprintf("Color(B): %g\n", e.b);
    fprintf("Color(C): %g\n", e.c);
end
