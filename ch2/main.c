#include <stdio.h>

int htoi(char *);
char *squeeze(char *, char *);
char *any(char *, char *);
unsigned rightrot(unsigned, int);
int lower(int);

int main() {
	char s[] = "i have a pencil and a pc\n";
	int i;

	printf("%d\n", htoi("0x10"));
	printf("%d\n", htoi("10"));
	printf("%d\n", htoi("i0"));
	printf("%d\n", htoi("1ac"));
	printf("%s\n", squeeze(s, " "));
	printf("%s\n", any(s, " p"));
	printf("%s\n", any(s, "h,p"));
	
	for (i = 0; i <= 64; i++)
		printf("%ud\n", rightrot(10, i));
	printf("%c\n", lower('a'));
	printf("%c\n", lower('A'));
	printf("%c\n", lower(-1));
	return 0;
}
