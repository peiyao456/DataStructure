#include<iostream>
using namespace std;
void AdjustDown(int a[],size_t i,size_t len)
{
	assert(a && i >= 0 && len > 0);
	size_t parent = i;
	size_t child = 2 * parent + 1;
	while (child < len)
	{
		if (child + 1 < len && a[child] < a[child + 1])
			++child;
		if (a[parent] < a[child])
		{
			swap(a[parent], a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

void HeapSort(int a[], size_t n)
{
	assert(a && n);
	for (int i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(a,i,n);//向下调整
	}
	/*for (size_t i = 0;i < n;++i)
	{
		swap(a[0],a[n-1-i]);
		AdjustDown(a,0,n-i-1);
	}*/
	for (size_t i = n-1;i > 0;--i)
	{
		swap(a[0],a[i]);
		AdjustDown(a,0,i);
	}
}
void Show(int a[],size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
void testSort()
{
	int a[] = { 3,4,5,1,2,6,7 };
	HeapSort(a,7);
	Show(a,7);
}
int main()
{
	testSort();
	system("pause");
	return 0;
}