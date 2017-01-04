/*******************************************************************
* TITLE: long.c
*
* FUNCTION: printout lines of more than 80 characters 
*
* CHANGE LOG:
* 	2016-3-7 *
*            8-10 modify to printout whole long line 
********************************************************************/

#include <stdio.h>
#include "getlin.h"

#define LONGLIN 80 

main() {
	int c, n;
	char line[LONGLIN+1];

	while (n = getlin(line, LONGLIN))
		if (line[n-1] != '\n') { /* longer than LONGLIN */
			printf("%s", line);
			while ((c = getchar()) != '\n' && c != EOF)
				putchar(c);
			if (c == '\n')
				putchar(c);	
		}
	return 0;
}
