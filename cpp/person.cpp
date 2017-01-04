#include <iostream>

using namespace std;

const int maxname = 30;

class person {
	static int count;
	char name[maxname];
	int age;
	float salery;
public:
	static void showcount(void);
	void getperson(void);
	void putperson(void);
	friend float tax(person p);
};	

int person::count;

void person::showcount(void) {
	cout << count << endl;
}

void person::getperson(void) {
	cin >> name >> age >> salery;
	count++;
}

void person::putperson(void) {
	cout << name << " " << age << " " << endl;
	cout << "salery: " << salery << endl;
}

float tax(person p) {
	return p.salery * .1;
}

int main() {
	person p;
	person *pp = &p;
	void (person:: *func)(void) = person::getperson;

	person::showcount();
	p.getperson();
	p.putperson();
	pp->*func;
	p.putperson();
	cout << "your tax: " << tax(p) << endl;
	person:: showcount();

	return 0;
}
