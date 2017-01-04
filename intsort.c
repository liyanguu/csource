/*
file name: intsort.c
log:
	2015-12-31
*/

#include <stdio.h>
#include "/home/liyang/include/sort.h"

#define MAXNUM 100

main() {
	int i, n;
	int array1[MAXNUM];
	int array2[MAXNUM];
	int array3[MAXNUM];	
	
	for (i = 0; i < MAXNUM && (n = getnum()) != EOF; i++)
		array1[i] = array2[i] = array3[i] = n;
	bubblesort(array1, i);
	selectsort(array2, i);
	insertsort(array3, i);
	for (n = 0; n < i; n++) {
		printf("%d ", array1[n]);
		printf("\n");
		printf("%d ", array2[n]);
			
	
