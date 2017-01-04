// test for my_list.h


#include <iostream>
#include <string>
#include "my_list.h"
using namespace std;


int main() {
	my_list<int> num_list;

	//(1)******** empty test:
	cout << "empty list size: " << num_list.size() << endl;	
	cout << "1st item in empty list: " << num_list[0] << endl;


	//(2)******* number test:

	cout << "enter some numbers: " << endl;
	int num = 0;
	while (cin >> num) {
		num_list.add(num);
	}
	cout << endl;
	for (int i = 0; i < num_list.size(); ++i) {
		cout << num_list[i] << endl;
	}

	return 0;
}
