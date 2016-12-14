#pragma once
#include<iostream>
using namespace std;
class UnionFindSet
{
public:
	UnionFindSet(int n)
		:_size(n)
	{
		_a = new int[n];
		for(int i = 0; i < n; ++i)
		{
			_a[i] = -1;
		}
	}
	~UnionFindSet()
	{
		if(_a)
		{
			delete[] _a;
			_a = NULL;
			_size = 0;
		}
	}
	int Find(const int& x)
	{
		int root = x;
		while(_a[root] >= 0)
		{
			root = _a[root];
		}
		return root;
	}
	void Union(const int x1,const int x2)
	{
		int root1 = Find(x1);
		int root2 = Find(x2);

		_a[root1] += _a[root2];
		if(root1 != root2)
		{
			_a[root2] = root1;
		}
	}
	int Friends(int n,int m,int r[][2])
	{
		for(int i = 0; i < m; ++i)
		{
			Union(r[i][0],r[i][1]);
		}
		int count = 0;
		for(int i = 0; i < _size; ++i)
		{
			if(_a[i] < 0)
				++count;
		}
		return count-1;
	}
private:
	int* _a;
	int _size;
};

void TestUnionFindSet()
{
	
	const int m = 4;
	const int n = 5;//5个朋友
	UnionFindSet ufs(6);
	int r[m][2] = {{1,2},{2,3},{4,5},{1,3}};
	cout<<"朋友圈的个数?"<<ufs.Friends(n,m,r)<<endl;
}