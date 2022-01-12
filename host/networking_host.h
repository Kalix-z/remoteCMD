#pragma once
#include <winsock2.h>

SOCKET init_server();

SOCKET accept_connection(SOCKET s, void(*func)(SOCKET));

void handle_connection(SOCKET sock);

enum class packetType {
	packet_init = 1
};

struct packet_t {
#pragma pack(push, 1)
	packetType type;
	char data[260];
#pragma pack(pop)

};
