//声明：代码中的几处注释，仅仅是个人心得
#pragma once
#include<iostream>
using namespace std;
#include<vector>

template<typename T>
struct Triple
{
	T _value;
	size_t _row;
	size_t _col;
	Triple(T value,size_t row,size_t col)
		:_value(value)
		,_row(row)
		,_col(col)
	{}
};
template<typename T>
class SparseMatrix
{
public:
	typedef Triple<T> Triple;
	SparseMatrix(T* a, size_t m, size_t n, const T& invalid)
		:_rowSize(m)
		, _colSize(n)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < m; ++i)
		{
			for (size_t j = 0; j < n;++j)
			{
				if (a[i * n + j] != invalid)
				{
					_a.push_back(Triple(a[i * n + j], i, j));
				}
				else
				{
					continue;
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _rowSize; ++i)
		{
			for (size_t j = 0; j < _colSize; ++j)
			{
				size_t size = _a.size();
				/*if ((_a[index]._row == i)
					&& (_a[index]._col == j)//注意：三个条件顺序不同，下边的实现则不同
					&& (index < size))*/  //如果这样写，下边的加一操作必须进行条件判断
				if ((index < size)
					&&(_a[index]._row == i)
					&& (_a[index]._col == j))//最好写成这样
				{
					cout << _a[index]._value << " ";
					//if (index != size - 1)
						++index;
				
				}
				else
				{
					cout << _invalid << " ";
				}
			}
			cout << endl;
		}
	}
private:
	vector<Triple> _a;//存放结构体的容器
	size_t _rowSize;
	size_t _colSize;
	T _invalid;
};
void TestSparseMatrix()
{
	int a[5][6] = {
		{0,1,0,3,0,5},
		{0,0,0,0,0,0},
		{0,2,0,4,0,6},
		{0,0,0,0,0,0},
		{ 0,0,0,0,0,0 }
	};
	SparseMatrix<int> sp((int*)a,5,6,0);
	sp.Display();
}