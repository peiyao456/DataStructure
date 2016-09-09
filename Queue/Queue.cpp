#include"Queue.hpp"

template<typename T>
ostream& operator<<(ostream& os, const Queue<T>& q)
{
	QueueNode<T>* cur = q._head;
	while (cur)
	{
		os << cur->_data << endl;
		cur = cur->_next;
	}
	return os;
}
template<typename T>
Queue<T>::Queue()
	:_head(NULL)
	,_tail(NULL)
{}

template<typename T>
Queue<T>::~Queue()
{
	QueueNode<T>* cur = _head;
	while (cur != NULL)
	{
		QueueNode<T>* del = cur;
		cur = cur->_next;
		delete del;
	}
}

template<typename T>
Queue<T>::Queue(const Queue<T>& q)
{
	QueueNode<T>* cur = q._head;
	while (cur != NULL)
	{
		Push(cur->_data);
		cur = cur->_next;
	}
}

template<typename T>
void Queue<T>::Push(T x)
{
	QueueNode<T>* newNode = new QueueNode<T>(x);
	if (_head == NULL) //当前队列是空
	{
		_head = _tail = newNode;
	}
	else
	{
		_tail->_next = newNode;
		_tail = _tail->_next;
	}
}

template<typename T>
void Queue<T>::Pop()
{
	if (_head == NULL)
	{
		return;
	}
	else if (_head == _tail)//队列中只有一个元素
	{
		delete _head;
		_head = _tail = NULL;
	}
	else
	{
		QueueNode<T>* del = _head;
		_head = _head->_next;
		_head->_prev = NULL;
		delete del;
	}
}

template<typename T>
void Queue<T>::Display()
{
	//if (_head != NULL)
	if (!isEmpty())
	{
		QueueNode<T>* cur = _head;
		while (cur)
		{
			cout << cur->_data << endl;
			cur = cur->_next;
		}
	}
}

template<typename T>
bool Queue<T>::isEmpty()
{
	return _head == NULL;
}