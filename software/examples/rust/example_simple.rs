use std::{error::Error, io};

use tinkerforge::{color_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Color Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let c = ColorBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Get current color.
    let get_color_result = c.get_color().recv()?;

    println!("Color [R]: {}", get_color_result.r);
    println!("Color [G]: {}", get_color_result.g);
    println!("Color [B]: {}", get_color_result.b);
    println!("Color [C]: {}", get_color_result.c);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
