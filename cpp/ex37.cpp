#include <iostream>
#include <cmath>

using namespace std;

double fact(double n);
double sinrad(double r);

int main() {
	cout << fact(5) << endl;
	cout << sinrad(3.1415) << endl;
	cout << sinrad(3.1415 / 2) << endl;
	cout << sinrad(0) << endl;
	return 0;
}

double fact(double n) {
	double res;
	
	if ((res = n) <= 0)
		return 1;
	for ( ; --n > 0; res *= n)
		;
	return res;
}

double sinrad(double x) {
	int i; 
	double sign, res;

	sign = -1;
	res = x;
	for (i = 3; i <= 51; i += 2) {
		res += sign * pow(x, i) / fact(i);
		sign *= -1;
	}
	return res;
}
