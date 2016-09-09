#include"Stack.hpp"
#include"Stack.cpp"

void test()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Push(5);
	cout << s1 << endl;
	s1.Display();
}
int main()
{
	test();
	system("pause");
	return 0;
}