use std::{error::Error, io, thread};
use tinkerforge::{color_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Color Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let c = ColorBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Get threshold receivers with a debounce time of 10 seconds (10000ms).
    c.set_debounce_period(10000);

    // Create receiver for color reached events.
    let color_reached_receiver = c.get_color_reached_receiver();

    // Spawn thread to handle received events. This thread ends when the `c` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for color_reached in color_reached_receiver {
            println!("Color [R]: {}", color_reached.r);
            println!("Color [G]: {}", color_reached.g);
            println!("Color [B]: {}", color_reached.b);
            println!("Color [C]: {}", color_reached.c);
            println!();
        }
    });

    // Configure threshold for color "greater than 100, 200, 300, 400".
    c.set_color_callback_threshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
