#include <stdio.h> 
#include <string.h>
#include "../str.h"
#include "dcl.h"

void wtod(void);
void dtow(void);

main(int argc, char *argv[]) { 
	if (strend(argv[0], "/dcl")) {
		printf("dcl\n");
		dtow();
	} else {
		printf("undcl\n");
		wtod();
	}
	return 0;
}

/* convert dcl to word description */
void dtow(void) {
	while (gettoken() != EOF) {         /* 1st token on line */
		if (!typespec())
			continue;
		printf("start parsing...\n");
		strcpy(datatype, token);    /* is the datatype */
		out[0] = '\0';
		dcl();
		if (tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
	}
}

/* undcl: convert word description to dcl */
void wtod(void) {
	int type;	
	char temp[MAXTOKEN];

	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n')
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*') {
				if ((type = nexttoken()) == PARENS || type == BRACKETS) 
					sprintf(temp, "(*%s)", out);
				else
					sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		printf("%s\n", out);
	}
}
