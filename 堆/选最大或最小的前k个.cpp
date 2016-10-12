//题目描述:找1000个数中最大的前10个，建一个小堆。

//仿函数
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

template<typename T, typename Compare = Greater<T>>
class HeapSearch
{
public:
	HeapSearch(T* _a , size_t size,size_t k)
	{
		for (size_t i = 0; i < k; ++i)
		{
			_heap.push_back(_a[i]);//将数组中的前k个元素入堆
		}
		for (int i = (k - 2) / 2; i >= 0; --i)
		{
			_AdjustDown(i,k);//向下调整
		}
		FindK(_a,size,k);
	}
	
	void Show(size_t k)
	{
		if (k)
		{
			for (size_t i = 0; i < k;++i)
				cout << _heap[i] << " ";
			cout << endl;
		}
	}
	void FindK(int array[], size_t size,size_t k)
	{
		Compare com;
		for (size_t i = 10; i < size; ++i)
		{
			//if (array[i] > _heap[0])
			if(com(_heap[0],array[i]))
			{
				swap(array[i], _heap[0]);
				_AdjustDown(0, k);
			}
			else
				continue;
		}
	}
protected:
	void _AdjustDown(size_t index,size_t k)
	{
		size_t parent = index;
		size_t child = 0;
		Compare com;
		while (child < k)
		{
			child = parent * 2 + 1;
			//if (child + 1 < _heap.size() && _heap[child] < _heap[child + 1])
			if (child + 1 < k && com(_heap[child + 1], _heap[child]))
				++child;
			//if (child < _heap.size()&&_heap[parent] < _heap[child])
			if (child < k && com(_heap[child], _heap[parent]))
			{
				swap(_heap[parent], _heap[child]);
				parent = child;
			}
			else
				break;
		}
	}
private:
	vector<T> _heap;
};
void testK()
{
	int array[1000] = { 10,20,30,5,6,7,8,9,0,1,2,23,56 };
	HeapSearch<int, Less<int>> h(array,100,10);
	h.Show(10);
}
int main()
{
	testK();
	system("pause");
	return 0;
}