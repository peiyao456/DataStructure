#include"Queue.hpp"
#include"Queue.cpp"

void test()
{
	Queue<int> q1;
	q1.Push(1);
	q1.Push(2);
	q1.Push(3);
	q1.Push(4);
	q1.Push(5);
	q1.Pop();
	q1.Pop();
	q1.Display();
	cout << q1 << endl;
	Queue<int> q2(q1);
	q2.Display();
}
int main()
{
	test();
	system("pause");
	return 0;
}