#include <iostream>

using namespace std;

class Comp {
	double re, im;
public:
	void makecomp(double x, double y);
	void print(void);
	friend Comp addcomp(Comp a, Comp b);
};

void Comp::makecomp(double x, double y) {
	re = x;
	im = y;
}

void Comp::print(void) {
	cout << "(" << re << ", " << im << ")" << endl;
}

Comp addcomp(Comp a, Comp b) {
	a.re += b.re;
	a.im += b.im;
	return a;
}

int main() {
	Comp a, b, c;

	a.makecomp(1., 2.);
	b.makecomp(3., 4.);
	c = addcomp(a, b);
	c.print();
	return 0;
}
