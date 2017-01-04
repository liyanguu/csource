#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>   /* for atoi */
#include <string.h>

#define MAXLINE 20000 /* max #lines to sort */
#define DIR     8     /* directory sort */
#define FOLD    4     /* ignore case */
#define DECR    2     /* sort in decreasing order */
#define NUMERIC 1     /* numeric sort */

int pos1 = 1; 
int pos2 = MAXLINE;
int option = 0;
char *lineptr[MAXLINE];

void quicksort(void *[], int, int, int (*)(void *, void *));
int cmpnum(char *, char *);
int cmpchar(char *, char *);
void readargs(int, char *[]);
char *substr(char *, int);
int readlines(char **, int);
void writelines(char **, int, int);

main(int argc, char *argv[]) {
	int nline;

	readargs(argc, argv);
	if ((nline = readlines(lineptr, MAXLINE)) >= 0) {
		quicksort((void **) lineptr, 0, nline-1,
		    (int (*)(void*,void*))(NUMERIC&option ? 
			cmpnum : cmpchar));
		writelines(lineptr, nline, option & DECR);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

void quicksort(void *v[], int left, int right,
		int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int i, int j);

	if (left >= right)    /* do nothing if array contains */
		return;       /* fewer than two elements */	
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; ++i)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last-1, comp);
	quicksort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int cmpnum(char *s, char *t) {
	double v1, v2;

	v1 = atof(substr(s, pos1));
	v2 = atof(substr(t, pos1));
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int cmpchar(char *s, char *t) {
	char a, b;
	int width = pos2-pos1+1;

	s = substr(s, pos1);
	t = substr(t, pos1);
	while (width-- > 0) {
		if (option & DIR) {
			while (*s && !isalnum(*s) && *s != ' ')
				s++;
			while (*t && !isalnum(*t) && *t != ' ')
				t++;
		}
		if (option & FOLD) {
			a = tolower(*s);
			b = tolower(*t);
		} else {
			a = *s;
			b = *t;
		}
		if (a == b && a == '\0')
			return 0;
		else if (a != b)
			return a - b;
		s++;
		t++;
	}
	return 0;
}

void readargs(int argc, char *argv[]) {
	int c;

	while (--argc > 0)
		if ((c = (*++argv)[0]) == '-' && !isdigit((*argv)[1]))
			while (c = *++argv[0])
				switch (c) {
				case 'n':
					option |= NUMERIC;
					 break;
				case 'r':
					option |= DECR;
					break;
				case 'f':
					option |= FOLD;
					break;
				case 'd':
					option |= DIR;
					break;
				default:
					printf("error: illegal option %c\n",c);
					argc = 0;
					break;
				}
		else if (c == '-') {
			if ((pos2 = atoi(++*argv)) < pos1) {
				printf("error: wrong pos2 %d\n", pos2);
				argc = 0;
			}
		} else if (c == '+') {
			if ((pos1 = atoi(++*argv)) < 1 || pos1 > pos2) {
				printf("error: wrong field %d\n", pos1);
				argc = 0;
			}
		} else
			argc = 0;
	if (argc) {
		printf("usage: sort -dfnr +pos1 -pos2\n");
		exit(1);
	}
}

char *substr(char *s, int p1) {
	while (*s && --p1 > 0)
		s++;
	return s;
}

/* 
void field(char *s, char *f) {
	int len = strlen(s);
	char *p;

	if (pos2 > 0 && pos2 < len)
		len = pos2;
	for (p = s + pos1; p < s + len; p++)
		if (dir) {
			if (isalnum(*p))
				*f++ = fold ? tolower(*p) : *p;
		} else
			*f++ = fold ? tolower(*p) : *p;
	*f = '\0';
}
*/
