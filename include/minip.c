/* 

log: 	
	2015-9-17 * 
	2016      
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define ABS(x) (((x) < 0) ? -(x) : (x))

void qsort(int *, int, int);
int bsearch(int x, int v[], int n);
int bsearch2(int x, int v[], int n);
double atof(char *s);
int atoi(char *s);
int htoi(char *s);			/* chapter 2 */
int btoi(char *s, int base);
int any(char s1[], char s2[]);		/* chapter 2 */
char *squeeze(char s1[], char s2[]);	/* chapter 2 */
void unescape(char *s, char *t);
void escape(char *s, char *t);
void expand(char *s, char *t);
void itoar(int, char *);
void itos(int, char *, int);
void itob(int, char *, int);
void printd(int);
void printx(char, int);
void miniprintf(char *fmt, ...);
void reverse(char *s);
void reverser(char *);

double atof(char *s) {
	double val, power, sign, pow2(int, int);
	int index;

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
	sign = (*s == '-') ? -1 : 1;
	if (*s == '-' || *s == '+')
		++s;
	for (index = 0; isdigit(*s); ++s)
		index = 10 * index + (*s - '0');
	if (sign < 0)
		val /= pow2(10, index);
	else
		val *= pow2(10, index);
	return val;
}

int atoi(char *s) {
	return (int) atof(s);
}

double pow2(int base, int n) {
	double p;

	for (p = 1.0; n > 0; --n)
		p *= base;
	return p;
}

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

/* btoi - convert base-decimal s into integer,  base <= 10 */
int btoi(char *s, int base) {
	int n;

	for (n = 0; *s >= '0' && *s <= '0'+base-1; s++)
		n = base * n + *s - '0';
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

int any(char s1[], char s2[]) {
	int i, j;

	for (i = 0; s1[i] != '\0'; ++i)
		for (j = 0; s2[j] != '\0'; ++j)
			if (s1[i] == s2[j])
				return i;
	return -1;
}

int bsearch2(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while (low <= high && x != v[mid]) {
		if (x > v[mid])
			low = mid + 1;
		else
			high = mid - 1;
		mid = (low + high) / 2;
	}
	if (x == v[mid])
		return mid;	/* found match */
	else
		return -1;	/* no match */
}

int bsearch(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x > v[mid])
			low = mid + 1;
		else if (x < v[mid])
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

/* convert escape sequences to real chars when coping from t to s */
void unescape(char *s, char *t) {
	int len;

	for (; *s = *t; s++, t++)
		if (*t == '\\')
			switch (*++t) {
			case 't':
				*s = '\t';
				break;
			case 'n':
				*s = '\n';
				break;
			case 'b':
				*s = '\b';
				break;
			case '\'':
				*s = '\'';
				break;
			case '\\':
				break;
			case 'f':
				*s = '\f';
				break;
			case 'r':
				*s = '\r';
				break;
			case 'v':
				*s = '\v';
				break;
			case 'a':
				*s = '\a';
				break;
			case '?':
				*s = '\?';
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				len = 0;
				while (*t >= '0' && *t <= '7') {
					len++;
					t++;
				}
				s += sprintf(s, "%d", btoi(t-len, 8))-1;
				t--;
				break;
			case 'x':
				t++;
				len = 0;
				while (*t >= '0' && *t <= '9' ||
					*t >= 'a' && *t <= 'f') {
					len++;
					t++;
				}
				s += sprintf(s, "%d", htoi(t-len))-1;
				t--;
				break;	
			default:
				*s = *t;
				break;
			}
}

/* convert invisible chars into escape sequence as it copies t to s */
void escape(char *s, char *t) {
	for ( ; *s = *t; s++, t++) 
		switch (*s) {
		case '\t':
			*s++ = '\\';
			*s = 't';
			break;
		case '\n':
			*s++ = '\\';
			*s = 'n';
			break;
		case '\\':
			*++s = '\\';
			break;
		case '\b':
			*s++ = '\\';
			*s = 'b';
			break;
		}
}

void expand(char *s, char *t) {
	char c;

	while (c = *s++)
		if (*s == '-' && *(s+1) >= c)
			for (++s; c < *s; *t++ = c++)
				;
		else
			*t++ = c;
	*t = '\0';
}

void itob(int n, char *s, int b) {
	int r, sign;
	char *p = s;

	sign = n;
	do {
		r = ABS(n % b);
		*s++ = (r > 9) ? 'a' + r - 10 : '0' + r;
	} while (n /= b);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(p);
}

void printd(int n) {
	if (n < 0) {
		putchar('-');
		n = -n;
	}	
	if (n / 10)  /* n / 10 > 0 */
		printd(n / 10);
	putchar(n % 10 + '0');
}

void itoar(int n, char *s) {
	static char *p;

	if (n / 10)
		itoar(n/10, s);
	else {
		p = s;
		if (n < 0)
			*p++ = '-';
	}
	*p++ = ABS(n % 10) + '0';
	*p = '\0';
}

void itos(int n, char *s, int w) {
	char *p = s;
	int sign = n;

	do
		*s++ = ABS(n % 10) + '0';
	while (n /= 10);
	if (sign < 0)
		*s++ = '-';
	while (s - p < w)
		*s++ = ' ';
	*s = '\0';
	reverse(p);
}

void printx(char d, int n) {
	if (n < 0)
		putchar('-');
	if (n / 16)
		printx(d, ABS(n / 16));
	if ((n = ABS(n % 16)) > 9)
		putchar(n - 10 + d);
	else
		putchar(n + '0');
}

void reverse(char *s) {
	char temp, *p;

	for (p = s + strlen(s) - 1; p > s; ++s, --p) {
		temp = *s;
		*s = *p;
		*p = temp;
	}	
}

void reverser(char *s) {
	void aux(char *, int, int);

	aux(s, 0, strlen(s)-1);
}

void aux(char *s, int i, int j) {
	char temp;

	if (i >= j)
		return;
	temp = s[i];
	s[i] = s[j];
	s[j] = temp;
	aux(s, ++i, --j);
}
	
void qsort(int *v, int left, int right) {
	int *lastp, *lp, *rp, *p;
	void swap(int *, int, int);

	lp = v + left;
	rp = v + right;
	if (lp >= rp)
		return;
	swap(v, lp - v, lp + (rp - lp)/2 - v);
	lastp = lp;
	for (p = lp + 1; p <= rp; ++p)
		if (*p > *lp)
			swap(v, ++lastp - v, p - v);
	swap(v, lp - v, lastp - v);
	qsort(v, lp - v, lastp - v - 1);
	qsort(v, lastp - v + 1, rp - v);	
}

void swap(int *v, int i, int j) {
	int temp;

	temp = *(v + i);
	*(v+i) = *(v+j);
	*(v+j) = temp;
}

#define MAXFMT 100

/* minimal printf with variable argument list */
void miniprintf(char* fmt, ...) {
	va_list ap;
	char s[MAXFMT], *pf, *p, *sval;
	int ival;
	double dval;
	unsigned uval;

	va_start(ap, fmt); /* let ap points to 1st unnamed argument */
	for (p = fmt; *p; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		s[0] = *p;
		for (pf = s; !isalpha(*++pf = *++p); )
			;
		if (*pf == 'h' || *pf == 'l')
			*++pf = *++p;
		*++pf = '\0';
		switch(*p) {
			case 'd': case 'i':
				ival = va_arg(ap, int);
				printf(s, ival);
				break;
			case 'x': case 'X': 
			case 'o': 
			case 'u':
				uval = va_arg(ap, unsigned);
				printf(s, uval);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf(s, dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				printf(s, sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);	/* do clean up */
}
