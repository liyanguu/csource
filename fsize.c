#include <stdio.h>
#include <string.h>
#include <fcntl.h>	/* flags for read and write */
#include <sys/stat.h>	/* structure returned by stat */
#include <sys/types.h>	/* typedefs */
#include <dirent.h> 
#include <time.h>

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));

/* print file sizes */
main(int argc, char *argv[]) {
	if (argc == 1)
		fsize(".");	/* default: current dir */
	else
		while (--argc > 0)
			fsize(*++argv);
	return 0;
}

/* fsize: print size of file "name" */
void fsize(char *name) {
	struct stat statbuf;
	char flag = '-';

	if (stat(name, &statbuf) == -1) {
		fprintf(stderr, "error: can't access %s\n", name);
		return;
	} else if ((statbuf.st_mode & S_IFMT) == S_IFDIR) {
		printf("in directory\n");
		flag = 'd';
		dirwalk(name, fsize);
	}
	printf("%5d %c%6o %3d %8lu %s %s\n", 
	  (int) statbuf.st_ino, flag, statbuf.st_mode & ~S_IFMT, 
	  (int) statbuf.st_nlink, statbuf.st_size,
	  ctime(&statbuf.st_atime), name);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "error: can't open %s\n", dir);
		return;
	}
	while ((dp = readdir(dfd)) != NULL) {
		printf("reading directory entries\n");
		if (strcmp(dp->d_name, ".") == 0 
		  || strcmp(dp->d_name, "..") == 0)
			continue;	/* skip self and parent */
		if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
			fprintf(stderr, "error: name %s/%s too long\n",
			   dir, dp->d_name);
		else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
