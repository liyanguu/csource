/* getdate6.c - ip v6 version of getdate
   log:
   	2016-3-8  * */

#include "unp.h"

#define bzero2(ptr, n) memset(ptr, 0, n)
#define MAXLINE 4096	
#define SA   struct sockaddr

int main (int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE+1];
	struct sockaddr_in6 servaddr;

	if (argc != 2) {
		printf("usage: %s <ip address>\n", argv[0]);
		return -1;
	}
	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
		printf("socket error\n");
		return -1;
	}
	bzero2(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(13); /* daytime server */
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		return -1;
	}
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
		printf("connect error\n");
		return -1;
	}
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = '\0';
		printf("%s", recvline);
	}
	if (n < 0) {
		printf("read error\n");
		return -1;
	}
	return 0;
}
