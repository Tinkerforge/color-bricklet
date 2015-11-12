function matlab_example_threshold()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletColor;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    c = handle(BrickletColor(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get threshold callbacks with a debounce time of 10 seconds (10000ms)
    c.setDebouncePeriod(10000);

    % Register color reached callback to function cb_color_reached
    set(c, 'ColorReachedCallback', @(h, e) cb_color_reached(e));

    % Configure threshold for color "greater than 100, 200, 300, 400"
    c.setColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for color reached callback
function cb_color_reached(e)
    fprintf('Color[R]: %i\n', e.r);
    fprintf('Color[G]: %i\n', e.g);
    fprintf('Color[B]: %i\n', e.b);
    fprintf('Color[C]: %i\n', e.c);
    fprintf('\n');
end
