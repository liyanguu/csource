#include <stdio.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "direntry.h"

/* opendirect: open a directory for readdir calls */
DIRECT *opendirect(char *dirname) {
	int fd;
	struct stat statbuf;
	DIRECT *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
	  || fstat(fd, &statbuf) == -1
	  || (statbuf.st_mode & S_IFMT) != S_IFDIR
	  || (dp = (DIRECT *) malloc(sizeof(DIRECT))) == NULL )
		return NULL;
	printf("dir open\n");
	dp->fd = fd;
	return dp;
}

void closedirect(DIRECT *dp) {
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

/* readdirect: read directory entries in sequence */
Direntry *readdirect(DIRECT *dp) {
	struct direct dirbuf; 	/* local directory structure */
	static Direntry d;
 
	while (read(dp->fd, (char *) &dirbuf, sizeof dirbuf)
				== sizeof dirbuf) {
		if (dirbuf.d_ino == 0) {	/* slot not in use */
			printf("slot in use\n");
			continue;
		}
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, sizeof(dirbuf.d_name));
		d.name[sizeof(dirbuf.d_name)] = '\0';
		return &d;	/* return: portable structure */ 
	}
	return NULL;
}
