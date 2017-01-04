#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

extern int tokentype;              /* type of last token */
extern char token[MAXTOKEN];       /* last token string */
extern char name[MAXTOKEN];        /* identifier name */
extern char datatype[MAXTOKEN];    /* data type = char, int, etc. */
extern char out[1000];             /* output string */
extern int prevtoken;

void dcl(void);
void dirdcl(void);
void parmdcl(void);
void dclspec(void);
int typespec(void);
int typequal(void);

void errmsg(char *);
int gettoken(void);
int nexttoken(void);

int getch(void);
void ungetch(int);
