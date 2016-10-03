#include<iostream>
using namespace std;
#include<stdlib.h>

template<typename T>
class StackArray
{
public:
	StackArray()
		:_array(new int [2])
		, _size1(0)
		, _size2(1)
		, _capacity(2)
	{}
	~StackArray()
	{
		if (NULL != _array)
		{
			delete[] _array;
			_array = NULL;
			_size1 = 0;
			_size2 = 0;
			_capacity = 0;
		}
	}
	void PushArr1(const T& x)
	{
		Capacity();
		_array[_size1] = x;
		_size1++;
	}
	void PushArr2(const T& x)
	{
		Capacity();
		_array[_size2] = x;
		_size2--;
	}
	void PopArray1()
	{
		if (_size1 > 0)
		{
			_size1--;
		}
	}
	void PopArray2()
	{
		if (_size2 != _capacity-1)
		{
			_size2++;
		}
	}
	T& TopArray1()
	{
		if (_size1 > 0)
		{
			return _array[_size1-1];
		}
	}
	T& TopArray2()
	{
		if (_size2 > 0)
		{
			return _array[_size2+1];
		}
	}
	void DisplayArray1()
	{
		if (_size1 > 0)
		{
			for (int i = _size1 - 1; i >= 0; --i)
			{
				cout << _array[i] << " ";
			}
			cout << endl;
		}
	}
	void DisplayArray2()
	{
		if (_size2 > 0)
		{
			for (int i = _size2 + 1 ; i <_capacity; ++i)
			{
				cout << _array[i] << " ";
			}
			cout << endl;
		}
	}
private:
	void Capacity()
	{
		if (_size1 + _size2 <= _capacity)
		{
			int NewCapacity = _capacity + 10;
			T* tmp = new T[NewCapacity];
			int k = NewCapacity - 1;
			//memcpy(tmp, _array1, _size1*sizeof(T));
			for (int i = 0; i < _size1; ++i)
			{
				tmp[i] = _array[i];
			}
			//memcpy(tmp+NewCapacity-1-_size2,_array2-_size2,_size2*sizeof(T));
			for (int i = _capacity-1; i > _capacity-_size2; --i)
			{
				tmp[k] = _array[i];
				k--;
			}
			delete[] _array;
			_size2 = NewCapacity - (_capacity - _size2);

			_capacity = NewCapacity;
		    _array = tmp;
		}
	}
private:
	T* _array;
	int _size1;
	int _size2;
	int _capacity;
};
//≤‚ ‘¥˙¬Î
void test()
{
	StackArray<int> s;
	s.PushArr1(1);
	s.PushArr1(2);
	s.PushArr1(3);
	s.PushArr1(4);
	s.PushArr1(5);
	s.PushArr1(6);
	s.PushArr1(7);
	s.DisplayArray1();
	s.PopArray1();
	s.DisplayArray1();

	s.PushArr2(5);
	s.PushArr2(6);
	s.PushArr2(7);
	s.PushArr2(8);
	s.PushArr2(9);
	s.PushArr2(10);
	s.DisplayArray2();
	s.PopArray2();
	s.DisplayArray2();
}
int main()
{
	test();
	system("pause");
	return 0;
}