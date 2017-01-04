/* file name: test_sort.c
   log:
	2016-2-18: create */

#include <stdio.h>
#include "sort.h"
#include "inout.h"

#define MAXNUM 50000

main() {
	int i, n, v[MAXNUM];

	for (n = 0; n < MAXNUM && getnum(&v[n]) > 0; n++)
		;
	printf("input size: %d\n", n);
	for (insertsort2(v, n), i = 0; i < n; i++)
		printf("%d ", v[i]);
}
