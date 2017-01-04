/*
file name: numbers.c
log:
	2015-10-13 write nn
	     12-12 change to numbers.c, write power
*/

long power(int pow, int n) {
	long n1;

	if (pow < 0 || n == 0)
		return 0L;
	for (n1 = 1L; pow-- > 0; n1 *= n)
		;
	return n1;
}
