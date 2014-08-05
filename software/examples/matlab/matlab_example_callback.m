function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletColor;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'abc'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    c = BrickletColor(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set Period for color callback to 1s (1000ms)
    % Note: The color is only called every second if the
    %       color has changed since the last call!
    c.setColorCallbackPeriod(1000);

    % Register color callback to function cb_color
    set(c, 'ColorCallback', @(h, e) cb_color(e));

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback function for color callback
function cb_color(e)
    fprintf('Color(R): %g\n', e.r);
    fprintf('Color(G): %g\n', e.g);
    fprintf('Color(B): %g\n', e.b);
    fprintf('Color(C): %g\n', e.c);
end
