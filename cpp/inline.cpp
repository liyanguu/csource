#include <iostream>
using namespace std;

inline float pow(float base, float p) {
	float sign, res;

	if ((sign = p) < 0)
		p = -p;
	else if (sign == 0)
		return 1;
	for (res = base; --p > 0; res *= base)
		;
	return (sign < 0) ? 1/res : res;
}

inline float max3(float a, float b, float c) {
	float t;

	t = (a > b) ? a : b;
	return (t > c) ? t : c;
}

int main() {
	cout << pow(2, 3) << ' ' 
		<< pow(2, -3) << ' '
		<< pow(2, 0) << ' '
		<< pow(-2, 3) << endl;

	cout << max3(3, 4, 1) << ' '
		<< max3(1, 2, 3) << ' '
		<< max3(5, 2, 1) << endl;
	return 0;
}
