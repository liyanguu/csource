#include <iostream>

using namespace std;

#define C_F 0
#define F_C 1

class temp {
	float t;
	
	public:

	void gett(void);
	void printt(void);
	void convert(int flag);
};

void temp::gett(void) {
	cin >> t;
}

void temp::printt(void) {
	cout << t;
}

void temp::convert(int type) {
	switch (type) {
	case C_F: 
		t = 9.0 / 5.0 * t + 32.0;
		break;
	case F_C:
		t =  (5.0 / 9.0) * (t - 32.0);
		break;
	default:
		cout << "wrong type\n";
		break;
	}
}

int main() {
	temp fahr;

	for ( ; ; ) {
		fahr.gett();
		fahr.convert(F_C);
		fahr.printt();
	}
	return 0;
}
