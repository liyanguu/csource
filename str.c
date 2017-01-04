/* file name: str.c

   change log:
	2015-5-5   write expand.c
	2015-11-26 create 
	2015-11-29 write revstr2
	2015-12-01 modify copynstr, num2str returns char *
	2015-12-05 write unescape
	2015-12-07 move expand, escape, unescape, getstring to text.c,
	           modify pendstr, pendnstr, copystr...
	2015-12-26 change the counting of cmpnstr 
	2016-3-2   move other "#include" lines to str.h
	2016-9-1   test isupper, tolower, cmpnstr */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "str.h"

/* return string length */
int strlength(char *s) {
	char *t = s;

	while (*s)
		s++;
	return s - t;
}

/* if t is at the end of s, return 1, else return 0 */
int strend(char *s, char *t) {
	char *send = s + strlength(s) - 1;
	char *tend = t + strlength(t) - 1;

	for (; send >= s && tend >= t && *send == *tend; --send, --tend)
		if (tend == t)
			return 1;
	return 0;
}

char *strindex(char *s, char *t) {
	char *ps, *pt;

	for ( ; *s; ++s) {
		for (ps = s, pt = t; *pt && *pt == *ps; ++pt, ++ps)
			;
		if (pt > t && *pt == '\0')
			return ps;
	}
	return NULL;
}

char *strrindex(char *s, char *t) {
	char *bs;

	bs = s;
	for (s += strlength(s) - strlength(t); s >= bs; --s)
		if (strindex(s, t) != NULL)
			return s;
	return NULL;
}
		
/* strcat2: concatenate string s and string t (s first in order) */
char* strcat2(char* s, char* t) {
	char *temp, *temp2;
	temp2 = temp = (char *)malloc(strlength(s) + strlength(t) + 1);
	while (*temp = *s) {
		temp++;
		s++;
	}
	while (*temp = *t) {
		temp++;
		t++;
	} 
	return temp2;
}


/* convert integer into decimal string,
   the result has at most 'len' digits (including '-' if negative) */
char *num2str(int n, char *s, int len) {
	int sign;
	char *p = s + (len - 1);

	if ((sign = n) < 0)
		n = -n;
	do
		*s++ = n % 10 + '0';
	while ((n /= 10) && s < p); 
	if (s < p && sign < 0)
		*s++ = '-';
	*s = '\0';
	return revstr(p - (len - 1));
}

/* append string t to the end of string s */
char *pendstr(char *s, char *t) {
	char *p = s + strlength(s);

	copystr(p, t);
	return s;
}			

char *pendnstr(char *s, char *t, int n) {
	char *p;

	for (p = s + strlength(s); n-- > 0 && (*p++ = *t++); )
		;
	*p = '\0';
	return s;
}	

char *copystr(char *s, const char *t) {
	char *p = s;

	while (*p++ = *t++)
		;
	return s;
}

char *copynstr(char *s, const char *t, int n) {
	char *p = s;

	while (n-- > 0 && (*p++ = *t++)) 
		;
	while (n-- > 0)
		*p++ = '\0';
	*p = '\0';
	return s;
}

char *revstr(char *s) {
	char *t, *p;

	for (p = s, t = s + (strlength(s) - 1); p < t; ++p, --t)
		swapt(char, *p, *t)
	return s;
}	

/* compare s to t, return 0 if s == t, <0 if s < t, or >0 if s > t */
int cmpstr(char *s, char *t) {
	for ( ; *s == *t && *s != '\0'; ++s, ++t)
		;
	return *s - *t;
}

int cmpnstr(char *s, char *t, int n) {
	for ( ; *s == *t; ++s, ++t)
		if (--n <= 0 || *s == '\0')
			return 0;
	return *s - *t;
}

char *rmhead(char *s) {
	while (isspace(*s))
		++s;
	return s;
}

int trim(char *s) {
	char *p;

	for (p = s + strlength(s) - 1; p >= s && isspace(*p); --p)
		;
	*++p = '\0';
	return p - s;
}

double str2flt(char *s) {
	double val, power, pow2(int, int);
	int index, sign;

	for ( ; isspace(*s); ++s)
		;
	sign = *s == '-' ? -1 : 1;
	if (*s == '+' || *s == '-')
		++s;
	for (val = 0.0; isdigit(*s); ++s)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		++s;
	for (power = 1.0; isdigit(*s); ++s) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	val *= sign / power;
	if (*s == 'e' || *s == 'E')
		++s;
	sign = *s == '-' ? -1 : 1;
	if (*s == '-' || *s == '+')
		++s;
	for (index = 0; isdigit(*s); ++s)
		index = 10 * index + (*s - '0');
	if (sign < 0)
		val /= pow(10, index);
	else
		val *= pow(10, index);
	return val;
}

int str2num(char *s) {
	int sign, n;

	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		++s;
	for (n = 0; isdigit(*s); ++s)
		n = n * 10 + *s - '0';
	return n * sign;
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

/* aisupper: return 1 if c is upper case in ASCII, 0 otherwise */
int aisupper(int c) {
	return c >= 'A' && c <= 'Z';
}

int atolower(int c) {
	return aisupper(c) ? c - 'A' + 'a' : c;
}
