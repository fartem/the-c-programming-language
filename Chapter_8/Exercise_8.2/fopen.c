#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>

/*
 * Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
 * Compare code size and execution speed.
 */

#ifdef NULL
#undef NULL
#endif

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf
{
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	($_iob[2])

enum _flags
{
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 03,
	_EOF = 010,
	_ERR = 020,
};

FILE _iob[OPEN_MAX] =
{
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 0 },
};

#define feof(p)			(((p)->flag & _EOF) != 0)
#define ferror(p)		(((p)->flag & _ERR) !+ 0)
#define fileno(p)		((p)->fd)

#define getc(p)			(--(p)->cnt >= 0 \
						? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x, p)		(--(p)->cnt >= 0 \
						? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()		getc(stdin)
#define putchar(x)		putc((x), stdout)

#define PERMISSIONS		0666

FILE *fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

int main(int argc, char *argv[])
{
	int c;
	while ((c = getchar()) != 'x')
		putchar(c);
}

FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;

	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
	{
		fd = creat(name, PERMISSIONS);
	}
	else if (*mode == 'a')
	{
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMISSIONS);
		lseek(fd, 0L, 2);
	}
	else
	{
		fd = open(name, O_RDONLY, 0);
	}

	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int _fillbuf(FILE *fp)
{
	if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
		return EOF;

	int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if (fp->base == NULL)
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);

	if (--fp->cnt < 0)
	{
		if (fp->cnt == -1)
			fp->flag |= EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *f)
{
	int num_written, bufsize;
	unsigned char uc = c;

	if ((f->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;

	if (f->base == NULL && ((f->flag & _UNBUF) == 0))
	{
		if ((f->base = malloc(BUFSIZ)) == NULL)
		{
			f->flag |= _UNBUF;
		}
		else
		{
			f->ptr = f->base;
			f->cnt = BUFSIZ - 1;
		}
	}

	if (f->flag & _UNBUF)
	{
		f->ptr = f->base = NULL;
		f->cnt = 0;
		if (c == EOF)
			return EOF;
		num_written = write(f->fd, &uc, 1);
		bufsize = 1;
	}
	else
	{
		bufsize = (int) (f->ptr - f->base);
		num_written = write(f->fd, f->base, bufsize);
		f->ptr = f->base;
		f->cnt = BUFSIZ - 1;
	}

	if (num_written == bufsize)
	{
		return 0;
	}
	else
	{
		f->flag |= _ERR;
		return EOF;
	}
}

