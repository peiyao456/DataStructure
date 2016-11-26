#pragma once
#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>
template<typename T>
struct TreeNode
{
	T _data;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode(const T& x)
		:_data(x)
		,_left(NULL)
		,_right(NULL)
	{}
};
template<typename T>
class BinaryTree
{
	typedef TreeNode<T> Node;
public:
	BinaryTree(T a[],int size,const T& invalid)
	{
		size_t index = 0;
		_root = _Create(a,size,index,invalid);
	}
	//求二叉树的镜像
	void Mirror()
	{
		_Mirror(_root);
	}
	void PreOrderR()
	{
		_PreOrderR(_root);
		cout<<endl;
	}
	void PreOrderNonR()
	{
		stack<Node*> s;
		Node* cur = _root;
		while(cur || !s.empty())
		{
			while(cur)
			{
				cout<<cur->_data<<" ";
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout<<endl;
	}
	size_t Depth()
	{
		return _Depth(_root);
	}
protected:
	Node* _Create(T a[],int size,size_t& index,const T& invalid)
	{
		assert(a);
		Node* root = NULL;
		while(index < size && a[index] != invalid)
		{
			root = new Node(a[index]);
			root->_left = _Create(a,size,++index,invalid);
			root->_right = _Create(a,size,++index,invalid);
		}
		return root;
	}
	void _PreOrderR(Node* root)
	{
		if(root == NULL)
			return;
		cout<<root->_data<<" ";
		_PreOrderR(root->_left);
		_PreOrderR(root->_right);
	}
	void _Mirror(Node* root)
	{
		if(root == NULL)
			return;
		if(root->_left == NULL && root->_right == NULL)
			return;
		//交换结点的左右指针
		swap(root->_left,root->_right);

		if(root->_left)
			_Mirror(root->_left);
		if(root->_right)
			_Mirror(root->_right);
	}
	size_t _Depth(Node* root)
	{
		if(root == NULL)
			return 0;
		int left = _Depth(root->_left);
		int right = _Depth(root->_right);
		return left > right ? left + 1 : right +1;
	}
private:
	Node* _root;
};
void Test()
{
	int array[] = {8,6,5,'#','#',7,'#','#',10,9,'#','#',11};
	BinaryTree<int> bt(array,sizeof(array)/sizeof(array[0]),'#');
	bt.PreOrderNonR();
	bt.PreOrderR();
	bt.Mirror();
	bt.PreOrderNonR();
	bt.PreOrderR();
	cout<<"Depth?"<<bt.Depth()<<endl;
}