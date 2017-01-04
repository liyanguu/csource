/* 
key_count.c: 
	count C keyword
log:
	2015-5-3  copied form P133
	2016-8-4  modify getword
	     8-8  pointer version 
*/

struct key {
	char *keyword;
	int count;
} keytab[] = {
	"auto",		0,
	"break",	0,
	"case",		0,
	"char",		0,
	"const",	0,
	"continue",	0,
	"default",	0,
	"do",		0,
	"double",	0,
	"else",		0,
	"enum",		0,
	"extern",	0,
	"float",	0,
	"for",		0,
	"goto",		0,
	"if",		0,
	"int",		0,
	"long",		0,
	"register",	0,
	"return",	0,
	"short",	0,
	"signed",	0,
	"sizeof",	0,
	"static",	0,
	"struct",	0,
	"switch",	0,
	"typedef",	0,
	"union",	0,
	"unsigned",	0,
	"void",		0,
	"volatile",	0,
	"while",	0,
};	


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getword.h"

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
#define BUFSIZE 100

struct key *bisearch(char *, struct key *, int);

/* count C keywords */
main() {
	char word[MAXWORD+1];
	struct key *p;

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((p = bisearch(word, keytab, NKEYS)) != NULL)
				p->count++;
	for (p = keytab; p < keytab + NKEYS; p++)
		if (p->count > 0)
			printf("%6s: %5d\n", p->keyword, p->count);
	return 0;
}


/* bisearch(): find keyword in keytab[0], ... , keytab[n-1] */
struct key *bisearch(char* word, struct key *tab, int n) {
	int cond;
	struct key *low, *high, *mid;

	low = tab;
	high = &tab[n];
	while (low < high) {
		mid = low + (high - low)/2;
		if ((cond = strcmp(word, mid->keyword)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}
