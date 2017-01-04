void miniprintf(char* fmt, ...) {
	va_list ap;
	char *p, *sval, s[SLEN];
	int ival;

	va_start(ap, fmt);	/* let ap points to final named argument fmt */
	for (p = fmt; *p; ++p) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch(*++p) {
			case '\0':
				return;
			case 'x': case 'd': case 'o': case 'b':
				ival = va_arg(ap, int);
				itos(ival, *p, s);
				miniprintf("%s", s);
				break;
			case 'c':
				ival = va_arg(ap, int);
				putchar(ival);	
				break;
			case 's':
				for (sval = va_arg(ap, char*); *sval; ++sval)
					putchar(*sval);
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);	/* do clean up */
}
