/**********************************************************
/ TITLE: binary_search.c
/
/ CHANGE LOG:
/ 	2015-4-16	COPIED FROM THE C PROGRAMMING LANGUAGE
**********************************************************/

#include <stdio.h>

int binsearch(const int x, const int v[], const int LIM) 
{
	int low, high, mid;

	low = 0;
	high = LIM - 1;
		
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
	
int binsearch2(const int x,const int v[], const int LIM)
{
	int low, high, mid;
	low = 0;
	high = LIM -1;
	mid = (LIM - 1)/2;
	
	while ((low <= high) && x != v[mid]) {
		if (x < v[mid])
			high = mid - 1;
		else 
			low = mid + 1;

		mid = (high + low)/2;
	}

	if (low <= high)
		return mid;	/* x matched */
	else
		return -1;	/* x mismatched */
}

main()
{
	#define MAX 1000000

	int list[MAX], i;
	for (i = 0; i < MAX; ++i)
		list[i] = i;	/* initiablize */
	
	/* start timming */ 
	int p = binsearch(0, list, MAX);			
	printf("%d\n", p);
	/* stop timming */

	/* start timming */
	int p2 = binsearch2(0, list, MAX);
	printf("%d\n", p2);
	/* stop */
}
