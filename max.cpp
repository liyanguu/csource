#include <iostream>

using namespace std;

int ascii_to_num(char* ptr);
template<typename T>
void to_swap(T &op1,T &op2);
	
int main(int argc, char* argv[]) {
	int max = ascii_to_num(argv[1]); 
	for(int i = 2; i < argc; ++i) {
		int num = ascii_to_num(argv[i]);
		if (num >= max) to_swap(max, num);
	}	
	cout << max << endl;
}


int ascii_to_num(char* ptr) {  
	int inc = 0; // address increase   
	int j = 1;  // magnitude of digit
	int num = 0;
	while (*ptr) {
		++ptr;
		++inc;
	}
	for (int i = inc; i > 0; --i) {
		--ptr;
		num += (*ptr - '0') * j;
		j *= 10;
	}
	return num;	
} 

template<typename T>
void to_swap(T &op1,T &op2) {
	T temp = op1;
	op1 = op2;
	op2 = temp;
}
