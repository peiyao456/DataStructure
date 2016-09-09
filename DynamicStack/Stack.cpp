#include"Stack.hpp"
#include"TyprTraits.h"

template<typename T>
ostream& operator<<(ostream& os,  Stack<T>& s)
{
	for (int i =s. _size - 1; i >= 0; --i)
	{
		os <<s._data[i] << endl;
	}
	return os;
}

template<typename T>
void Stack<T>::Display()
{
	if (!isEmpty())
	{
		for (int i = _size - 1; i >= 0; --i)
		{
			cout << _data[i] << endl;
		}
	}
}

template<typename T>
void Stack<T>::CheckCapacity(int count)
{
	if (_size + count <= _capacity)
	{
		int NewCapacity = _size + 10;
		T* tmp = new T[NewCapacity];
		copy(tmp,_data,_size);
		delete _data;
		_data = tmp;
		_capacity = NewCapacity;
	}
}

template<typename T>
Stack<T>::Stack()
	:_data(new T[4])
	, _size(0)
	, _capacity(4)
{}

template<typename T>
Stack<T>::~Stack()
{
	if (_data != NULL)
	{
		delete _data;
		_size = 0;
		_capacity = 0;
	}
}

template<typename T>
Stack<T>::Stack(const Stack& s)
{
	_data = new T[s._capacity];
	copy(_data,s._data,s._size);
	_size = s._size;
	_capacity = s_capacity;
}

template<typename T>
void Stack<T>::Push(T x)
{
	CheckCapacity(1);
	_data[_size++] = x;
}

template<typename T>
void Stack<T>::Pop()
{
	assert(_size > 0);
	_size--;
}

template<typename T>
T& Stack<T>::Top()
{
	return _data[_size - 1];
}

template<typename T>
bool Stack<T>::isEmpty()
{
	return _size == 0;
}

template<typename T>
void Stack<T>::copy(T* tmp, T* data, size_t size)
{
	if (TypeTraits<T>::__IsPODType().Get())
	{
		memcpy(tmp,data,sizeof(T)*size);
	}
	else
	{
		for (size_t i = 0; i < size; ++i)
		{
			tmp[i] = data[i];
		}
	}
}

