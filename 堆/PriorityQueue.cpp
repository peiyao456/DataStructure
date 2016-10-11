//ע�������ļ�ʹ�õ�Heap��heap.cpp�ļ��ж����Heap
template<typename T,typename Compare = Greater<T>>
class PriorityQueue
{
public:
	PriorityQueue(T* a,size_t size)
		:_q(a,size)
	{}
	void Pop()
	{
		_q.Pop();
	}
	void Push(const T& x)
	{
		_q.Push(x);
	}
	const T& Top()
	{
		return _q.Top();
	}
	void Show()
	{
		_q.Show();
	}
private:
	Heap<T,Compare> _q;
};
void testQueue()
{
	int a[] = { 3,4,5,1,2,6,7 };
	//����С��
	PriorityQueue<int,Less<int>> q1(a,7);
	q1.Show();
	q1.Push(0);
	q1.Show();
	q1.Pop();
	q1.Show();
	//���Դ��
	PriorityQueue<int> q2(a, 7);
	q2.Show();
	q2.Push(10);
	q2.Show();
	q2.Pop();
	q2.Show();
}