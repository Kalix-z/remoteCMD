#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include "networking_host.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define PORT 5001

SOCKET init_server() {
	WSADATA wsa;
	
	SOCKET sock, new_socket;
	struct sockaddr_in host, client;
	bool returnVal = true;


	// initializes the windows socket data with version 2.2
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		std::cerr << "Failed to initialize WSA (networking_host.cpp), error code: " << WSAGetLastError() << '\n';
		returnVal = false;
	}

	// initializes the actuall socket
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "Failed to initialize socket (networking_host.cpp), error code: " << WSAGetLastError() << '\n';
		returnVal = false;
	}

	// use standard internet for this connection
	host.sin_family = AF_INET;
	host.sin_addr.s_addr = INADDR_ANY;
	host.sin_port = htons(PORT);

	if (bind(sock, (sockaddr*)&host, sizeof(host)) == SOCKET_ERROR) {
		std::cerr << "Failed to bind socket (networking_host.cpp), error code: " << WSAGetLastError() << '\n';
		returnVal = false;
	}

	return sock;
}


SOCKET accept_connection(SOCKET s, void(*func)(SOCKET)) {
	// starts to listen for connections
	listen(s, 3);

	int c = sizeof(sockaddr_in);

	sockaddr_in client;
	SOCKET sock;



	while ((sock = accept(s, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
		std::cout << "Connection accepted\n";
		func(sock);
	}

	if (sock == INVALID_SOCKET) {
		std::cerr << "Failed to accept (networking_host.cpp), error code: " << WSAGetLastError();
	}
	return sock;
}

void handle_connection(SOCKET sock) {

	packet_t* client_init = (packet_t*)malloc(sizeof(packet_t));

	if (!client_init) {
		std::cerr << "Memory error";
		exit(-1);
	}

	// recive the init packet
	recv(sock, (char*)client_init, sizeof(packet_t), 0);

	std::cout << (int)client_init->type;

	free(client_init);
}