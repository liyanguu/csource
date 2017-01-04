#include <stdio.h>

int brace, brack, paren, row, rbrace, rbrack, rparen;

void search(int);
void in_comment(void);
void in_quote(int);

main() {
	int c;

	brace = brack = paren = 0;
	row = 1;
	while ((c = getchar()) != EOF) {
		if (c == '/') {
			if ((c = getchar()) == '*')
				in_comment();
			else
				search(c);
		} else if (c == '\'' || c == '"')
			in_quote(c);
		else
			search(c);

		if (brace != 0) {
			rbrace = row;
			if (brace < 0) {
				printf("%d unblanced braces\n", rbrace);
				brace = 0;
			}
		} else if (brack != 0) {
			rbrack = row;
			if (brack < 0) {
				printf("%d unblanced brackets\n", rbrack);
				brack = 0;
			}
		} else if (paren != 0) {
			rparen = row;
			if (paren < 0) {
				printf("%d unblanced parentheses\n", rparen);
				paren = 0;
			}
		}
	}
	
	if (brace > 0)
		printf("%d unblanced braces\n", rbrace);
	if (brack > 0)
		printf("%d unblanced brackets\n", rbrack);
	if (paren > 0)
		printf("%d unblanced parentheses\n", rparen);
}

void search(int c) {
	switch(c) {
	case '{':
		++brace;
		break;
	case '}':
		--brace;
		break;
	case '[':
		++brack;
		break;
	case ']':
		--brack;
		break;	
	case '(':
		++paren;
		break;
	case ')':
		--paren;
		break;
	case '\n':
		++row;
		break;
	default:
		break;
	}
}

void in_comment(void) {
	int c, d;

	c = getchar();
	d = getchar();
	while (c != '*' || d != '/') {
		if (c == '\n')
			++row;
		c = d;
		d = getchar();
	}
}

void in_quote(int c) {
	int d;

	while ((d = getchar()) != c)
		if (d == '\\')
			getchar();
		else if (d == '\n')
			++row;
}
