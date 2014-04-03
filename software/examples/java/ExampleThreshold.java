import com.tinkerforge.BrickletColor;
import com.tinkerforge.IPConnection;

public class ExampleThreshold {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "abc"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get threshold callbacks with a debounce time of 10 seconds (10000ms)
		c.setDebouncePeriod(10000);

		// Add and implement color reached listener
		// Configure threshold for color values,
		// RED   greater than 100
		// GREEN greater than 200
		// BLUE  greater than 300
		// CLEAR greater than 400
		c.setColorCallbackThreshold('>', (int)(0), (int)(100), (int)(0), (int)(200), (int)(0), (int)(300), (int)(0), (int)(400));

		c.addColorReachedListener(new BrickletColor.ColorReachedListener() {
			public void colorReached(int r, int g, int b, int c) {
				System.out.println("Color(R): " + r);
				System.out.println("Color(G): " + g);
				System.out.println("Color(B): " + b);
				System.out.println("Color(C): " + c);
				System.out.println("");
			}
		});

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
