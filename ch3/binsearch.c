/**********************************************************
/ TITLE: binsearch.c
/
/ CHANGE LOG:
/ 	2015-4-16	COPIED FROM THE C PROGRAMMING LANGUAGE
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* header for binsearch() */
int monosearch(int k, int v[], int lim);
int binsearch(int k, int v[], int lim);
int binsearch2(int k, int v[], int lim);
int getstring(char s[], const int lim);
/* --------------------- */

#define MAX 1000000
#define LEN 100

main() {
	int i, x, list[MAX], p;
	char s[LEN];	
	time_t start, end;


	for (i = 0; i < MAX; ++i)
		list[i] = i - MAX / 2;	/* initialize */

	while (getstring(s, LEN) > 0) {
		x = atoi(s);

		/* start timming */ 
		time(&start);
		p = binsearch(x, list, MAX);			
	 	/* stop */
		time(&end);
		printf("%-10s %d %.0fs\n", 
		"binary search", p, difftime(start, end));

		time(&start);
		p = monosearch(x, list, MAX);			
		time(&end);
		printf("%-10s %d %.0fs\n", 
		"mono search", p, difftime(start, end));

		time(&start);
		p = binsearch2(x, list, MAX);			
	 	/* stop */
		time(&end);
		printf("%-10s %d %.0fs\n", 
		"binary search 2", p, difftime(start, end));
	}
}



/* function definitions */

#include <ctype.h>
int getstring(char s[], const int lim) {
	int i;
	char c;

	for (i = 0; i < lim-1 && !isspace(c = getchar()) && c!=EOF; ++i)
		s[i] = c;
	s[i] = '\0';
	return i;
}

int monosearch(int k, int v[], int limt) {
	int i;

	for (i = 0; i < limt; ++i)
		if (k == v[i]) return i; /* match */

	return -1; /* mismatch */
}

int binsearch(int x, int v[], int lim) {
	int low, high, mid;

	low = 0;
	high = lim - 1;
		
	while (low <= high) {
		mid = (low + high)/2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	
	return -1;	/* mismatch */
}

int binsearch2(int x, int *v, int lim) {
	int low, high, mid;

	low = 0;
	high = lim-1;
	while (low <= high && v[mid = (low+high)/2] != x)
		if (v[mid] > x)
			high = mid-1;
		else
			low = mid+1;
	if (v[mid] == x)
		return mid;
	return -1;
}
