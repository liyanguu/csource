#define NALLOC	1024	/* minimum #units to request */

typedef long Align;	/* for alignment to long boundary */

union header {
	struct {
		union header *ptr;	/* next block if no free space */
		unsigned size;		/* size of this block */
	} s;
	Align x;			/* force alignment of blocks */
};

typedef union header Header;

