using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current color
		int r, g, b, c_;
		c.GetColor(out r, out g, out b, out c_);

		Console.WriteLine("Color[R]: " + r);
		Console.WriteLine("Color[G]: " + g);
		Console.WriteLine("Color[B]: " + b);
		Console.WriteLine("Color[C]: " + c_);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
