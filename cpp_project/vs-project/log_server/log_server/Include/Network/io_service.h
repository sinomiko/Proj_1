#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>



#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#else
#include <sys/select.h>
#endif /* _WIN32 */

#include "Include/Network/self_pipe.h"
#include "Include/Network/tcp_socket.h"
#include "Include/Utils/thread_pool.h"

#ifndef __MC_IO_SERVICE_NB_WORKERS
#define __MC_IO_SERVICE_NB_WORKERS 1
#endif /* __MC_IO_SERVICE_NB_WORKERS */



class io_service {

public:
	//! ctor & dtor
	io_service(void);
	~io_service(void);

	//! copy ctor & assignment operator
	io_service(const io_service&) = delete;
	io_service& operator=(const io_service&) = delete;

public:
	//! callback handler typedef
	//! called on new socket event if register to io_service
	typedef std::function<void(fd_t)> event_callback_t;

	//! track & untrack socket
	void track(const tcp_socket& socket, const event_callback_t& rd_callback = nullptr, const event_callback_t& wr_callback = nullptr);
	void set_rd_callback(const tcp_socket& socket, const event_callback_t& event_callback);
	void set_wr_callback(const tcp_socket& socket, const event_callback_t& event_callback);
	void untrack(const tcp_socket& socket);

	//! wait until the socket has been effectively removed
	//! basically wait until all pending callbacks are executed
	void wait_for_removal(const tcp_socket& socket);

private:
	//! struct tracked_socket
	//! contains information about what a current socket is tracking
	struct tracked_socket {
		//! ctor
		tracked_socket(void)
			: rd_callback(nullptr)
			, wr_callback(nullptr) {}

		//! rd event
		event_callback_t rd_callback;
		std::atomic<bool> is_executing_rd_callback = ATOMIC_VAR_INIT(false);

		//! wr event
		event_callback_t wr_callback;
		std::atomic<bool> is_executing_wr_callback = ATOMIC_VAR_INIT(false);

		//! marked for untrack
		std::atomic<bool> marked_for_untrack = ATOMIC_VAR_INIT(false);

	};



public:

	//! poll worker function
	void poll(void);

	//! init m_poll_fds_info
	int init_poll_fds_info(void);

	//! process poll detected events
	void process_events(void);
	void process_rd_event(const fd_t& fd, tracked_socket& socket);
	void process_wr_event(const fd_t& fd, tracked_socket& socket);

private:

	//! tracked sockets
	std::unordered_map<fd_t, tracked_socket> m_tracked_sockets;

	//! whether the worker should stop or not
	std::atomic<bool> m_should_stop;

	//! poll thread
	std::thread m_poll_worker;

	//! callback workers
	thread_pool m_callback_workers;

	//! thread safety
	std::mutex m_tracked_sockets_mtx;

	//! data structure given to select
	std::vector<fd_t> m_polled_fds;
	fd_set m_rd_set;
	fd_set m_wr_set;

	//! condition variable to wait on removal
	std::condition_variable m_wait_for_removal_condvar;

	//! fd associated to the pipe used to wake up the poll call
	self_pipe m_notifier;
};



//! default io_service getter & setter
const std::shared_ptr<io_service>& get_default_io_service(void);
void set_default_io_service(const std::shared_ptr<io_service>&);





