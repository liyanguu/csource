/*
file name: text.c
log:
	2015-12-7  split from strings.c
	     12-26 write getword 
*/

#include <stdio.h>
#include <ctype.h>
#include "/home/liyang/include/text.h"

static int bp = 0;
static char buf[BUFSIZE]; 

int getcha(void) {
	return bp == 0 ? getchar() : buf[--bp];
}

void ungetcha(int c) {
	if (bp >= BUFSIZE)
		printf("input buffer overflow !\n");
	else
		buf[bp++] = c;
}

/* getstr.c - collects alphabetic and numeral strings
   return EOF or punctuation marks and newline */
int getstr(char s[]) {
	int i, c;	
	while ((c = getchar()) == ' ' || c == '\t') 
		;
	if (c == EOF)
		return EOF;
	i = 0;
	if (isalpha(c)) {
		s[0] = c;
		while (isalpha(s[++i] = c = getchar()))
			;
		s[i] = '\0';
		ungetc(c, stdin);
		return ALPH;
	}
	if (isdigit(c)) {
		s[0] = c;
		while (isdigit(s[++i] = c = getchar()))
			;
		s[i] = '\0';
		ungetc(c, stdin);
		return NUMB;
	}
	return c;
}

int getstring(char *s, int len) {
	char c;

	while(isspace(c = getchar()))
		;
	for( ; --len > 0 && !isspace(c) && c != EOF; c = getchar())
		*s++ = c;
	*s = '\0';
	return c;
}	

/* getword - page 136 */
int getword(char *word, int len) {
	int c;
	char *w = word;

	while (isspace(c = getcha()) || c == '/')
		if (isspace(c)) {
			continue;
		} else if ((*w = getcha()) != '*') {
			ungetcha(*w);
			*w++ = c;
			w = '\0';
			return c;	
		} else
			while ((c = getcha()) != EOF)
				if (c == '*' && getcha() == '/')
					break;
	}
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '\"') { 
		*w = '\0';
		return c;
	}
	if (isalpha(c)) {
		for ( ; --len > 0; ++w)
			if (!isalnum(*w = getcha())) {
				ungetcha(*w);
				break;
			}
	} else
		for ( ; --len > 0; ++w)
			if ((*w = getcha()) == c) {
				w++;
				break;
			} 
	*w = '\0';
	return word[0];
}

void escape(char *s, char *t) {
	while (*t) {
		switch(*t) {
		case ' ':
			*s++ = '\\', *s++ = 'b';
			break;
		case '\t':
			*s++ = '\\', *s++ = 't';
			break;
		case '\n':
			*s++ = '\\', *s++ = 'n';
			break;	
		default:
			*s++ = *t;
			break;
		}
		t++;
	}
	*s = '\0';
}

void unescape(char *s, char *t) {
	while (*t) {
		if (*t == '\\')
			switch (*++t) {
			case 'b':
				*s++ = ' ';
				break;
			case 't':
				*s++ = '\t';
				break;
			case 'n':
				*s++ = '\n';
				break;
			default:
				*s++ = '\\', *s++ = *t;
				break;
			}
		else
			*s++ = *t;
		if (*t == '\0')
			return;
		t++;
	}
	*s = '\0';
}

/* expand string like a-z 0-9 to a...z 0...9 */
void expand(char *dst, char *src) {
	int headc, i, j, k;
	headc = '\0';
	for (i = j = 0; src[i] != '\0'; ++i) {
		if (src[i] == '-') {
			++i;
			if ((isalpha(headc) && isalpha(src[i])) || (isdigit(headc) && isdigit(src[i]))) {
				/* expand */
				if (headc > src[i]) 
					for (k = headc - 1; k >= src[i]; --k)
						dst[j++] = k;
				else
					for (k = headc + 1; k <= src[i]; ++k)
						dst[j++] = k;		
				headc = '\0';
			}
			else if (src[i] == '\0') {
				dst[j++] = '-';
				dst[j] = '\0';
				return;
			}
			else {
				dst[j++] = '-';
				dst[j++] = headc = src[i];
			}
		}
		else 
			dst[j++] = headc = src[i];	
	}
	dst[j] = '\0';
}

