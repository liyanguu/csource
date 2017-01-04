/* file name: hist.c - histogram of occurance of alphabets in files
   log:
	2015-6-9   *
	2016-01-12 make it to draw the bar chart.  */

#include <stdio.h>

#define FROMATOZ 26
#define MAXLEV 30    /* max levels of bar */ 

int hist[FROMATOZ] = {0};

int isalpha2(char c);
char toupper2(char c);
int charcnt(FILE *);

int main(int argc, char *argv[]) {
	int c, len, max, i, total;
	FILE *fp;
	
	total = 0;
	if (argc == 1) {
		total = charcnt(stdin);
	} else 
		while (--argc > 0) {
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("error: can't open \"%s\"\n", *argv);
				return 1;
			}
			total += charcnt(fp);
			close(fp);
		}

	max = 0;
	for (i = 0; i < FROMATOZ; ++i)
		if (hist[i] > max)
			max = hist[i];

	printf("alphabet histogram:\n");
	for (i = 0; i < FROMATOZ; ++i) {
		printf("%c: %5d ", 'A' + i, hist[i]);
		if (hist[i] > 0)
			if ((len = hist[i] * MAXLEV / max) <= 1)
				putchar('-');
			else 
				while (len-- > 0)
					putchar('-');
		putchar('\n');
	}
	printf("TOTAL: %d\n", total);
	return 0;
}	

int isalpha2(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? 1 : 0;
}

char toupper2(char c) {
	return c >= 'a' && c <= 'z' ? 'A'+c-'a' : c;
}

int charcnt(FILE *fp) {
	int c, total;

	total = 0;
	while ((c = getc(fp)) != EOF)
		if (isalpha2(c)) {
			++total;
			++hist[toupper2(c) - 'A'];
		}
	return total;
}
