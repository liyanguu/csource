/* file name: sio.h

change log:
	2015-11-26 split from getnum.c 
*/

#if !defined(H_SIO)
#define H_SIO

#include <stdio.h>	/* for FILE */

#define getnum(pn) fgetnum(pn, stdin)

int getint(int *);
int getfloat(double *);
int fgetnum(int *pn, FILE *fp);
int getlin(char *, int);
int getl(char *, int);
int getch(void);
void ungetch(int);

#endif
