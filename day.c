/*
file name: day.c - calculate days in a year
change log:
	2015-12-2 create
	12-4 change total[12] --> total[13]
*/

#include <stdio.h>

int leap(int y);

main() {
	int year, mon, day, total[13];
	
	scanf("%d-%d-%d", &year, &mon, &day);
	total[0] = leap(year) ? 366 : 365;
	total[1] = 31;
	total[2] = leap(year) ? 29 : 28;
	total[3] = 31;
	total[4] = 30;
	total[5] = 31;
	total[6] = 30;
	total[7] = 31;
	total[8] = 31;
	total[9] = 30;
	total[10] = 31;
	total[11] = 30;
	total[12] = 31;
	if (mon < 1 || mon > 12)
		return;
	if (day < 1 || day > total[mon])
		return;
	while (--mon >= 1)
		day += total[mon];
	printf("%d\n", day);
}

int leap(int y) {
	if ((y % 4 == 0 && y % 400 != 0) || y % 400 == 0)
		return 1;
	else
		return 0;
}
