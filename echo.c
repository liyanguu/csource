#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
char line[MAXLINE];

void unescape(char *, char*);

int main(int argc, char **argv) {
	int newline, escseq;

	newline = escseq = 0;
	if (--argc > 0) {
		if ((*++argv)[0] == '-' && (strlen(*argv) == 2))
			switch((*argv)[1]) {
			case 'n':
				newline = 1;
				break;
			case 'e':
				escseq = 1;
				break;
			default:
				++argc;
				--argv;
			}
		else {
			++argc;
			--argv;
		}
	}
	while (--argc > 0) {
		++argv;
		if (escseq) {
			unescape(line, *argv);
			printf("%s", line);
		} else
			printf("%s", *argv);
		printf("%s", (argc > 1) ? " " : "");
	}
	if (!newline)
		printf("\n");
	return 0;
}
