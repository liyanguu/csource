/*
file name: keycount.c
log:
	2015-12-26 create
*/

struct key {
	char *word;
	int count;
};

struct key keytab[] = {
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"switch", 0,
	"typedef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
};

#include <stdio.h>
#include <ctype.h>
#include "/home/liyang/include/strings.h"
#include "/home/liyang/include/text.h"

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key *binsearch(char *, struct key *, int);

main() {
	struct key *kp;
	char word[MAXWORD];

	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((kp = binsearch(word, keytab, NKEYS)) != NULL)
				kp->count++;
	for (kp = keytab; kp < keytab + NKEYS; kp++)
		printf("%10s %d\n", kp->word, kp->count);
	return 0;
} 

struct key *binsearch(char *name, struct key *tab, int n) {
	int cond;
	struct key *low = &tab[0]; 
	struct key *high = &tab[n]; 
	struct key *mid;

	while (low < high) {
		mid = low + (high - low) / 2;
		if ((cond = cmpstr(name, mid->word)) > 0)
			low = mid + 1;
		else if (cond < 0)
			high = mid;
		else
			return mid;
	}
	return NULL;
}	
