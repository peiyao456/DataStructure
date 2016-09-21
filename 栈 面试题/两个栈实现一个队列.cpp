#include<iostream>
using namespace std;
#include<stack>

//ʵ�ַ���һ
//ÿ��pushʱ�����ջ2��Ϊ�գ���ջ2������Ԫ��push��ջ1
//popʱ����ջ2��Ϊ�գ�ֱ�Ӵ�ջ2pop������ջ1��Ԫ��push��ջ2����pop
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
		if (_s1.empty() && _s2.empty())//s1,s2��Ϊ��
		{
			return;
		}
		if (!_s2.empty())//s2��Ϊ��
		{
			_s2.pop();
			
		}
		else if (!_s1.empty() && _s2.empty())//s1��Ϊ��
		{
			//while(!_s1.empty())
			while (_s1.size() != 1)
			{
				_s2.push(_s1.top());//������pushһ��
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

//ʵ�ַ�����
//ÿ��pop��֮�󶼽�ջ2��ʣ�µ�Ԫ��ȫ��push��ջ1
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
		if (_s1.empty() && _s2.empty())//s1,s2��Ϊ��
		{
			return;
		}
		if (!_s2.empty())//s2��Ϊ��
		{
			_s2.pop();
			
		}
		else if (!_s1.empty() && _s2.empty())//s1��Ϊ��
		{
			//while(!_s1.empty())
			while (_s1.size() != 1)
			{
				_s2.push(_s1.top());//������pushһ��
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