function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletColor;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Color Bricklet

    ipcon = IPConnection(); % Create IP connection
    c = handle(BrickletColor(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register color callback to function cb_color
    set(c, 'ColorCallback', @(h, e) cb_color(e));

    % Set period for color callback to 1s (1000ms)
    % Note: The color callback is only called every second
    %       if the color has changed since the last call!
    c.setColorCallbackPeriod(1000);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for color callback
function cb_color(e)
    fprintf('Color [R]: %i\n', e.r);
    fprintf('Color [G]: %i\n', e.g);
    fprintf('Color [B]: %i\n', e.b);
    fprintf('Color [C]: %i\n', e.c);
    fprintf('\n');
end
