use std::{error::Error, io};

use tinkerforge::{color_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Color Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let color_bricklet = ColorBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Get current color
    let get_color_result = color_bricklet.get_color().recv()?;

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
