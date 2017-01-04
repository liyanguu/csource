/*
file name: search.c
log:
	2015-12-25 merry christmas !
	           write binsearch
*/

#include "/home/liyang/include/strings.h"
#include "/home/liyang/include/search.h"

int binsearch(char *word, struct key tab[], int n) {
	int cond;
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = cmpstr(word, tab[mid].word)) > 0)
			low = mid + 1;
		else if (cond < 0)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

