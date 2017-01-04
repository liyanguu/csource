#include <stdio.h>

main() {
	/* signed types */
	printf("signed char min = %d\n",
		 - (signed char) ((unsigned char) ~0 >> 1) - 1);
	printf("signed char max = %d\n", 
		(signed char) ((unsigned char) ~0 >> 1));
	printf("signed short min = %hd\n", 
		- (short) ((unsigned short) ~0 >> 1) - 1);
	printf("signed short max = %hd\n", 
		(short) ((unsigned short) ~0 >> 1));
	printf("signed int min = %d\n", - (int) (~0u >> 1) - 1);
	printf("signed int max = %d\n", (int) (~0u >> 1));
	printf("signed long min = %ld\n", - (long) (~0ul >> 1) - 1);
	printf("signed long max = %ld\n", (long) (~0ul >> 1));

	/* unsigned types */
	printf("unsigned char max = %u\n", (unsigned char) ~0);
	printf("unsigned short max = %hu\n", (unsigned short) ~0);
	printf("unsigned int max = %u\n", (unsigned int) ~0);
	printf("unsigned long max = %lu\n", (unsigned long) ~0);
	return 0;
}
