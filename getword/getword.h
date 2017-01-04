#if !defined(h_getword)
#define h_getword

#define BUFSIZE 100

int getword(char *, int);
int getch(void);
void ungetch(int);
void in_comment(void);

#endif
