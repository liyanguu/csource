#include <iostream>

using namespace std;

class Time {
	int hours;
	int minutes;
public:
	void maketime(int h, int m);
	void showtime(void);
	void addtime(Time t1, Time t2);
};

void inline Time::maketime(int h, int m) {
	hours = h;
	minutes = m;
}

void inline Time::showtime(void) {
	cout << hours << ":" << minutes << endl;
}

void Time::addtime(Time t1, Time t2) {
	minutes = t1.minutes + t2.minutes;
	hours = minutes / 60;
	minutes %= 60;
	hours += t1.hours + t2.hours;
}

int main() {
	Time ta, tb, tc;

	ta.maketime(2, 45);
	tb.maketime(3, 16);
	tc.addtime(ta, tb);
	ta.showtime();
	tb.showtime();
	tc.showtime();
	return 0;
}
