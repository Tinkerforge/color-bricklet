function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    c = java_new("com.tinkerforge.BrickletColor", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current color
    color = c.getColor();
    fprintf("Color(R): %g\n", color.r);
    fprintf("Color(G): %g\n", color.g);
    fprintf("Color(B): %g\n", color.b);
    fprintf("Color(C): %g\n", color.c);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
