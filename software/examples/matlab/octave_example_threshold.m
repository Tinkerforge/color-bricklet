function octave_example_threshold()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Color Bricklet

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    c = java_new("com.tinkerforge.BrickletColor", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.setDebouncePeriod(10000);

    % Register color reached callback to function cb_color_reached
    c.addColorReachedCallback(@cb_color_reached);

    % Configure threshold for color "greater than 100, 200, 300, 400"
    c.setColorCallbackThreshold(">", 100, 0, 200, 0, 300, 0, 400, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for color reached callback
function cb_color_reached(e)
    fprintf("Color[R]: %d\n", e.r);
    fprintf("Color[G]: %d\n", e.g);
    fprintf("Color[B]: %d\n", e.b);
    fprintf("Color[C]: %d\n", e.c);
    fprintf("\n");
end
