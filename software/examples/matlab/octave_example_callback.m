function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    c = java_new("com.tinkerforge.BrickletColor", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set Period for color callback to 1s (1000ms)
    % Note: The color callback is only called every second if the
    %       color has changed since the last call!
    c.setColorCallbackPeriod(1000);

    % Register color callback to function cb_color
    c.addColorCallback(@cb_color);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for color callback
function cb_color(e)
    fprintf("Color(R): %g\n", e.r);
    fprintf("Color(G): %g\n", e.g);
    fprintf("Color(B): %g\n", e.b);
    fprintf("Color(C): %g\n", e.c);
end
