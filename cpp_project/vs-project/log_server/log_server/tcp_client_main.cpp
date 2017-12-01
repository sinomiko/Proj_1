#include "tcp_client.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <signal.h>

#ifdef _WIN32
#include <Winsock2.h>
#endif // _WIN32 
/*
std::condition_variable cv;

void
signint_handler(int) {
    cv.notify_all();
}

void
on_new_message(tcp_client& client, const tcp_client::read_result& res) {
    if (res.success) {
        std::cout << "Client recv data" << std::endl;
        client.async_write({ res.buffer, nullptr });
        client.async_read({ 1024, std::bind(&on_new_message, std::ref(client), std::placeholders::_1) });
    }
    else {
        std::cout << "Client disconnected" << std::endl;
        client.disconnect();
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

    tcp_client client;
    client.connect("127.0.0.1", 3001);
    client.async_read({ 1024, std::bind(&on_new_message, std::ref(client), std::placeholders::_1) });

    signal(SIGINT, &signint_handler);

    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock);

#ifdef _WIN32
    WSACleanup();
#endif // _WIN32 

    return 0;
}
*/