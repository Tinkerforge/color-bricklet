using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Color Bricklet

	// Callback function for color reached callback
	static void ColorReachedCB(BrickletColor sender, int r, int g, int b, int c)
	{
		Console.WriteLine("Color[R]: " + r);
		Console.WriteLine("Color[G]: " + g);
		Console.WriteLine("Color[B]: " + b);
		Console.WriteLine("Color[C]: " + c);
		Console.WriteLine("");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		c.SetDebouncePeriod(10000);

		// Register color reached callback to function ColorReachedCB
		c.ColorReachedCallback += ColorReachedCB;

		// Configure threshold for color "greater than 100, 200, 300, 400"
		c.SetColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
