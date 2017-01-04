struct linklist {
	int lnum;
	struct linklist *next;
};

struct linklist *lalloc(void);
void addlink(struct linklist *, int);
void linkprint(struct linklist *);
