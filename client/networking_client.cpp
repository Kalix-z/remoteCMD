#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "networking_client.h"
#pragma comment(lib,"ws2_32.lib") //Winsock Library
using std::string;

networking_client::networking_client(const char* _ip, u_short _port) {

	ip = _ip;
	port = _port;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		std::cout << "Failed to initialize WSAdata (networking_client.cpp), error code: " << WSAGetLastError();
	}

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		std::cout << "Failed to initialize Socket (networking_client.cpp), error code: " << WSAGetLastError();
	}

	server.sin_addr.s_addr = inet_addr(_ip);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
}

bool networking_client::connect_to_server() {
	bool result = connect(s, (sockaddr*)&server, sizeof(server));
	packet_t* init_packet = create_init();
	send_packet(init_packet);
	free(init_packet);
	return result;
}


void networking_client::send_packet(const packet_t* p) {
	send(s, (const char*)p, sizeof(packet_t), 0);
}

packet_t* create_init() {
	packet_t* p = (packet_t*)malloc(sizeof(packet_t));
	if (!p) {
		std::cerr << "memory error\n";
		exit(-1);
	}
	p->type = packetType::packet_init;

	return p;
}

