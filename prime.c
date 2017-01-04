/* prime.c - print out first 500 prime numbers */
/* 2015-6-12 */

#include <stdio.h>
#define NUMPRIME 500 

int main() {
	int buf1[NUMPRIME], i, j, k;

	buf1[0] = 2;
	i = 2; /* index of prime */
	j = 1;

	while (i <= 500) {
		for (k = 2; k < i; ++k)
			if ((2 * j + 1) % buf1[k - 1] == 0) /* not a prime */
				break;

		if (k == i) { /* find a prime */
			buf1[i - 1] = 2 * j + 1;
			++i;
		}

		++j;
	}
	
	for (i = 0; i < NUMPRIME; ++i)
		printf("%3d:\t%4d\n", i, buf1[i]);

	return 0;
}
