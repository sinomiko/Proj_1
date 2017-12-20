#include <winsock2.h>
#include <fcntl.h>
#include <iostream>

#include "Include/Network/self_pipe.h"
#include "Include/Network/self_pipe.h"
#include "Include/Utils/error.h"
#include "Include/Utils/typedefs.h"

//!
//! ctor & dtor
//!
self_pipe::self_pipe(void)
	: m_fd(__MC_INVALID_FD) {
	//! Create a server
	m_fd = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (m_fd == __MC_INVALID_FD) { __MC_THROW(error, "fail socket()"); }

	unsigned long flags = 1;
	ioctlsocket(m_fd, FIONBIO, &flags);

	//! Bind server to localhost
	struct sockaddr_in inaddr;
	memset(&inaddr, 0, sizeof(inaddr));
	inaddr.sin_family = AF_INET;
	inaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	inaddr.sin_port = 0;
	if (bind(m_fd, (struct sockaddr*) &inaddr, sizeof(inaddr)) == SOCKET_ERROR) { __MC_THROW(error, "fail bind()"); }

	//! Retrieve server information
	m_addr_len = sizeof(m_addr);
	memset(&m_addr, 0, sizeof(m_addr));
	if (getsockname(m_fd, &m_addr, &m_addr_len) == SOCKET_ERROR) { __MC_THROW(error, "fail getsockname()"); }

	//! connect read fd to the server
	if (connect(m_fd, &m_addr, m_addr_len) == SOCKET_ERROR) { __MC_THROW(error, "fail connect()"); }
}

self_pipe::~self_pipe(void) {
	closesocket(m_fd);
}

//!
//! get rd/wr fds
//!
fd_t
self_pipe::get_read_fd(void) const {
	return m_fd;
}

fd_t
self_pipe::get_write_fd(void) const {
	return m_fd;
}

//!
//! notify
//!
void
self_pipe::notify(void) {
	(void)sendto(m_fd, "a", 1, 0, &m_addr, m_addr_len);
}

//!
//! clr buffer
//!
void
self_pipe::clr_buffer(void) {
	char buf[1024];
	(void)recvfrom(m_fd, buf, 1024, 0, &m_addr, &m_addr_len);
}