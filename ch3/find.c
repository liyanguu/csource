#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/liyang/c/include/getlin.h"

int number, except;

int pattfile(char *, FILE *, char *);

main(int argc, char *argv[]) {
	FILE *fp;
	char *patt;
	int c, found;

	found = 0;
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				fprintf(stderr,
					"find: illegal option %c\n", c);
				found = -1;
				argc = 0;
				break;
			}
	if (argc < 1)
		fprintf(stderr, "Usage: find -xn patt\n");
	else if (argc == 1)
		found = pattfile(argv[0], stdin, "");
	else {
		patt = argv[0];
		while (--argc && (fp = fopen(*++argv, "r")) != NULL) {
			found += pattfile(patt, fp, *argv);
			fclose(fp);
		}
		if (argc) {
			fprintf(stderr, "find: can't open %s\n", *argv);
			found = -2;
		}
	}
	exit(found);
}

#define MAXLINE 1000

char line[MAXLINE];

/* pattfile: print out all lines in file fp 
	which contain pattern s, return #lines found */
int pattfile(char *s, FILE *fp, char *name) { 
	int nline, nfound;

	nfound = nline = 0;
	while (fgets(line, MAXLINE, fp) != NULL) {
		nline++;
		if ((strindex(line, s) != NULL) != except) {
			nfound++;
			if (*name)
				printf("%s: ", name);
			if (number)
				printf("%d: ", nline);
			printf("%s", line);
		} 
	}
	return nfound;
}
