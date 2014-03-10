using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "abc"; // Change to your UID

	// Callback function for color callback
	static void ColorCB(BrickletColor sender, int r, int g, int b, int C)
	{
        System.Console.WriteLine("Color(R): " + r);
        System.Console.WriteLine("Color(G): " + g);
        System.Console.WriteLine("Color(B): " + b);
        System.Console.WriteLine("Color(C): " + C);
        System.Console.WriteLine("");
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set Period for color callback to 1s (1000ms)
		// Note: The color callback is only called every second if the 
		//       color has changed since the last call!
		c.SetColorCallbackPeriod(1000);

		// Register color callback to function ColorCB
		c.Color += ColorCB;

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
		ipcon.Disconnect();
	}
}
