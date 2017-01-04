/*
filename: c2f.c - convert celsius to fahrenheit degrees
log: 
	2015-10-15 *
	2016-01-12 change name from cels_fahr.c to simpler c2f.c.
	  rewrite using symbolic constants, and using a macro
	  to do the conversion. 
*/

#include <stdio.h>

#define LOW -20
#define HIGH 100
#define STEP 7 

#define cels2fahr(t) ((9.0 / 5.0) * (t) + 32.0)

main() {
	int cels;

	printf("%10s %10s\n", "celsius", "fahrenheit");
	for (cels = LOW; cels <= HIGH; cels += STEP)
		printf("%10d %10.1f\n", cels, cels2fahr(cels));
}
