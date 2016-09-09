#ifndef __STACK_H__
#define __STACK_H__

#include<iostream>
using namespace std;
#include<memory.h>
#include<assert.h>

template<typename T>
class Stack
{
	template<typename T>
	friend ostream& operator<<(ostream& os,const Stack<T>& s);
public:
	Stack();
	~Stack();
	Stack(const Stack& s);
	void Push(T x);
	void Pop();
	T& Top();
	bool isEmpty();
	void Display();
private:
	void CheckCapacity(int count);
	void copy(T* tmp, T* data, size_t size);
public:
	T* _data;
	int _size;
	int _capacity;
};
#endif//__STACK_H__