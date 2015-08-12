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
	uint16_t r; uint16_t g; uint16_t b; uint16_t cl;
	if(color_get_color(&c, &r, &g, &b, &cl) < 0) {
		fprintf(stderr, "Could not get value, probably timeout\n");
		return 1;
	}

	printf("Color(R): %u\n", r);
	printf("Color(G): %u\n", g);
	printf("Color(B): %u\n", b);
	printf("Color(C): %u\n", cl);
	printf("\n");

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	return 0;
}
