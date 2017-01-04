#include <iostream>
using namespace std;

double volume(double s);
double volume(double r, double h);
double volume(double l, double w, double h);

double vol(double l = 1, double w = 1, double h = 1);

double power(double x, int n = 2);
int power(int x, int n = 2);

int main() {
	cout << volume(2) << endl;
	cout << volume(1, 2) << endl;
	cout << volume(2, 2, 3) << endl;
	cout << vol() << endl;
	cout << vol(2) << endl;
	cout << vol(3, 3) << endl;

	cout << power(4) << endl;
	cout << power(1.414) << endl;
	cout << power(2, 5) << endl;
	cout << power(2, 6) << endl;
	cout << power(1., 3) << endl;
	return 0;
}

double power(double x, int n) {
	double res;

	if (n <= 0)
		return 1;
	for (res = 1; n; n >>= 1) {
		if (n & 1 == 1)
			res *= x;
		x *= x;
	}
	return res;
}

int power(int x, int n) {
	int res;

	for (res = 1; n > 0; n >>= 1) {
		if (n & 1 == 1)
			res *= x;
		x *= x;
	}
	return res;
}

double volume(double s) {
	return s * s * s;
}

double volume(double r, double h) {
	return 3.141592654*r*r*h;
}

double volume(double l, double w, double h) {
	return l * w * h;
}

double vol(double l, double w, double h) {
	return l * w * h;
}
