#include <stdio.h>

int main() {
	int c;
	int decomment(int);
	void echo_quote(int);

	while ((c=getchar()) != EOF) {
		while ((c = decomment(c)) == '/')
			;
		if (c == '\'' || c == '"')
			echo_quote(c);
		else
			putchar(c);
	}
}

int decomment(int c) {
	int d;

	if (c != '/')
		return c;
	if ((c = getchar()) == '*') {
		for (c = getchar(), d = getchar(); c != '*' || d != '/';
			c = d, d = getchar())
			;
		return getchar();
	} else {
		putchar('/');
		return c; 
	}
}

void echo_quote(int c) {
	int d;

	putchar(c);
	while ((d = getchar()) != EOF) {
		putchar(d);
		if (d == c)
			break;
	}
}
