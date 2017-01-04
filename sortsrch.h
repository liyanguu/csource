typedef int (*)(void *, void *) PFI;

void quicksort(void **, int, int, PFI);
void shellsort(void **, int, PFI);
void swap(void **, int, int);
void **bisearch(void **, int, PFI);
