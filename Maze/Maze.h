#ifndef __MAZE_H__
#define __MAZE_H__

#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;

typedef struct NodePos
{
	int _row;
	int _col;
	NodePos(int row = 0,int col = 0)
		:_row(row)
		,_col(col)
	{}
}Pos;
class Stack
{
public:
	Stack();
	~Stack();
	void Push(Pos pos);
	void Pop();
	bool isEmpty();
	Pos& Top();
protected:
	void CheckCapacity(int count);
protected:
	Pos* _data;
	int _size;
	int _capacity;
};
class Maze
{
public:
	Maze();
	~Maze();
	bool GetPath();
	void PrintMap();
protected:
	bool isAccess(Pos pos);
protected:
	int _rows;
	int _cols;
	int* _maze;
	Stack _s;
	Pos _entry;
};
#endif//__MAZE_H__