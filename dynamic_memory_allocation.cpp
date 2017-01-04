//***********************************************************
// TITLE: dynamic_memory_allocation -- C++ addressing mode test 
//
// AUTHOR: liyang
// 
// CHANGE LOG: 
//	2015-4-7: version 3
//*********************************************************** 

#include<iostream>

using namespace std;

void fun(); // prototype & definition
void fun() {}
void fun2();
void fun2() {}

int main(int argc, char* argv[]) {

	const int SIZE =  10;

// address of variable:

	cout << "address of int constant: " << &SIZE << endl;
	int num1, num2; // reserve a double word (64 bits) 
	cout << "address of int variables: " << endl << &num1 << endl << &num2 << endl;
	long* l1, l2; // reserve a quardword (128 bits) 
	cout << "address of long pointer variables: " << endl << &l1 << endl << &l2 << endl;
	int num3; // reserve a word (32 bits)
	cout << "address of another int varible: " << endl << &num3 << endl;

// address of functions: 

	cout << "address of function main: " << &argv[0] << endl; 
	fun(); // first call
	cout << "address of function fun (1st call): " << &fun << endl;
	fun(); // second call
	cout << "address of function fun (2nd call): " << &fun << endl;
	void (*fun2_p) (void) = &fun2;
	cout << "address of function fun2: " << fun2_p << endl;

// declaring a pointer-to-int array

	int* array[SIZE];

	cout << "addresses of a pointer-to-int array: " << endl;	
	for (int i = 0; i < SIZE; ++i) {
		cout << "index " << i << " address: " << &array[i] << endl;
	}


// allocating a pointer-to-int array

	int** int_array = new int* [SIZE];
	cout << "allocating a pointer-to-int array:" << endl;
	for (int i = 0; i < SIZE; ++i) {
		cout << "index " << i << " address: " << &int_array[i] << endl;
	}

// allocation once at a time

	int* int_ptr2 = new int; 
	cout << "alloction once at a time:" << endl; 
	for (int i = 1; i <= SIZE; ++i) {
		int_ptr2 = new int; 
		cout << "number " << i << " address: " << int_ptr2 << endl; 
	}	

	return 0;
}
