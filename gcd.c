/* FILENAME: gcd.c - greatest common divisor */
/* DATE: 2015-9-17 */

#include <stdio.h>
#include "strings.c"

/*
int getnum(void);
void printnum(int);
*/
int gcd(int n1, int n2);

#define LEN 10

main() {
	int n1, n2;
	char s[LEN];

	printf("input one number: ");
	getstring(s, LEN);
	n1 = str2num(s);

	printf("input another number: ");			
	getstring(s, LEN);

	n2 = gcd(n1, str2num(s));
	num2str(n2, s, LEN);
	printf("the greatest common divisor of them is: %s\n", s);
}

int getnum(void) {
	int c, n;
	n = 0;
	while ((c = getchar()) != '\n')
		n = n * 10 + c - '0';
	return n;
}	

#define BUFSIZE 100
void printnum(int n) {
	char buf[BUFSIZE];
	char *bufp = buf;
	for (*bufp = '\0'; n; n /= 10) 
		*++bufp = n % 10 + '0';
	for (; *bufp; --bufp)
		putchar(*bufp);
	return;
}
	
int gcd(int n1, int n2) {
	int r;

	if (n1 * n2 <= 0)
		return 0;

	while ((r = n1 % n2) != 0) {
		n1 = n2;
		n2 = r;
	}

	return n2;
}
