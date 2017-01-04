#include <stdio.h>

#define MAXLINE 1000

int strindex(char *s, char *pattern);
int strrindex(char *s, char *pattern);

main(int argc, char **argv) {
	char line[MAXLINE];
	int found = 0, col;

	while (getlin(line, MAXLINE) > 0)
		if ((col = strrindex(line, argv[1])) >= 0) {
			printf("%d: %s", col, line);
			found++;
		}
	return found;
}

int strindex(char *s, char *t) {
	int i, j, k;
	
	for (i = 0; s[i]; i++) {
		for (j = i, k = 0; t[k] && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

int strrindex(char *s, char *t) {
	char *p, *q, *r;
	int pos = -1;
	
	for (p = s; *p; p++) {
		for (q = p, r = t; *r && *q == *r; q++, r++)
			;
		if (r > t && *r == '\0')
			pos =  p - s;
	}
	return pos;
}
