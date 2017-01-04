#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dcl.h"

char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */

/* dcl: parse a declarator */
void dcl(void) {
	int ns;

	for (ns = 0; gettoken() == '*'; ++ns)   /* count *'s */
		;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
	int type;

	if (tokentype == '(') {           /* ( dcl ) */
		dcl();
		if (tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME) {     /* variable name */
		strcpy(name, token);
	} else
		printf("dirdcl: expecting name or (dcl)\n");
	while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function expecting");
			parmdcl();
			strcat(out, " and returning");
		} else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

/* parmdcl: parse a parameter declarator */
void parmdcl(void) {
	do
		dclspec();
	while (tokentype == ',');
	if (tokentype != ')')
		printf("parmdcl: missing ) in parameter declaration\n");
}

void dclspec(void) {
	char temp[MAXTOKEN];

	temp[0] = '\0';
	gettoken();
	do {
		if (tokentype != NAME) {
			prevtoken = YES;
			dcl();
		} else if (typespec() == YES) {
			strcat(temp, " ");
			strcat(temp, token);
			gettoken();
		} else if (typequal() == YES) {
			strcat(temp, " ");
			strcat(temp, token);
			gettoken();
		} else
			errmsg("unknown type in parameter list\n");
	} while (tokentype != ',' && tokentype != ')');
	strcat(out, temp);
	if (tokentype == ',')
		strcat(out, ",");
}

/* typespec: return YES if token is a type-specifier */
int typespec(void) {
	static char *types[] = {
		"char",
		"double",
		"float",
		"int",
	};
	int i;
	
	for (i = 0; i < sizeof(types)/sizeof(char *); ++i)
		if (strcmp(token, types[i]) == 0)
			return YES;
	return NO;
}

/* typequal: return YES if token is a type-qualifier */
int typequal(void) {
	static char *typeq[] = {
		"const",
		"volatile"
	};
	int i;
	
	for (i = 0; i < sizeof(typeq)/sizeof(char *); ++i)
		if (strcmp(token, typeq[i]) == 0)
			return YES;
	return NO;
}
