/* cmp.c - compare two files, printing the first line
	where they differ

   log:
	2016-8-30 * */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

main(int argc, char *argv[]) {
	FILE *fp1, *fp2;
	char line1[MAXLINE];
	char line2[MAXLINE];
	char *lp1, *lp2;

	if (argc != 3) {
		fprintf(stderr, "Usage: cmp file1 file2\n");
		exit(1);
	}

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "r");
	if (fp1 == NULL || fp2 == NULL) {
		fprintf(stderr, "diff: can't open file %s %s\n",
			fp1 == NULL ? argv[1] : "",
			fp2 == NULL ? argv[2] : "");
		exit(2);
	}

	lp1 = fgets(line1, MAXLINE, fp1);
	lp2 = fgets(line2, MAXLINE, fp2);
	while (lp1 != NULL || lp2 != NULL) {
		if (lp1 == NULL) {
			printf("%s: %s", argv[2], lp2);
			break;
		} else if (lp2 == NULL) {
			printf("%s: %s", argv[1], lp1);
			break;
		} else if (strcmp(lp1, lp2) != 0) {
			printf("%s: %s", argv[1], lp1);
			printf("%s: %s", argv[2], lp2);
			break;
		}
		lp1 = fgets(line1, MAXLINE, fp1);
		lp2 = fgets(line2, MAXLINE, fp2);
	}
	fclose(fp1);
	fclose(fp2);
	exit(0);
}
