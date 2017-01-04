/* cat2 - system calls version */

#include <stdio.h>
#include <stdlib.h>	/* for exit() */
#include <fcntl.h>

char *prog;	/* prog name for errors */

void filecopy(int, int);
void err(char *, ...);

main(int argc, char *argv[]) {
	int fd;
	prog = argv[0];

	if (argc == 1)	/* no args; copy standard input */
		filecopy(1, 0);
	else
		while (--argc)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				err("%s: can't open file %s\n", prog, *argv);
			} else {
				filecopy(1, fd);
				close(fd);
			}
	exit(0);
}	

#define BUFSIZE 1024

/* filecopy: copy file src to file dst, system call version */
void filecopy(int dst, int src) {
	int n;
	char buf[BUFSIZE];

	while ((n = read(src, buf, BUFSIZE)) > 0)
		if (write(dst, buf, n) != n)
			err("%s: write error", prog);
}

#include <stdarg.h>

/* err: print out error message and exit */
void err(char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	va_end(ap);
	exit(1);
}
