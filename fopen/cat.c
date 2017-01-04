/* log
	2016-9-1	*
	2016-9-3	test fopen */

#include "file.h"

void filecopy(FILE *, FILE*);

/* cat: concatenate files, version 2 */
main(int argc, char *argv[]) {
	FILE *fp;
	char *prog = argv[0];	/* program name for errors */

	if (argc == 1)	/* no args; copy standard input */
		filecopy(stdout, stdin);
	else
		while (--argc)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				return 1;
			} else {
				filecopy(stdout, fp);
				fclose(fp);
			}
	if (ferror(stdout)) {
		return 2;
	}
	fclose(stdout);
	return 0;
}

/* filecopy: copy file src to file dst */
void filecopy(FILE *dst, FILE *src) {
	int c, n;

	while ((c = getc(src)) != EOF)
		putc(c, dst);
}
