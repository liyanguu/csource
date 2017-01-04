/* file name: str.h
change log: 2015-10-13 create
		10-22 add catstr
		11-26 split strings.h from strings.c */ 

#if !defined(H_STR)
#define H_STR

#define swapt(t, a, b) { t Temp; Temp = a, a = b, b = Temp; }
#define isupperc(c) (c >= 'A' && c <= 'Z')
#define tolowerc(c) (isupperc(c) ? c + 'a' - 'A' : c)


int strlength(char *);
int strend(char *, char *patt);
char *strindex(char *, char *patt);
char *strrindex(char *, char *patt);
char* strcat2(char *, char *);
int str2num(char *);
double str2flt(char *);
char *num2str(int, char *, int);
char *pendstr(char *, char *);
char *pendnstr(char *, char *, int);
char *revstr(char *);
char *copystr(char *, const char *);
char *copynstr(char *, const char *, int);
int cmpstr(char *, char *);
int cmpnstr(char *, char *, int);
char *rmhead(char *);
int trim(char *);
unsigned setbits(unsigned, int, int, unsigned);
int bitcnt(unsigned);
unsigned invert(unsigned, int, int);
int aisupper(int);
int atolower(int);

#endif
