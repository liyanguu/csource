/* 2014-4-24
	copied form P65 trim()
	Exercise 3-4
*/


/* c control flow

logic control:

if (expression)
	statements


if (expression)
	statements
else
	statements


if (expression)
	statements
else if(expression)
	statements
else if(expression)
	statements
else
	statements


switch (expr) {
	case const-expr:
		statements
	case const-expr:
		statements
	...
	default:
		statements
}

loops:

while (expression)
	statements

for (expr1; expr2; expr3)
	statements

do {
	statements
} while (expr);

*/




#include <string.h>
#include <stdio.h>
#define LEN 100

int trim (char s[]) {
	int n;
	
	for (n = strlen(s) - 1; n >= 0; --n)
		if (s[n] != ' ' && s[n] != '\n' && s[n] != '\t')
			break;
	
	s[++n] = '\0';
	return 0;
}

/* absolute value for 32-bit integer */
/* use long to test int */
#define MIN64 -4294967296
#define MAX64 4294967295
int abs(long int n) {
	if (n > MAX64 || n < MIN64) {
		printf("overflow !\n");
		return 0;
	}
	return int(-n);
}	
	
main() {
	long int n;

	n = -4294967296;
	n = abs(n);
	printf("absolute value: %d", n);


	int i, c;
	char s[LEN];

	for (i = 0; i < LEN-1 && (c = getchar()) != EOF; ++i)
		s[i] = c;

	s[i] = '\0';

	trim(s);
	printf("%s\n", s);

	return 0;
}


		
