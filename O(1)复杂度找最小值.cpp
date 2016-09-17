#include<iostream>
using namespace std;
#include<stack>

int Min(int arr[], int n)
{
	stack<int> s;
	s.push(arr[0]);
	for (int i = 1; i < n; ++i)
	{
		if (arr[i] > s.top())
		{
			int tmp = s.top();
			s.pop();
			s.push(arr[i]);
			s.push(tmp);
		}
		else
		{
			s.push(arr[i]);
		}
	}
	return s.top();
}

void test()
{
	int arr[] = { 20,3,0,1,5,7,3,200 };
	int ret = Min(arr,sizeof(arr)/sizeof(arr[0]));
	cout << ret << endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}