#include <condition_variable>
#include <iostream>
#include <mutex>
#include <signal.h>
#include <memory>

#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */
#include "tcp_server.h"
/**/

std::condition_variable cv;

void
signint_handler(int) {
	cv.notify_all();
}

void
on_new_message(const std::shared_ptr<tcp_client>& client, const tcp_client::read_result& res) {
	if (res.success) {
		std::cout << "Client recv data" << std::endl;
		client->async_write({ res.buffer, nullptr });
		client->async_read({ 1024, std::bind(&on_new_message, client, std::placeholders::_1) });
	}
	else {
		std::cout << "Client disconnected" << std::endl;
		client->disconnect();
	}
}


int
main(void) {
#ifdef _WIN32
	//! Windows netword DLL init
	WORD version = MAKEWORD(2, 2);
	WSADATA data;

	if (WSAStartup(version, &data) != 0) {
		std::cerr << "WSAStartup() failure" << std::endl;
		return -1;
	}
#endif // _WIN32 

	tcp_server s;
	s.start("127.0.0.1", 3001, [](const std::shared_ptr<tcp_client>& client) -> bool {
		std::cout << "New client" << std::endl;
		client->async_read({ 1024, std::bind(&on_new_message, client, std::placeholders::_1) });
		return true;
	});

	signal(SIGINT, &signint_handler);

	std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	cv.wait(lock);

#ifdef _WIN32
	WSACleanup();
#endif // _WIN32 

	return 0;
}
/**/