#include <iostream>
using namespace std;

void myswap(int &a, int &b);

int main() {
	int n1, n2;

	cin >> n1 >> n2;
	myswap(n1, n2);
	cout << n1 << " " << n2 << endl;
	return 0;
}

void myswap(int &a, int &b) {
	int temp;

	temp = a;
	a = b;
	b = temp;
}
