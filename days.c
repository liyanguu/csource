/* days.c - calculate days between two dates */
/* 2015-4-30 */

#include <stdio.h>
#include <ctype.h>
#include "getlin.h"

int isleap(int y);
int days_of_year(int y, int m, int d);
void month_day(int y, int yd, int *pm, int *pd);
int days(int y2, int m2, int d2, int y1, int m1, int d1);
void obtain_date(int *y, int *m, int *d, char *str);
int days2(char *date2, char *date1);

main(int argc, char *argv[]) {
	int month, day;

	if (argc == 4)
		printf("%d\n", days_of_year(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])));
	else if (argc == 3) {
		month_day(atoi(argv[1]), atoi(argv[2]), &month, &day);
		printf("%d %d\n", month, day);
	} else
		printf("usage: %s year (month day | yearday)\n", *argv); 
}

int isleap (int y) {
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

static char daytab[2][13] = { 
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int days_of_year(int y, int m, int d) {
	char leap, *p;

	if (y < 0 || m < 1 || m > 12)
		return 0;
	leap = isleap(y);
	p = daytab[leap];
	if (d < 1 || d > p[m])
		return 0;
	while (--m)
		d += *++p;
	return d;
}

void month_day(int y, int yd, int *pm, int *pd) {
	char *p, leap;

	if (y < 0) {
		*pm = *pd = 0;
		return;
	}
	leap = isleap(y);
	for (p = daytab[leap]; ++p <= daytab[leap]+12 && yd > *p; ) 
		yd -= *p;
	if (yd < 1 || p > daytab[leap]+12) {
		*pm = *pd = 0;
		return;
	}
	*pm = p - daytab[leap];
	*pd = yd;
}

/* y2-m2-d2 after y1-m1-d1 */
int days(int y2, int m2, int d2, int y1, int m1, int d1) {
	int i, duration;

	if (days_of_year(y1, m1, d1) + days_of_year(y2, m2, d2) == 0)
		return -1;
	duration = 0;
	for (i = y2; i > y1; --i)
		duration += isleap(i) ? 366 : 365;
	return duration - days_of_year(y1, m1, d1) + days_of_year(y2, m2, d2);
}

void obtain_date(int *y, int *m, int *d, char *str) {
	/* obtain year */
	for ( ; *str != '-'; ++str) {
		if (!isdigit(*str)) {
			printf("year is not a number, using 1999 instead!\n");
			*y = 1999;
			break;
		}
		*y = *y * 10 + *str - '0';
	}

	/* obtain month */
	for (++str; *str != '-'; ++str) {
		if (!isdigit(*str)) {
			printf("month is not a number, using 1 instead!\n");
			*m = 1;
			break;
		}
		*m = *m * 10 + *str - '0';
	}

	/* obtain day */
	for (++str; *str != '\0'; ++str) { 
		if (!isdigit(*str)) {
			printf("day is not a number, using 1 instead!\n");
			*d = 1;
			return;
		}
		*d = *d * 10 + *str - '0';
	}
}

int days2(char * date2, char * date1) {
	int y2, m2, d2, y1, m1, d1;
	y2 = m2 = d2 = y1 = m1 = d1 = 0; 

	obtain_date(&y2, &m2, &d2, date2);
	obtain_date(&y1, &m1, &d1, date1);

	return days(y2, m2, d2, y1, m1, d1);
}
