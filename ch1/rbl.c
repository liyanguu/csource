/* rbline.c - remove tailing blanks and tabs from input line,
	delete all-blank lines. 
   log:
	2016-3-10 * */

#include <stdio.h>    
#include <ctype.h>
#define MAXLINE 2000		

int getlin(char line[], int lim);
int rmtail(char line[], int lim);

main() {                 
	int n;
	char line[MAXLINE+1];

	while (n = getlin(line, MAXLINE))
		if (rmtail(line, n))
			printf("%s$\n", line);
	return 0;
}                            

int rmtail(char s[], int len) {
	while (--len >= 0 && isspace(s[len]))
		;				
	s[++len] = '\0';
	return len;
}

#define TRUE 1
#define FALSE 0
int getlin(char s[], int len) {
	int i, c, loop;

	loop = TRUE;
	i = 0;
	while (loop) {
		loop = FALSE;
		if (i < len - 1)
			if ((c = getchar()) != EOF)
				if (c != '\n') {
					s[i++] = c;
					loop = TRUE;
				}
	}
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}			
