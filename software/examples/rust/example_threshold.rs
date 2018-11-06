use std::{error::Error, io, thread};
use tinkerforge::{color_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Color Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let color_bricklet = ColorBricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    // Get threshold listeners with a debounce time of 10 seconds (10000ms)
    color_bricklet.set_debounce_period(10000);

    //Create listener for color reached events.
    let color_reached_listener = color_bricklet.get_color_reached_receiver();
    // Spawn thread to handle received events. This thread ends when the color_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in color_reached_listener {
            println!("Color [R]: {}", event.r);
            println!("Color [G]: {}", event.g);
            println!("Color [B]: {}", event.b);
            println!("Color [C]: {}", event.c);
            println!();
        }
    });

    // Configure threshold for color "greater than 100, 200, 300, 400"
    color_bricklet.set_color_callback_threshold('>', 100, 0, 200, 0, 300, 0, 400, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
