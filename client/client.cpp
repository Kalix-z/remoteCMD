#include <iostream>
#include <winsock2.h>
#include "networking_client.h"

int main() {
	std::cout << "Connecting to host...";

	networking_client client = networking_client("127.0.0.1", 5001);

	std::cout << "Connected!";

	client.connect_to_server();
}