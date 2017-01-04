#include <iostream>

using namespace std;

int main() {
	int m, i;
	int *v;

	cin >> m;
	if (m <= 0)
		return 0;
	v = new int[m];
	if (v == NULL) {
		cout << "not enough memory\n";
		return 0;	
	}
	for (i = 1; i <= m; i++) {
		v[i] = i;
		cout << ' ' << v[i];
	}
	cout << endl;
	return 0;
}
