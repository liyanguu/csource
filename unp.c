#include "unp.h"

int Socket(int family, int type, int protocol) {
	int n;

	if ((n = socket(family, type, protocol)) < 0)
		error(-1, errno, "socket error");
	return n;
}
	
void Bind(int sockfd, SA *addr, socklen_t addrlen) {
	if (bind(sockfd, addr, addrlen) == -1)
		error(-1, errno, "bind error");
}

void Listen(int sockfd, int backlog) {
	if (listen(sockfd, backlog) == -1)
		error(-1, errno, "listen error");
}

int Accept(int sockfd, SA *addr, socklen_t *addrlen) {
	int n; 

	if ((n = accept(sockfd, addr, addrlen)) < 0)
		error(-1, errno, "accept error");
	return n;
}

int Write(int fd, char *s, size_t len) {
	int n;

	if ((n = write(fd, s, len)) < 0)
		error(-1, errno, "write error");
	return n;
}

void Close(int fd) {
	if (close(fd) == -1)
		error(-1, errno, "close error");
}	
