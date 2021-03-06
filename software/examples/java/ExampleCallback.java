import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletColor;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Color Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletColor c = new BrickletColor(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add color listener
		c.addColorListener(new BrickletColor.ColorListener() {
			public void color(int r, int g, int b, int c) {
				System.out.println("Color [R]: " + r);
				System.out.println("Color [G]: " + g);
				System.out.println("Color [B]: " + b);
				System.out.println("Color [C]: " + c);
				System.out.println("");
			}
		});

		// Set period for color callback to 1s (1000ms)
		// Note: The color callback is only called every second
		//       if the color has changed since the last call!
		c.setColorCallbackPeriod(1000);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
