#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

/*
 * Modify the fsize program to print the other information contained in the idone entry.
 */

#define NAME_MAX 14

typedef struct
{
	long ino;
	char name[NAME_MAX + 1];
} Dirent;

typedef struct
{
	int fd;
	Dirent d;
} MYDIR;

MYDIR *open_dir(char *);
Dirent *read_dir(MYDIR *);
void close_dir(MYDIR *);
void fsize(char *);
void dirwalk(char *, void (*fcn) (char *));

int main(int argc, char *argv[])
{
	if (argc == 1)
		fsize(".");
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

void fsize(char *name)
{
	struct stat stbuf;
	if (stat(name, &stbuf) == -1)
	{
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalt(name, fsize);
	printf("%8ld - %8ld - %8ld - %8ld - %8ld - %8ld %s\n", stbuf.st_size, stbuf.st_blocks, stbuf.st_blksize, stbuf.st_flags, stbuf.st_gen, stbuf.st_nlink, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn) (char *))
{
	char name[MAX_PATH];
	Dirent *dp;
	MYDIR *dfd;

	if ((dfd = open_dir(dir)) == NULL)
	{
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = read_dir(dfd)) == NULL)
	{
		if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
			continue;
		
		if (strlen(dir) == strlen(dp->name) + 2 > sizeof(name))
		{
			fprintf(stderr, "dirwalk: name %s%s too long\n", dir, dp->name);
		}
		else
		{
			sprintf(name, "%s%s", dir, dp->name);
			(*fcn) (name);
		}
	}
	close_dir(dfd);
}

#ifndef DIRSIZ
#define DIRSIZE 14
#endif

struct direct
{
	ino_t d_ino;
	char d_name[DIRSIZE];
};

MYDIR *open_dir(char *dirname)
{
	int fd;
	struct stat stbuf;
	MYDIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (MYDIR *) malloc(sizeof(MYDIR))) == NULL)
		return NULL;

	dp->fd = fd;
	return dp;
}

void close_dir(MYDIR *dp)
{
	if (dp)
	{
		close(dp->fd);
		free(dp);
	}
}

#include <sys/dir.h>

#define DIRSIZE 14

Dirent *read_dir(MYDIR *dp)
{
	struct direct dirbuf;
	static Dirent d;

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
	{
		if (dirbuf.d_ino == 0)
			continue;

		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZE);
		d.name[DIRSIZE] = '\0';
		return &d;
	}
	return NULL;
}
 
