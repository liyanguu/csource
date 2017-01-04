/*******************************************************************
* TITLE: long.c
*
* FUNCTION: printout lines of more than 80 characters 
*
* CHANGE LOG:
* 	2016-3-7 *
*            8-10 modify to printout whole long line 
********************************************************************/

#include <stdio.h>

#define LONGLIN 80 

int getlin(char s[], int len);
void copy(char dst[], char src[]);

main() {
	int c, n;
	char line[LONGLIN+1];

	while (n = getlin(line, LONGLIN))
		if (line[n-1] != '\n') { /* longer than LONGLIN */
			printf("%s", line);
			while ((c = getchar()) != '\n' && c != EOF)
				putchar(c);
			if (c == '\n')
				putchar(c);	
		}
	return 0;
}

int getlin(char s[], int len) {
	int i, c, loop;

	for (i = 0, loop = 1; loop; )
		if (i < len - 1)
			if ((c = getchar()) != EOF)
				if (c != '\n')
					s[i++] = c;
				else
					loop = 0;
			else
				loop = 0;
		else
			loop = 0;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}	

void copy(char dst[], char src[]) {
	int i;

	for (i = 0; (dst[i] = src[i]) != '\0'; ++i)
		;
}
