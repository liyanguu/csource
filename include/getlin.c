#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "getlin.h"

int getlin(char *s, int lim) {
	int c;
	char *p = s;

	while ((c = getchar()) != '\n' && c != EOF)
		*s++ = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - p;
}

void reverse(char *s) {
	char t, *p;
	
	for (p=s; *p; p++)
		;
	for (p--; s < p; s++, p++)
		t = *s, *s = *p, *p = t;
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
	for (s += strlen(s) - strlen(t); s >= bs; --s)
		if (strindex(s, t) != NULL)
			return s;
	return NULL;
}

double stof(char *s) {
	double val, power, sign;
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
	val *= pow(10, (sign > 0) ? index : -index);
	return val;
}
