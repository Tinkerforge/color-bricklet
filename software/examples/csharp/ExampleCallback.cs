using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Color Bricklet

	// Callback function for color callback
	static void ColorCB(BrickletColor sender, int r, int g, int b, int c)
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

		// Register color callback to function ColorCB
		c.ColorCallback += ColorCB;

		// Set period for color callback to 1s (1000ms)
		// Note: The color callback is only called every second
		//       if the color has changed since the last call!
		c.SetColorCallbackPeriod(1000);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
