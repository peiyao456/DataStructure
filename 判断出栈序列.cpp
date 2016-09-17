//判断元素出栈、入栈序列的合法性
//比如，入栈序列（1,2,3,4,5），出栈序列（4,5,3,2,1）是合法序列

#include<iostream>
using namespace std;
#include<stack>

bool isOrder(int pushS[], int  popS[], int n)
{
	stack<int> s;
	int j = 0;
		
	for (int i = 0; i < n; ++i)
	{
		s.push(pushS[i]);
		while (!s.empty() && s.top() == popS[j])
		{
			s.pop();
			j++;
		}
	}
	return s.empty();
}

void test()
{
	int pushS[5] = { 1,2,3,4,5 };
	int popS[5] = { 4,5,3,2,1};

	bool ret = isOrder(pushS, popS,  5);
	cout << ret << endl;
}

int main()
{
	test();

	system("pause");
	return 0;
}