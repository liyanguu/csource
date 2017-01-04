#include <iostream>
using namespace std;

int *getmatrix(int n, int m = 3);
void display(int *a, int n, int m = 3);

int main() {
	const int n = 3;
	int *m, *a;

	m = getmatrix(n);
	display(m, n);
	a = getmatrix(n, 4);
	display(a, n, 4);
	return 0;
}

int *getmatrix(int n, int m) {
	int i, j;
	int *a, *b;

	b = a = new int[m*n];	
	for (i= 0; i < m; i++)
		for (j = 0; j < n; j++)
			cin >> *a++;
	return b;
}

void display(int *a, int n, int m) {
	int i, j;

	for (i=0; i < m; i++) {
		for (j = 0; j < n ; j++)
			cout << ' ' << a[i * n + j];
		cout << endl;
	}
}
