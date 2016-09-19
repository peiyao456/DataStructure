//保证push pop min的时间复杂度都是O（1）
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