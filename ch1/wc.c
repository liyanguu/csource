/*************************************************************
* TITLE: word_count.c
*
* FUNCTION: counts lines, characters, words from standard input
* 
* CHANGE LOG:
*	2015-4-14 copied form THE C PROGRAMMING LANGUAGE
**************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define IN  1
#define OUT 0

void count(FILE *, char *);

double nltotal, nwtotal, nctotal;

int main(int argc, char **argv) {
	FILE *fp;
	char *progname = *argv;
	int nfile = 0;

	if (argc == 1)
		count(stdin, "");
	else
		while (--argc > 0) {
			if ((fp=fopen(*++argv, "r")) == NULL) {
				printf("%s: can't open %s\n",
					progname, *argv);
				exit(1);
			}
			nfile++;
			count(fp, *argv);
			fclose(fp);
		}
	if (nfile > 1)
		printf("%6.0f %6.0f %6.0f %s\n", 
			nltotal, nwtotal, nctotal, "总用量");
	exit(0);
}

void count(FILE *fp, char *name) {
	int c, state;
	double nl, nc, nw;

	state = OUT;
	nl = nc = nw = 0;
	while ((c = getc(fp)) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\t' || c == '\n' || !isalnum(c))
			state = OUT;
		else if (state == OUT) {
			++nw;
			state = IN;
		} 
	}
	nltotal += nl;
	nwtotal += nw;
	nctotal += nc;
	printf("%6.0f %6.0f %6.0f %s\n", nl, nw, nc, name);
}
