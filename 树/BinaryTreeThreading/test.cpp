#include"BinaryTreeThreading.h"
void test()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#' , '#', 5, 6 };
	BinaryTreeThreading<int> b1(array1,10,'#');
	b1.InOrderThreading();
	b1.InOrder();
	int array2[15] = { 1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8 };
	BinaryTreeThreading<int> b2(array2, 15, '#');
	b2.PreOrderThreading();
	b2.PreOrder();
	int array3[15] = { 0,1,3,'#','#',4,'#','#',2,5 };
	BinaryTreeThreading<int> b3(array3, 10, '#');
	b3.PostOrderThreading();
	b3.PostOrder();
}
int main()
{
	test();
	system("pause");
	return 0;
}