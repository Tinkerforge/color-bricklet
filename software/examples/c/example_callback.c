
#include <stdio.h>

#include "ip_connection.h"
#include "bricklet_color.h"

#define HOST "localhost"
#define PORT 4223
#define UID "abc" // Change to your UID

// Callback for color with RGBC values greater than 255
void cb_color(uint16_t r, uint16_t g, uint16_t b, uint16_t c, void *user_data) {
	(void)user_data; // avoid unused parameter warning

	printf("Color(R) = %d.\n", r);
    printf("Color(G) = %d.\n", g);
    printf("Color(B) = %d.\n", b);
    printf("Color(C) = %d.\n", c);
	printf("\n");
}

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

	// Set Period for color callback to 1s (1000ms)
	// Note: The callback is only called every second if the 
	//       color has changed since the last call!
	color_set_color_callback_period(&c, 1000);

	// Register color callback to function cb_color
	color_register_callback(&c,
	                              COLOR_CALLBACK_COLOR, 
	                              (void *)cb_color,
	                              NULL);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}