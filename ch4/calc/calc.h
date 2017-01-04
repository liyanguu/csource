#define NUMBER '0' 
#define NAME 'n'
#define VAR 'A'

void mathfnc(char *);

int getop(char *);

void push(double);
double pop(void);
double top(void);
void swap(void);
void dup(void);
void clear(void);

int getch(void);
void ungetch(int);
