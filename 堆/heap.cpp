#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
//·Âº¯Êý
template<typename T>
struct Less
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};
template<typename T>
struct Greater
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template<typename T,typename Compare = Greater<T>>
class Heap
{
public:
	Heap(T* _a,size_t size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			_heap.push_back(_a[i]);
		}
		for (int i = (size-2) / 2; i >= 0; --i)
		{
			_HeapDown(i);//µ÷Õû
		}
	}
	void Show()
	{
		if (_heap.size())
		{
			for (size_t i = 0; i < _heap.size();++i)
				cout << _heap[i] << " ";
			cout << endl;
		}
	}
	void Push(const T& x)
	{
		_heap.push_back(x);
		_HeapUp(_heap.size()-1);
	}
	void Pop()//É¾³ý¶Ñ¶¥µÄÔªËØ
	{
		assert(_heap.size()>0);
		swap(_heap[0],_heap[_heap.size()-1]);
		_heap.pop_back();
		_HeapDown(0);
	}
protected:
	void _HeapDown(size_t index)
	{
		size_t parent = index;
		size_t child = 0;
		Compare com;
		while (child < _heap.size())
		{
			child = parent * 2 +1 ;
			//if (child + 1 < _heap.size() && _heap[child] < _heap[child + 1])
			if (child + 1 < _heap.size() && com(_heap[child+1],_heap[child]))
				++child;
			//if (child < _heap.size()&&_heap[parent] < _heap[child])
			if (child < _heap.size() && com(_heap[child],_heap[parent]))
			{
				swap(_heap[parent], _heap[child]);
				parent = child;
			}
			else
				break;
		}
	}
	void _HeapUp(size_t child)
	{
		assert(_heap.size()>0);
		size_t parent = 0;
		Compare com;
		while (child > 0)
		{
			parent = (child - 1) / 2;
			//if (_heap[parent] < _heap[child])
			if(com(_heap[child],_heap[parent]))
			{
				swap(_heap[parent], _heap[child]);
				child = parent;
			}
			else
				break;
		}
	}
private:
	vector<T> _heap;
};

void testHeap()
{
	int a[] = { 3,4,5,1,2,6,7 };
	//²âÊÔ´ó¶Ñ
	Heap<int> h1(a,7);
	h1.Show();
	h1.Push(10);
	h1.Show();
	h1.Pop();
	h1.Show();
	//²âÊÔÐ¡¶Ñ
	Heap<int, Less<int>> h2(a, 7);
	h2.Show();
	h2.Push(0);
	h2.Show();
	h2.Pop();
	h2.Show();
}
int main()
{
	testHeap();
	system("pause");
	return 0;
}