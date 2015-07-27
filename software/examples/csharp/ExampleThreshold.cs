using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback for color threshold reached
	static void ReachedCB(BrickletColor sender, int r, int g, int b, int cl)
	{
		System.Console.WriteLine("Color(R): " + r);
		System.Console.WriteLine("Color(G): " + g);
		System.Console.WriteLine("Color(B): " + b);
		System.Console.WriteLine("Color(C): " + cl);
		System.Console.WriteLine("");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		c.SetDebouncePeriod(10000);

		// Register threshold reached callback to function ReachedCB
		c.ColorReached += ReachedCB;

		// Configure threshold for color values,
		// RED   greater than 100
		// GREEN greater than 200
		// BLUE  greater than 300
		// CLEAR greater than 400
		c.SetColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
