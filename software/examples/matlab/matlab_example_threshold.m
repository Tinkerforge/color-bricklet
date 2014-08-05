function matlab_example_threshold()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletColor;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'abc'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    c = BrickletColor(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.setDebouncePeriod(10000);

    % Register threshold reached callback to function cb_reached
    set(c, 'ColorReachedCallback', @(h, e) cb_reached(e));

    % Configure threshold for color values,
    % RED   greater than 100
    % GREEN greater than 200
    % BLUE  greater than 300
    % CLEAR greater than 400
    c.setColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback for illuminance greater than 200 Lux
function cb_reached(e)
    fprintf('Color(R): %g\n', e.r);
    fprintf('Color(G): %g\n', e.g);
    fprintf('Color(B): %g\n', e.b);
    fprintf('Color(C): %g\n', e.c);
end
