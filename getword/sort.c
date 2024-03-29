#include <stdio.h>

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

char **bisearch(char **word, char *tab[], int n) {
	int cond;
	char **low, **high, **mid;

	low = tab;
	high = &tab[n];
	while (low < high) {
		mid = low + (high - low)/2;
		if ((cond = strcmp(*word, *mid)) < 0)
			high = mid;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return NULL;
}
