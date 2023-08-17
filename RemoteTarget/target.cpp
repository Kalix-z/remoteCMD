#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;

int main() {
	io_service service;
	tcp::socket socket(service);
	socket.connect(tcp::endpoint(ip::address::from_string("127.0.0.1"), 80));
	const string msg = "target says hi";
	boost::system::error_code err;
	write(socket, buffer(msg), err);
	if (err)
		std::cerr << "ERROR, failed to connect to client pc, error: " << err.message() << '\n';
	else
		std::cout << "SUCCESS, connected to client pc" << '\n';

	streambuf recv_buf;
	std::cout << "here";

	read_until(socket, recv_buf, '\n');
	if (err && err != error::eof)
		std::cerr << "ERROR, failed to recieve reply from client pc, error: " << err.message() << '\n';
	else {
		const char* data = buffer_cast<const char*>(recv_buf.data());
		std::cout << "data: " << data;
	}
	while(1);
}