/* log:
	2016-9-5	field version
	     9-5 19:00	modify to bit-op version */

#define NULL		0
#define EOF		(-1)
#define BUFSIZE		1024
#define OPEN_MAX	20	/* max #files open at once */

typedef struct _iobuf {
	int cnt;	/* characters left */
	char *ptr;	/* next character position */
	char *base;	/* location of buffer */
	int flag;	/* mode of file access */
	int fd;		/* file descriptor */
} FILE;
extern FILE _iob[];

enum _flags {
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020
};

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->flag & _EOF) != 0)
#define ferror(p)	(((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)

#define getc(p)		(--(p)->cnt >= 0 \
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p)	(--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)

FILE *fopen(char *, char *);
int fflush(FILE *);
int fclose(FILE *);
int fseek(FILE *, long offset, int origin);
