#include "inout.h"

main() {
	int a;

	while (getnum(&a) > 0)
		printf("%d\n", a);
}
