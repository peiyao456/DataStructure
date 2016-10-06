//保证push pop min的时间复杂度都是O（1）
//单栈
#include<iostream>
using namespace std;
#include<stack>
template<typename T>
class Array
{
public:
	Array(T arr[], int size)
		:_arr(arr)
		, _size(size)
	{

	}
	T Min()
	{
		int i = 0;
		stack<int> s;
		s.push(_arr[0]);
		s.push(_arr[0]);
		for (i = 1; i < _size; ++i)
		{
			if ((s.empty()) || (s.top() > _arr[i]))
			{
				s.push(_arr[i]);
				s.push(_arr[i]);
			}
			else
			{
				int min = s.top();
				s.pop();
				s.push(_arr[i]);
				s.push(min);
			}
		}
		return s.top();
	}
	T& Top()
	{
		return _arr[_size - 1];
	}

private:
	T* _arr;
	int _size;
};
void test()
{
	int arr[7] = { 2,3,1,4,5,0,3 };
	Array<int> Arr(arr, 7);

	cout << Arr.Min() << endl;
}
int main()
{
	test();
	return 0;
}
//借助辅助栈
#include<iostream>
using namespace std;
template<typename T>
class Stack
{
public:
	Stack()
		:_data(NULL)
		,_min(NULL)
		,_size(0)
		,_capacity(0)
	{}
	~Stack()
	{
		delete[] _data;
		delete[] _min;
		_data = NULL;
		_min = NULL;
		_size = 0;
		_capacity = 0;
	}
	void Push(const T& x)
	{
		CheckCapacity();
		_data[_size] = x;
		
		if (x < _min[_size - 1] || _size == 0)
		{
			_min[_size] = x;
		}
		else
		{
			_min[_size] = _min[_size - 1];
		}
		++_size;
	}
	void Pop()
	{
		if (_size > 0)
		{
			--_size;
		}
	}
	size_t Min()
	{
		return _min[_size - 1];
	}
protected:
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			size_t NewCapacity = 2 * _capacity + 5;
			T* tmp1 = new T[NewCapacity];
			T* tmp2 = new T[NewCapacity];
			//拷贝内容
			for (size_t i = 0; i < _size; ++i)
			{
				tmp1[i] = _data[i];
			}
			delete[] _data;
			_data = tmp1;
			for (size_t i = 0; i < _size; ++i)
			{
				tmp2[i] = _min[i];
			}
			delete[] _min;
			_min = tmp2;

			_capacity = NewCapacity;
		}
	}
private:
	T* _data;
	T* _min;
	size_t _size;
	size_t _capacity;
};
void test()
{
	Stack<int> s;
	s.Push(3);
	s.Push(4);
	s.Push(2);
	s.Push(1);
	cout << s.Min() << endl;
	s.Push(0);
	cout << s.Min() << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}