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

    // Create receiver for color events.
    let color_receiver = c.get_color_receiver();

    // Spawn thread to handle received events. This thread ends when the `c` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for color in color_receiver {
            println!("Color [R]: {}", color.r);
            println!("Color [G]: {}", color.g);
            println!("Color [B]: {}", color.b);
            println!("Color [C]: {}", color.c);
            println!();
        }
    });

    // Set period for color receiver to 1s (1000ms).
    // Note: The color callback is only called every second
    //       if the color has changed since the last call!
    c.set_color_callback_period(1000);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
