
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_color.h"

#define HOST "localhost"
#define PORT 4223
#define UID "abc" // Change to your UID

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Color c;
	color_create(&c, UID, &ipcon); 

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Get current color in RGBC
	uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t C;
	if(color_get_color(&c, &r, &g, &b, &C) < 0) {
		fprintf(stderr, "Could not get value, probably timeout\n");
		exit(1);
	}

	printf("Color(R) = %d.\n", r);
    printf("Color(G) = %d.\n", g);
    printf("Color(B) = %d.\n", b);
    printf("Color(C) = %d.\n", C);
	printf("\n");

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}