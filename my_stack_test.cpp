#include <iostream>
#include <string>
#include "my_stack.h"
using namespace std;

int main() {
	
	// empty test:
/*
	my_stack<string> empty_stack;
	string str = empty_stack.pop();
	cout << str << endl;
*/
	

	// number test:
/*
	cout << "input some numbers:" << endl;
	int num;
	my_stack<int> number_stack;
	while (cin >> num) {
		number_stack.push(num);
	}
	while (!number_stack.empty()) {
		cout << number_stack.pop() << ' '; 
	}
*/
	

	// string test:
	cout << "input some words" << endl;
	string word;
	my_stack<string> word_stack;
	while (cin >> word) {
		word_stack.push(word);
	}
	while (!word_stack.empty()) {
		cout << word_stack.pop() << ' ';
	}	


	return 0;
}
		

