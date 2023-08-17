#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;

string read(tcp::socket& socket);
void send(tcp::socket& socket, string msg);


int main() {
    io_service service;
    //listen for new connection
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 80));
    //socket creation 
    tcp::socket socket(service);
    //waiting for connection
    acceptor.accept(socket);
    //read operation
    string message = read(socket);
    std::cout << message << '\n';
    //write operation
    send(socket, "Hello From client!\n");
    std::cout << "Client sent Hello message to Target!" << '\n';
    while (1);
}


string read(tcp::socket& socket) {
	streambuf buf;
	read(socket, buf, transfer_all());
    string data = buffer_cast<const char*>(buf.data());
    return data;
}

void send(tcp::socket& socket, string msg) {
	const string m = msg + '\n';
	std::cout << write(socket, buffer(m));
}