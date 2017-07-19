#include "error.h"
#include "logger.h"
#include "tcp_client.h"

//!
//! ctor & dtor
//!

tcp_client::tcp_client(void)
	: m_io_service(get_default_io_service())
	, m_disconnection_handler(nullptr) {
	__MC_LOG(debug, "create tcp_client");
}

tcp_client::~tcp_client(void) {
	__MC_LOG(debug, "destroy tcp_client");
	disconnect(true);
}

//!
//! custom ctor
//! build socket from existing socket
//!

tcp_client::tcp_client(tcp_socket&& socket)
	: m_io_service(get_default_io_service())
	, m_socket(std::move(socket))
	, m_disconnection_handler(nullptr) {
	m_is_connected = true;
	__MC_LOG(debug, "create tcp_client");
	m_io_service->track(m_socket);
}

//!
//! get host & port information
//!
const std::string&
tcp_client::get_host(void) const {
	return m_socket.get_host();
}

std::uint32_t
tcp_client::get_port(void) const {
	return m_socket.get_port();
}

//!
//! start & stop the tcp client
//!
void
tcp_client::connect(const std::string& host, std::uint32_t port) {
	if (is_connected()) { __MC_THROW(warn, "tcp_client is already connected"); }

	try {
		m_socket.connect(host, port);
		m_io_service->track(m_socket);
	}

	catch (const mc_error& e) {
		m_socket.close();
		throw e;
	}

	m_is_connected = true;
	__MC_LOG(info, "tcp_client connected");
}

void
tcp_client::disconnect(bool wait_for_removal) {
	if (!is_connected()) { return; }
	m_is_connected = false;
	m_io_service->untrack(m_socket);
	if (wait_for_removal) { m_io_service->wait_for_removal(m_socket); }
	m_socket.close();
	__MC_LOG(info, "tcp_client disconnected");
}

//!
//! Call disconnection handler
//!
void
tcp_client::call_disconnection_handler(void) {
	if (m_disconnection_handler) {
		__MC_LOG(debug, "call disconnection handler");
		m_disconnection_handler();
	}
}

//!
//! io service read callback
//!
void
tcp_client::on_read_available(fd_t) {
	__MC_LOG(info, "read available");
	read_result result;
	auto callback = process_read(result);
	if (!result.success) {
		__MC_LOG(warn, "read operation failure");
		disconnect();
	}
	if (callback) { callback(result); }
	if (!result.success) { call_disconnection_handler(); }
}

//!
//! io service write callback
//!
void
tcp_client::on_write_available(fd_t) {
	__MC_LOG(info, "write available");
	write_result result;
	auto callback = process_write(result);

	if (!result.success) {
		__MC_LOG(warn, "write operation failure");
		disconnect();
	}

	if (callback) { callback(result); }
	if (!result.success) { call_disconnection_handler(); }
}

//!

//! process read & write operations when available

//!

tcp_client::async_read_callback_t

tcp_client::process_read(read_result& result) {
	std::lock_guard<std::mutex> lock(m_read_requests_mtx);
	if (m_read_requests.empty()) { return nullptr; }
	const auto& request = m_read_requests.front();
	auto callback = request.async_read_callback;
	try {
		result.buffer = m_socket.recv(request.size);

		result.success = true;
	}
	catch (const mc_error&) {
		result.success = false;
	}

	m_read_requests.pop();
	if (m_read_requests.empty()) { m_io_service->set_rd_callback(m_socket, nullptr); }
	return callback;
}

tcp_client::async_write_callback_t
tcp_client::process_write(write_result& result) {
	std::lock_guard<std::mutex> lock(m_write_requests_mtx);
	if (m_write_requests.empty()) { return nullptr; }
	const auto& request = m_write_requests.front();
	auto callback = request.async_write_callback;
	try {
		result.size = m_socket.send(request.buffer, request.buffer.size());
		result.success = true;
	}

	catch (const mc_error&) {
		result.success = false;
	}

	m_write_requests.pop();
	if (m_write_requests.empty()) { m_io_service->set_wr_callback(m_socket, nullptr); }
	return callback;
}

//!
//! async read & write operations
//!

void
tcp_client::async_read(const read_request& request) {
	std::lock_guard<std::mutex> lock(m_read_requests_mtx);

	if (is_connected()) {
		m_io_service->set_rd_callback(m_socket, std::bind(&tcp_client::on_read_available, this, std::placeholders::_1));
		m_read_requests.push(request);
	}

	else {
		__MC_THROW(warn, "tcp_client is disconnected");
	}
}

void

tcp_client::async_write(const write_request& request) {
	std::lock_guard<std::mutex> lock(m_write_requests_mtx);

	if (is_connected()) {
		m_io_service->set_wr_callback(m_socket, std::bind(&tcp_client::on_write_available, this, std::placeholders::_1));

		m_write_requests.push(request);
	}

	else {
		__MC_THROW(warn, "tcp_client is disconnected");
	}
}

//!
//! socket getter
//!

tcp_socket&
tcp_client::get_socket(void) {
	return m_socket;
}

const tcp_socket&
tcp_client::get_socket(void) const {
	return m_socket;
}

//!
//! set on disconnection handler
//!
void
tcp_client::set_on_disconnection_handler(const disconnection_handler_t& disconnection_handler) {
	m_disconnection_handler = disconnection_handler;
}

//!
//! returns whether the client is currently running or not
//!
bool
tcp_client::is_connected(void) const {
	return m_is_connected;
}

//!
//! comparison operator
//!
bool
tcp_client::operator==(const tcp_client& rhs) const {
	return m_socket == rhs.m_socket;
}

bool
tcp_client::operator!=(const tcp_client& rhs) const {
	return !operator==(rhs);
}