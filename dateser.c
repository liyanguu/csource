/* dateser.c - server program for getdate
   log:
	2016-3-8 copy from the UNP pp11, list 1.9 */

#include "unp.h"

int main(int argc, char **argv) {
	int listenfd, connfd, i;
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	char *bp;
	time_t ticks;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero2(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13); /* daytime server */
	Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
	Listen(listenfd, 0);
	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *)NULL, NULL); 
		ticks = time(NULL);
		snprintf(buf, MAXLINE, "%s", ctime(&ticks));
		bp = buf;
		for (i = strlen(buf); i > 0; --i)
			Write(connfd, bp++, 1); 	
		Close(connfd);
	}
}
