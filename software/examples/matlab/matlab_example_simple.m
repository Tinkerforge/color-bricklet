function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletColor;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'abc'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    c = BrickletColor(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current color
    color = c.getColor();
    fprintf('Color(R): %g\n', color.r);
    fprintf('Color(G): %g\n', color.g);
    fprintf('Color(B): %g\n', color.b);
    fprintf('Color(C): %g\n', color.c);

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end
