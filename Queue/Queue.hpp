#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include<iostream>
using namespace std;

template<typename T>
struct QueueNode
{
	QueueNode(T& x)
		:_data(x)
		,_next(NULL)
		,_prev(NULL)
	{}
	T _data;
	QueueNode<T>* _next;
	QueueNode<T>* _prev;
};
template<typename T>
class Queue
{
	template<typename T>
	friend ostream& operator<<(ostream& os,const Queue<T>& q);
public:
	Queue();
	~Queue();
	Queue(const Queue<T>& q);
	void Push( T x);
	void Pop();
	void Display();
	bool isEmpty();
protected:
	QueueNode<T>* _head;
	QueueNode<T>* _tail;
};
#endif//__QUEUE_HPP__