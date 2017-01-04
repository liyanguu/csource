#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#include "getch.h"

int miniscanf(char *, ...);

main() {
	int c, n, day, year, month;
	char monthname[20];

	while ((n=miniscanf("%d/%d/%d", &day, &month, &year)) != EOF)
		if (n == 3)
			printf("%d %d %d\n", day, month, year);
		else {
			printf("invalid\n");
			while ((c = getch()) != '\n')
				putchar(c);
		}
	return 0;
}

int miniscanf(char *fmt, ...) {
	va_list ap;
	int c, *pival, n = 0;
	double *pdval;
	char *p, *psval;

	va_start(ap, fmt);
	for (p = fmt; *p; ++p) {
		for ( ; *p != '%' && *p; ++p) {
			if (isspace(*p))
				continue;
			while (isspace(c = getch()))
				;
			if (*p != c) {
				if (c == EOF)
					return c;
				ungetch(c);
				return n;
			}
		}
		if (*p == '\0')
			return n;
		switch(*++p) {
		case 'd':
			pival = va_arg(ap, int *);
			if ((c = scanf("%d", pival)) == 1)
				++n;
			else if (c == EOF)
				return c;
			else
				return n;
			break;
		case 'c':
			psval = va_arg(ap, char *);
			if ((c = getch()) == EOF)
				return c;
			*psval = c;
			++n;
			break;
		case 's':
			psval = va_arg(ap, char *);
			while (isspace(*psval = c = getch()))
				;
			while (!isspace(*++psval = c = getch()) && c != EOF)
				;
			*psval = '\0';
			if (c == EOF)
				return c;
			ungetch(c);
			++n;
			break;
		default:
			while (isspace(c = getch()))
				;
			if (*p != c) {
				if (c == EOF)
					return c;
				ungetch(c);
				return n;
			}
			break;
		}
	}
	va_end(ap);
	return n;
}
