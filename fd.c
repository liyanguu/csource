#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 5

main() {
	char buf[BUFSIZE+1];
	int fd, n;

	fd = open("text.txt", O_RDONLY);
	printf("%d", fd);
	while ((n = read(fd, buf, BUFSIZE)) > 0) {
		printf("\n%d ", n);
		buf[n] = '\0';
		printf("%s", buf);
	}	
	return 0;
}
