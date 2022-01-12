#pragma once
#include <iostream>
#include <string>
#include <winsock2.h>


enum class packetType {
	packet_init = 1
};

struct packet_t {
#pragma pack(push, 1)
	packetType type;
	char data[260];
#pragma pack(pop)

};

class networking_client {
private:
	WSADATA wsa;
	SOCKET s;
	std::string ip;
	u_short port;
	sockaddr_in server;

	void send_packet(const packet_t* p);

public:
	networking_client(const char* ip, u_short port);

	bool connect_to_server();
};

packet_t* create_init();