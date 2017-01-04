/* copyed from K&R pp.22 */

#include <stdio.h>
#include <ctype.h>

void printrow(int startc, int starti, int lim, float *ftab);

main() {
	int c, i, j;
	float nwhite, nother;
	float ndigichar[36];

	nwhite = nother = 0;
	for (i = 0; i < 36; ++i)
		ndigichar[i] = 0;

	while ((c = getchar()) != EOF)
		if (isdigit(c))
			++ndigichar[c-'0'];	
		else if (isalpha(c))
			++ndigichar[tolower(c)-'a'+10];
		else if (isspace(c))
			++nwhite;
		else
			++nother;

	printf("digits =\n");
	printrow('0', 0, 10, ndigichar);
	printf("characters =\n");
	printrow('a', 10, 10, ndigichar);
	printrow('a'+10, 20, 10, ndigichar);
	printrow('a'+20, 30, 6, ndigichar);
	printf("white = %5.0f, other = %5.0f\n", nwhite, nother);
}

void printrow(int startc, int starti, int lim, float *ftab) {
	int i;

	for (i = 0; i < lim; ++i)
		printf("%5c ", startc + i);
	putchar('\n');
	for (i = 0; i < lim; ++i)
		printf("%5.0f ", ftab[starti + i]);
	putchar('\n');
}
