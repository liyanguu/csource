/* file name: getdate.c - get time/date from a time server
   log:
	2016-2-28 copy from UNIX network programming, pp4, list 1.5 */

#include "unp.h"

int main (int argc, char **argv) {
	int sockfd, n, i;
	char recvline[MAXLINE+1];
	struct sockaddr_in servaddr;

	if (argc != 2) {
		printf("usage: %s <ip address>\n", argv[0]);
		return -1;
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error(-1, errno, "socket error");
	bzero2(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13); /* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		error(-1, errno, "inet_pton error");
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		error(-1, errno, "connect error");
	i = 0;
	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = '\0';
		printf("%s", recvline);
		++i;
	}
	if (n < 0)
		error(-1, errno, "read error");
	printf("read: %d\n", i);
	return 0;
}
