// my_stack.h
// a simple stack template implementation
// 简单模板栈实现
// created in 2015-3-30
// 创建于 2015年3月30日

#include <iostream>
using namespace std;

#ifndef MY_STACK_H
#define MY_STACK_H

template <class T>
class my_stack {
public:
	my_stack();
	T pop();
	void push(const T& new_item);
	bool empty() { return length == 0; }
protected:
	void add_front(const T& new_item);
	struct Node {
		T item;
		Node* next;
	};
private:
	Node* head;
	long length;
};

// constructor
template <class T>
my_stack<T>::my_stack() {
	head = NULL;
	length = 0;
}

// protected member function:
template <class T>
void my_stack<T>::add_front(const T& new_item) {
	Node* new_hd = new Node;
	new_hd -> item = new_item;
	new_hd -> next = head;
	head = new_hd;
}

// public member functions:
template <class T>
T my_stack<T>::pop() {
	if (length == 0) {
		cerr << "*** the stack is empty !" << endl;
		return 0;
	}
	else {
		Node* old_hd = head;
		head = head -> next;
		T my_item = old_hd -> item;
		delete old_hd;
		--length;
		return my_item;
	}
}
template <class T>
void my_stack<T>::push(const T& new_item) {
	add_front(new_item);
	++length;
}


#endif	
