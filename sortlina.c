/* array version */

#include <stdio.h>
#include <string.h>
#include "getlin.h"

#define MAXLINE 20000 
#define BUFSIZE 1000000

char *lineptr[MAXLINE];
char buf[BUFSIZE];

void quicksort(char *lineptr[], int left, int right);

main() {
	int nline;
	
	if ((nline = readlinesa(lineptr, MAXLINE, buf, BUFSIZE)) >= 0)
		quicksort(lineptr, 0, nline-1);
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
	writelines(lineptr, nline);
	return 0;
}

void quicksort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)    /* do nothing if array contains */
		return;       /* fewer than two elements */	
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; ++i)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last-1);
	quicksort(v, last+1, right);
}

void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
