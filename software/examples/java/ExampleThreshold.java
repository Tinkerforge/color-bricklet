import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletColor;

public class ExampleThreshold {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		c.setDebouncePeriod(10000);

		// Add color reached listener
		c.addColorReachedListener(new BrickletColor.ColorReachedListener() {
			public void colorReached(int r, int g, int b, int c) {
				System.out.println("Color[R]: " + r);
				System.out.println("Color[G]: " + g);
				System.out.println("Color[B]: " + b);
				System.out.println("Color[C]: " + c);
				System.out.println("");
			}
		});

		// Configure threshold for color "greater than 100, 200, 300, 400"
		c.setColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
