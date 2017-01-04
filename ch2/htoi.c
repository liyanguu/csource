#include <stdio.h>
#include <ctype.h>

/* htoi() - convert a string of hexadecimal digits into integer */
int htoi(char *s) {
	int c, n;
	
	if (*s == '0' && (*++s == 'x' || *s == 'X'))
		++s;
	for (n = 0; ; ++s)
		if (isdigit(c = tolower(*s)))
			n = 16 * n + (c - '0');
		else if (c >= 'a' && c <= 'f')
			n = 16 * n + (c + 10 - 'a');
		else
			break;
	return n;
}

/* squeeze - deletes any char in s1 that matches any char in s2 */
char *squeeze(char *s1, char *s2) {
	char *p, *p1, *p2;

	for (p = p1 = s1 ; *s1; ++s1) {
		for (p2 = s2; *p2 && *p2 != *s1; ++p2)
			;
		if (*p2 == '\0')
			*p1++ = *s1;
	}
	*p1 = '\0';
	return p;
}

char *any(char *s1, char *s2) {
	char *p2;

	for ( ; *s1; s1++)
		for (p2 = s2; *p2; p2++)
			if (*s1 == *p2)
				return s1;
	return NULL;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	return x & ~(~(~0 << n) << (p+1-n)) | (y & ~(~0 << n)) << (p+1-n);
}

int bitcnt(unsigned x) {
	int b;

	for (b = 0; x != 0; x &= x-1)
		++b;
	return b;
}

unsigned invert(unsigned x, int p, int n) {
	return x ^ (~(~0 << n) << (p+1-n));
}

unsigned rightrot(unsigned x, int n) {
	unsigned int rbit;
	int wordlen = bitcnt(~0);

	while (n-- > 0) {
		rbit = (x & 1) << wordlen-1;	/* save right most bit */
		x >>= 1;
		x |= rbit;
	}
	return x;
}

int lower(int c) {
	return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
