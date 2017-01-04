#include <stdio.h>
#include <limits.h>
#include <float.h>

main() {
	printf("char: %d - %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("short: %d - %d\n", SHRT_MIN, SHRT_MAX);
	printf("int:  %d - %d\n", INT_MIN, INT_MAX);
	printf("long: %ld - %ld\n", LONG_MIN, LONG_MAX);
	printf("unsigned char: 0 - %d\n", UCHAR_MAX);
	printf("unsigned short: 0 - %d\n", USHRT_MAX);
	printf("unsigned int: 0 - %u\n", UINT_MAX);
	printf("unsigned long: 0 - %lu\n", ULONG_MAX);
	printf("%15s: %d\n", "float radix", FLT_RADIX);
	printf("%15s: %e - %e\n", "float", FLT_MIN, FLT_MAX);
	printf("%15s: %g - %g\n", "double", DBL_MIN, DBL_MAX);
	printf("%15s: %f\n", "float epsilon", FLT_EPSILON);
	printf("%15s: %f\n", "double epsilon", DBL_EPSILON);
	return 0;
} 
