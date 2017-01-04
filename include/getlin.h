#ifndef H_GETLIN
#define H_GETLIN

#define ABS(x) ((x) >= 0 ? (x) : -(x))

int getlin(char *line, int limit);
void reverse(char *s);
int htoi(char *s);
char *any(char *s1, char *s2);
char *squeeze(char *s1, char *s2);
int btoi(char *s, int base);
void unescape(char *s, char *t);
void escape(char *s, char *t);
void expand(char *src, char *dst);
void itos(int n, char *, int width);
void itob(int n, char *, int base);
char *strindex(char *s, char *pat);
char *strrindex(char *s, char *pat);
double stof(char *s);

#endif
