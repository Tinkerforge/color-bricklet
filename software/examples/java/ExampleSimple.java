import com.tinkerforge.BrickletColor;
import com.tinkerforge.BrickletColor.Color;
import com.tinkerforge.IPConnection;

public class ExampleSimple {
    private static final String host = "localhost";
    private static final int port = 4223;
    private static final String UID = "abc"; // Change to your UID
    
    // Note: To make the example code cleaner we do not handle exceptions. Exceptions you
    //       might normally want to catch are described in the documentation
    public static void main(String args[]) throws Exception {
        IPConnection ipcon = new IPConnection(); // Create IP connection
        BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

        ipcon.connect(host, port); // Connect to brickd
        // Don't use device before ipcon is connected

        // Get current color
        Color color = c.getColor(); // Can throw com.tinkerforge.TimeoutException

        System.out.println("Color(R): " + color.r);
        System.out.println("Color(G): " + color.g);
        System.out.println("Color(B): " + color.b);
        System.out.println("Color(C): " + color.c);
        System.out.println("");
        
        System.console().readLine("Press key to exit\n");
        ipcon.disconnect();
    }
}