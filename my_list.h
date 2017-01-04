// my_list.h
// a dynamic array
// 动态数组
// created in 2015-4-1
// 创建于2015年4月1日

#include <iostream>

using namespace std;

#ifndef  MY_LIST_H
#define  MY_LIST_H

template <class T>
class my_list {
private:
	int length;
	T* header;
public:
	my_list();
	~my_list();
	int size() const { return length; }
	void add(T item);
	T* operator[] (int i) const;	
};

// constructor:

template <class T>
my_list<T>::my_list() {
	cout << "a my_list object is created." << endl;
	length = 0;
	header = NULL;
}

// destructor:

template <class T>
my_list<T>::~my_list() {
	cout << "my_list object destructed !" << endl;
}

// member functions: 

template <class T>
void my_list<T>::add(T item) {
	header = new T;
	*header = item;
	cout << "address " << header << ": " << *header << endl;   
	++length;
}

// operator overloading:

template <class T>
T* my_list<T>::operator[] (int i) const {
	if (i < 0 || i > (length-1)) {
		cerr << "***** WARNING: invalid index: " << i << endl;
		return 0;
	} else
		return header - 8 * i;  
} 


#endif
