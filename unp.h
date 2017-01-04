/* unp.h 
   2016-2-29 copy from UNIX network programming, pp784, D1 */

#if !defined(H_UNP)
#define H_UNP 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <time.h>
#include <unistd.h>

#define bzero2(ptr, n) memset(ptr, 0, n);
#define MAXLINE 4096
#define LISTENQ 1024
#define SA  struct sockaddr

int Socket(int family, int type, int protocol);
void Bind(int listenfd, SA *addr, socklen_t addrlen);
void Listen(int listenfd, int quesize);
int Accept(int sockfd, SA *addr, socklen_t *addrlen);
void Close(int fd);
int Write(int fd, char *s, size_t len); 

#endif
