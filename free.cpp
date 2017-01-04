// free.cpp - test the size of free memory storage


#include <iostream>
#include <new>

using namespace std;

int main() {
	long int count = 0;
	try {
		do {
			char* c_ptr = new char[1024];
			++count;
		} while (true);
	}

	catch (bad_alloc b) {
		cout << "the size of free memory storage(MB) is: ";
		cout << count/1024 << endl;
	}
	return 0;
}
