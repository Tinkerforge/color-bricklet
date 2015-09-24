#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_color.h"

#define HOST "localhost"
#define PORT 4223
#define UID "XYZ" // Change to your UID

int main(void) {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Color c;
	color_create(&c, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		return 1;
	}
	// Don't use device before ipcon is connected

	// Get current color
	uint16_t r, g, b, c_;
	if(color_get_color(&c, &r, &g, &b, &c_) < 0) {
		fprintf(stderr, "Could not get color, probably timeout\n");
		return 1;
	}

	printf("Color[R]: %d\n", r);
	printf("Color[G]: %d\n", g);
	printf("Color[B]: %d\n", b);
	printf("Color[C]: %d\n", c_);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
