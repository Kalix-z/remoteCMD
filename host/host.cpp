#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include "networking_host.h"

using std::string;



int main() {
	std::cout << "Initializing Server...\n";

	SOCKET temp = init_server();

	std::cout << "Initialized Server!\n";

	accept_connection(temp, handle_connection);
}