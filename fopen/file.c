#include <fcntl.h>
#include "file.h"
#include "memalloc.h"
#define PERM 0666

/* fopen: open file, return fileptr */
/* mode = "r", "w", "a" */
FILE *fopen(char *name, char *mode) {
	int c = *mode;
	int fd;
	FILE *fp;

	if (c != 'r' && c != 'w' && c != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; ++fp)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;	/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slot */
		return NULL;
	
	if (c == 'w')
		fd = creat(name, PERM);
	else if (c == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERM);	
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (c == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
	int bufsize;

	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = ((fp->flag & _UNBUF) != 0) ? 1 : BUFSIZE;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) memalloc(bufsize)) == NULL)
			return EOF;	/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* allocate and flush the buffer to fp */
int _flushbuf(int c, FILE *fp) {
	int bufsize;

	if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
		return EOF;
	bufsize = ((fp->flag & _UNBUF) != 0) ? 1 : BUFSIZE;
	if (fp->base != NULL) {
		if (write(fp->fd, fp->base, bufsize) != bufsize) {
			fp->flag |= _ERR;
			return EOF;
		}
	} else if ((fp->base = memalloc(bufsize)) == NULL)
		return EOF;
	fp->ptr = fp->base;
	fp->cnt = bufsize - 1;
	return *fp->ptr++ = c;
}

/* flush the buffer associated with fp */
int fflush(FILE *fp) {
	int nfill;

	if (fp == NULL) {
		for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
			if (fflush(fp) == EOF)
				return EOF;
		return 0;
	} else if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
		return EOF;	/* not open for write */
	nfill = fp->ptr - fp->base;
	if (write(fp->fd, fp->base, nfill) != nfill) {
		fp->flag |= _ERR;
		return EOF;
	}
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZE;
	fp->ptr = fp->base;
	return 0;
}

int fclose(FILE *fp) {
	if ((fp->flag & _WRITE) != 0)
		if (fflush(fp) == EOF)
			return EOF;
	memfree(fp->base);
	fp->base = NULL;
	fp->cnt = 0;
	fp->flag &= ~(_READ | _WRITE);
	close(fp->fd);
	return 0;
}

int fseek(FILE *fp, long offset, int origin) {
	if (fp->flag & _READ) {
		if (origin == 1)	/* adjust current position */
			offset -= fp->cnt;
		fp->cnt = 0;	/* discard buffer */
	} else if (fp->flag & _WRITE)
		if (fflush(fp) == EOF)
			return EOF;
	return lseek(fp->fd, offset, origin) >= 0L ? 0 : EOF;
}

FILE _iob[OPEN_MAX] = {	/* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, _READ, 		0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 		1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 	2 }
};
