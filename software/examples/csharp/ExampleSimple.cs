using Tinkerforge;

class Example
{
    private static string HOST = "localhost";
    private static int PORT = 4223;
    private static string UID = "abc"; // Change to your UID

    static void Main() 
    {
        IPConnection ipcon = new Tinkerforge.IPConnection(); // Create IP connection
        BrickletColor c = new Tinkerforge.BrickletColor(UID, ipcon); // Create device object

        ipcon.Connect(HOST, PORT); // Connect to brickd
        // Don't use device before ipcon is connected

        // Get current color
        int r;
        int g;
        int b;
        int C;
        c.GetColor(out r, out g, out b, out C);

        System.Console.WriteLine("Color(R): " + r);
        System.Console.WriteLine("Color(G): " + g);
        System.Console.WriteLine("Color(B): " + b);
        System.Console.WriteLine("Color(C): " + C);
        System.Console.WriteLine("");

        System.Console.WriteLine("Press key to exit");
        System.Console.ReadKey();
        ipcon.Disconnect();
    }
}
