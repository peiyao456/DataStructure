#include<iostream>
using namespace std;
#include<stack>

//实现方法一
//每次push时，如果栈2不为空，将栈2的所有元素push进栈1
//pop时，当栈2不为空，直接从栈2pop；否则将栈1的元素push进栈2，再pop
template<typename T>
class Queue
{
public:
	void Push(const T& x)
	{
		if (!_s2.empty())
		{
			while (!_s2.empty())
			{
				_s1.push(_s2.top());
				_s2.pop();
			}
		}
		_s1.push(x);
	}
	void Pop()
	{
		if (_s1.empty() && _s2.empty())//s1,s2均为空
		{
			return;
		}
		if (!_s2.empty())//s2不为空
		{
			_s2.pop();
			
		}
		else if (!_s1.empty() && _s2.empty())//s1不为空
		{
			//while(!_s1.empty())
			while (_s1.size() != 1)
			{
				_s2.push(_s1.top());//可以少push一次
				_s1.pop();
			}
			_s1.pop();
			
		}
	}
	void Display()
	{
		while (!_s2.empty())
		{
			cout << _s2.top() << " ";
			_s2.pop();
		}
		while (!_s1.empty())
		{
			_s2.push(_s1.top());
			_s1.pop();
		}
		while (!_s2.empty())
		{
			cout << _s2.top() << " ";
			_s2.pop();
		}
	}
	int Size()
	{
		return _s1.size() + _s2.size();
	}
public:
	stack<T> _s1;
	stack<T> _s2;
};

//实现方法二
//每次pop完之后都将栈2中剩下的元素全部push进栈1
template<typename T>
class Queue
{
public:
	void Push(const T& x)
	{
		_s1.push(x);
	}
	void Pop()
	{
		if (_s1.empty() && _s2.empty())//s1,s2均为空
		{
			return;
		}
		if (!_s2.empty())//s2不为空
		{
			_s2.pop();
			
		}
		else if (!_s1.empty() && _s2.empty())//s1不为空
		{
			//while(!_s1.empty())
			while (_s1.size() != 1)
			{
				_s2.push(_s1.top());//可以少push一次
				_s1.pop();
			}
			_s1.pop();
			
		}
		while (!_s2.empty())
		{
			_s1.push(_s2.top());
			_s2.pop();
		}
	}
	void Display()
	{
		while (!_s2.empty())
		{
			cout << _s2.top() << " ";
			_s2.pop();
		}
		while (!_s1.empty())
		{
			_s2.push(_s1.top());
			_s1.pop();
		}
		while (!_s2.empty())
		{
			cout << _s2.top() << " ";
			_s2.pop();
		}
	}
	int Size()
	{
		return _s1.size() + _s2.size();
	}
public:
	stack<T> _s1;
	stack<T> _s2;
};


void test()
{
	Queue<int> q;
	q.Push(2);
	q.Push(3);
	q.Push(1);
	q.Pop();
	q.Push(4);
	q.Push(5);
	q.Pop();
	cout << q.Size() << endl;
	q.Display();
}
int main()
{
	test();
	system("pause");
	return 0;
}