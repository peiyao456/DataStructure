#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>
enum OP_SYM_NUM
{
	OP_NUM,
	OP_SYM,
	ADD,
	SUB,
	MUL,
	DIV
};
struct OP
{
	int _symbol;
	int _value;
};
void test()
{
	//后缀表达式为：12 3 4 + * 6 - 8 2 / +
	OP array[] = {
		{OP_NUM,12},
		{ OP_NUM,3 },
		{ OP_NUM,4 },
		{OP_SYM,ADD},
	    {OP_SYM,MUL},
		{ OP_NUM,6},
		{ OP_SYM,SUB },
		{ OP_NUM,8 },
		{ OP_NUM,2 },
		{ OP_SYM,DIV },
		{ OP_SYM,ADD }
	};
	stack<int> s;
	int result = 0;
	for (int i = 0; i < sizeof(array) / sizeof(OP);++i)
	{
		if (array[i]._symbol == 0)//表明是操作数
		{
			s.push(array[i]._value);
		}
		else//操作符
		{
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch (array[i]._value)
			{
			case ADD:
				result = left + right;
				break;
			case SUB:
				result = left - right;
				break;
			case MUL:
				result = left * right;
				break;
			case DIV:
				result = left / right;
				break;
			default:
				assert(false);
				break;
			}
			s.push(result);
		}
	}
	cout << result << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}