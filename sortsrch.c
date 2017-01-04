#include "sortsrch.h"

void quicksort(void **v, int left, int right, PFI cmp) {
	int last;

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*cmp)(v[i], v[left]) < 0)
			swap(v, ++last, i)
	swap(v, left, last);
	quicksort(v, left, last-1);
	quicksort(v, last+1, right);	
}

void shellsort(void **v, int lim, PFI cmp) {
	int gap, i, j;

	for (gap = lim/2; gap > 0; gap /= 2)
		for (i = gap; i < lim; i++)
			for (j = i; j >= 0 
			  && (*cmp)(v, j, j-gap)<0; j -= gap)
				swap(v, j, j-gap);
}

void **bisearch(void **v, int lim, PFI cmp) {
	
}	

void swap(void **v, int i, int j) {
	void *t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}
