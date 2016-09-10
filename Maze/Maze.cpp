#include"Maze.h"

const int Rows = 10;
const int Cols = 10;
const int startRow = 2;
const int startCol = 0;

void Stack::CheckCapacity(int count)
{
	if (_size + count > _capacity)
	{
		int NewCapacity = _size + count + 3;
		Pos* tmp = new Pos[NewCapacity];
		
		for (int i = 0; i < _size; ++i)
		{
			_data[i] = tmp[i];
		}
		//delete[] _data;
		_data = tmp;
		_capacity = NewCapacity;
	}
}
Stack::Stack()
	:_data(new Pos [3])
	,_size(0)
	,_capacity(3)
{}
Stack::~Stack()
{
	if (_data != NULL)
	{
		delete[] _data;
		_size = 0;
		_capacity = 0;
	}
}
void Stack::Push(Pos x)
{
	CheckCapacity(1);
	_data[_size++] = x;
}
void Stack::Pop()
{
	if (_size > 0)
	{
		_size--;
	}
}
bool Stack::isEmpty()
{
	return _size == 0;
}

Pos& Stack::Top()
{
	return _data[_size - 1];
}

Maze::Maze()
{
	char c = 0;
	FILE *pf = fopen("MazeMap.txt","r");
	if (pf == NULL)
	{
		perror("open file for read:");
		exit(EXIT_FAILURE);
	}

	_rows = Rows;
	_cols = Cols;
	_entry._row = startRow;
	_entry._col = startCol;
	_maze = new int[_rows* _cols];

	//读取迷宫
	for (int i = 0; i < _rows; ++i)
	{
		for (int j = 0; j < _cols;)
		{
			c = fgetc(pf)- '0';
			if ((c == 0) || (c == 1))
			{
				_maze[i * _cols + j] = c;
				++j;
			}
		}
	}
	fclose(pf);
}

Maze::~Maze()
{
	if (_maze)
	{
		delete[] _maze;
		_rows = 0;
		_cols = 0;
	}
}
bool Maze::isAccess(Pos pos)
{
	if ((pos._col >= 0) && (pos._col < _cols)
		&& (pos._row >= 0) && (pos._row < _rows)
		&& (_maze[pos._col + _cols * pos._row] == 0))
	{
		return true;
	}
	else
		return false;
}

bool Maze::GetPath()
{
	Pos pos = _entry;
	_s.Push(pos);
	_maze[pos._row*_cols + pos._col] = 2;

	while (!_s.isEmpty())
	{
		Pos next = _s.Top();
		if ((next._col == _cols - 1 )|| (next._row == _rows - 1)||(next._row == 0))
		{
			return true;
		}
		next._row++;
		if (isAccess(next))
		{
			_maze[next._row*_cols + next._col] = 2;//设置当前路径已走
			_s.Push(next);
			continue;
		}

		next._row--;
		if (isAccess(next))
		{
			_maze[next._row*_cols + next._col] = 2;//设置当前路径已走
			_s.Push(next);
			continue;
		}

		next._col++;
		if (isAccess(next))
		{
			_maze[next._row*_cols + next._col] = 2;//设置当前路径已走
			_s.Push(next);
			continue;
		}

		next._col--;
		if (isAccess(next))
		{
			_maze[next._row*_cols + next._col] = 2;//设置当前路径已走
			_s.Push(next);
			continue;
		}
		//说明当前路径走不通，出栈，并标记
		_s.Pop();
		_maze[next._row*_cols+next._col] = 3;
	}
	return false;
}

void Maze::PrintMap()
{
	for (int i = 0; i < _rows; ++i)
	{
		for (int j = 0; j < _cols; ++j)
		{
			cout << _maze[i*_cols + j] << " ";
		}
		cout << endl;
	}
}