#define MAXNAME 1024 

typedef struct {	/* portable directory entry */
	long ino;		/* inode number */
	char name[MAXNAME+1];
} Direntry;

typedef struct {	/* minimal DIRECT: no buffering, etc. */
	int fd;		/* file descriptor for directory */
	Direntry d;	/* the directory entry */
} DIRECT;

DIRECT *opendirect(char *dirname);
Direntry *readdirect(DIRECT *dfd);
void closedirect(DIRECT *dfd);
