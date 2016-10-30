#include"RBTree.hpp"
void testRBTree()
{
	int array1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> tree1;
	for (int i = 0; i < sizeof(array1) / sizeof(array1[0]); ++i)
	{
		tree1.Insert(array1[i]);
		cout<<array1[i]<<"->" << tree1.Blance()<<endl;
	}
	tree1.InOrderNonR();
	cout<< tree1.Blance()<<endl;
}
int main()
{
	testRBTree();
	system("pause");
	return 0;
}