#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 5

main() {
	char buf[BUFSIZE+1];
	int fd, n;

	fd = open("text.txt", O_RDONLY);
	printf("%d %d %d %d %d\n", fd, read(fd, buf, BUFSIZE), read(fd, buf, BUFSIZE), read(fd, buf, BUFSIZE), read(fd, buf, BUFSIZE));
	close(fd);
	return 0;
}
