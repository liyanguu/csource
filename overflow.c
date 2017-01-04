#include <stdio.h>
#include <limits.h>

main() {
	int i = INT_MAX;
	int j = INT_MIN;

	for ( ; ; )
		printf("%d %d\n", ++i, --j);
}
