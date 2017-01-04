#include <stdio.h>
#include <stdlib.h>

void pagecopy(FILE *, FILE *, char *);

main(int argc, char *argv[]) {
	FILE *fp;

	if (argc == 1)
		pagecopy(stdout, stdin, "");
	else {
		while (--argc && (fp = fopen(*++argv, "r")) != NULL) {
			pagecopy(stdout, fp, *argv);
			fclose(fp);
		}
		if (argc) {
			fprintf(stderr, "page: can't open %s\n", *argv);
			exit(1);
		}
	}
	exit(0);
}

#define MAXSCR 22	/* max #line in one screen */
#define MAXLINE 1000

void pagecopy(FILE *dst, FILE *src, char *name) {
	int nline, npage;
	char line[MAXLINE];

	nline = npage = 0;
	while (fgets(line, MAXLINE, src) != NULL) {
		if (++nline == 1) {
			if (*name)
				fprintf(dst, "%s, ", name);
			fprintf(dst, "page %d\n", ++npage);
		}
		fprintf(dst, "%s", line);
		if (nline == MAXSCR-1)
			nline = 0;
	}
	if (nline)
		while (nline++ < MAXSCR-1) 
			putc('\n', dst);
}
