//�ж�Ԫ�س�ջ����ջ���еĺϷ���
//���磬��ջ���У�1,2,3,4,5������ջ���У�4,5,3,2,1���ǺϷ�����

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