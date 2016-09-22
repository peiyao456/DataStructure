#include<iostream>
using namespace std;
#include<queue>
template<typename T>
class Stack
{
public:
	void Push(const T& x)
	{
		//q1,q2��Ϊ�գ�push��q1
		if (_q1.empty()&&_q2.empty())
		{
			_q1.push(x);
		}
		else if (!_q1.empty())//q1���վ�push��q1
		{
			_q1.push(x);
		}
		//q1�գ�q2���գ�ֱ�ӷ���q1������pop�Ļ����ܸ�����һЩ����Ҫ��֮����Ҫpush�Ͳ�������
		else//q2���գ�push��q2
		{
			_q2.push(x);
		}
	}
	T Pop()
	{
		if (_q1. empty() && _q2.empty())
		{
			exit(EXIT_FAILURE);
		}
		if (!_q1.empty())
		{
			while (_q1.size() != 1)
			{
				T tmp = _q1.front();
				_q1.pop();
				_q2.push(tmp);
			}
			T  ret = _q1.front();
			_q1.pop();
			return ret;
		}
		if (!_q2.empty())
		{
			while (_q2.size() != 1)
			{
				T tmp = _q2.front();
				_q2.pop();
				_q1.push(tmp);
			}
			T  ret = _q2.front();
			_q2.pop();
			return ret;
		}
		
	}
private:
	queue<T> _q1;
	queue<T> _q2;
};
void test()
{
	Stack<int> s;
	s.Push(1);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(7);
	cout << s.Pop() << endl;
	cout << s.Pop() << endl;
	cout << s.Pop() << endl;
	s.Push(8);
	cout << s.Pop() << endl;
	cout << s.Pop() << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}