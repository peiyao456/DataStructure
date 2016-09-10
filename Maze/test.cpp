#include"Maze.h"
void test()
{
	Maze m;
	m.PrintMap();
	if (m.GetPath())
	{
		cout << "ÓÐÍ¨Â·" << endl;
	}
	m.PrintMap();
}
int main()
{
	test();
	system("pause");
	return 0;
}