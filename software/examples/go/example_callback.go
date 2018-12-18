package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/color_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
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

	c.RegisterColorCallback(func(r uint16, g uint16, b uint16, c uint16) {
		fmt.Printf("Color [R]: %d\n", r)
		fmt.Printf("Color [G]: %d\n", g)
		fmt.Printf("Color [B]: %d\n", b)
		fmt.Printf("Color [C]: %d\n", c)
		fmt.Println()
	})

	// Set period for color receiver to 1s (1000ms).
	// Note: The color callback is only called every second
	//       if the color has changed since the last call!
	c.SetColorCallbackPeriod(1000)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
