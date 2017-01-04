/* filename: convert.c - print celsius-fahrenheit table 
   2015-10-15 create 
   2016-3-3   change style of table head */

#include <stdio.h>

#define LOWER 0
#define UPPER 100.0
#define STEP .55 
#define F_C 0
#define C_F 1

/* return convertion between clesius and fahrenheit, according to type */
float convert(float n, int type);

main() {
	float cels;

	printf("celsius  fahrenheit\n");
	printf("-------------------\n");
	for (cels = LOWER; cels <= UPPER; cels += STEP)
		printf("%7.3f %7.3f\n", cels, convert(cels, C_F));
}

float convert(float n, int type) {
	switch (type) {
	case C_F: 
		return 9.0 / 5.0 * n + 32.0;
	case F_C:
		return (5.0 / 9.0) * (n - 32.0);
	default:
		printf("wrong type\n");
		return 0;
	}
}
