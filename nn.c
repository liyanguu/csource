/* filename: nn.c - return n^n */
/* date: 2015-10-13 */

long nn(int n) {
	int n1;
	long n2;

	if (n <= 0)
		return 0;
	for (n1 = n - 1, n2 = n; n1 > 0; --n1)
		n2 *= n;

	return n2;
}	
