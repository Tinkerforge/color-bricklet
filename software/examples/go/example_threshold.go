package main

import (
	"fmt"
	"tinkerforge/color_bricklet"
	"tinkerforge/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Color Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	c, _ := color_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Get threshold receivers with a debounce time of 10 seconds (10000ms).
	c.SetDebouncePeriod(10000)

	c.RegisterColorReachedCallback(func(r uint16, g uint16, b uint16, c uint16) {
		fmt.Printf("Color [R]: %d\n", r)
		fmt.Printf("Color [G]: %d\n", g)
		fmt.Printf("Color [B]: %d\n", b)
		fmt.Printf("Color [C]: %d\n", c)
		fmt.Println()
	})

	// Configure threshold for color "greater than 100, 200, 300, 400".
	c.SetColorCallbackThreshold('>', 100, 0, 200, 0, 300, 0, 400, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
