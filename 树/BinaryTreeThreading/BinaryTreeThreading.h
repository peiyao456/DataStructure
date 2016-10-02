//注明：在后序遍历线索二叉树中，需要找某个结点的父节点，本人使用递归找的，但是递归太深会造成
//栈溢出,所以，最好还是在结点的定义中，多定义一个成员parent，这样就会好一点。
//这个方法之后会继续补充。
#pragma once
#include<iostream>
using namespace std;
#include<assert.h>

enum Type
{
	LINK,
	THREAD
};
template<typename T>
struct BinaryTreeTNode
{
	T _data;
	BinaryTreeTNode* _lchild;
	BinaryTreeTNode* _rchild;
	Type _lTag;
	Type _rTag;
	BinaryTreeTNode(const T& x = T())
		:_data(x)
		,_lchild(NULL)
		,_rchild(NULL)
		,_lTag(LINK)
		,_rTag(LINK)
	{}
};

template<typename T>
class BinaryTreeThreading
{
	typedef BinaryTreeTNode<T> Node;
public:
	BinaryTreeThreading(T* a, size_t size, const T& invalid)
		:_root(NULL)
		,prev(NULL)
	{
		size_t index = 0;
		_root = _Create(a, size, index, invalid);
	}
	void PreOrderThreading()
	{
		_PreOrderThreading(_root);
	}
	void InOrderThreading()
	{
		_InOrderThreading(_root);
	}
	void PostOrderThreading()
	{
		_PostOrderThreading(_root);
	}
	void InOrder()//中序遍历线索二叉树
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_lTag == LINK)
			{
				cur = cur->_lchild;
			}
			cout << cur->_data << " ";
			while (cur->_rTag == THREAD && cur->_rchild != NULL)
			{
				cur = cur->_rchild;
				cout << cur->_data << " ";
			}
			cur = cur->_rchild;
		}
		cout << endl;
	}
	void PreOrder()//先序遍历
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_lTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_lchild;
			}
			cout << cur->_data << " ";
			cur = cur->_rchild;
		}
		cout << endl;
	}
	void PostOrder()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_lTag == LINK )
			{
				cur = cur->_lchild;
			}
			while (cur && cur->_lTag == THREAD)
			{
				cout << cur->_data << ' ';
				prev = cur;
				cur = cur->_rchild;
			}
			if (cur == _root )//访问到根节点
			{
				cout << cur->_data << " ";
				return;
			}
			if (cur->_rchild == _root)
			{
				cout << cur->_data << " ";
				cout << cur->_rchild->_data << " ";
				return;
			}
			while (cur && cur->_rchild == prev)
			{
				cout << cur->_data << ' ';
				prev = cur;
				cur = _Parent(_root,cur);  
			}
			
			if (cur && cur->_rTag == LINK)
			{
				cur = cur->_rchild;
			}
			
		}
		cout << endl;
	}
protected:
	Node* _Parent(Node* root, Node* p)//寻找结点p的父节点
	{
		if (root == NULL || p == NULL)
			return NULL;
		if (root->_lchild == p || root->_rchild == p)
			return root;
		_Parent(root->_lchild,p);
		_Parent(root->_rchild,p);
		return root;
	}
	Node* _Create(T* a,size_t size,size_t& index,const T& invalid)
	{
		assert(a != NULL);
		Node* root = NULL;
		if (a[index] != invalid && index < size)
		{
			root = new Node(a[index]);
			root->_lchild = _Create(a, size, ++index, invalid);
			root->_rchild = _Create(a, size, ++index, invalid);
		}
		return root;
	}
	
	void _PreOrderThreading(Node* root)
	{
	
		if (root)
		{
			if (!root->_lchild)
			{
				root->_lTag = THREAD;
				root->_lchild = prev;        //前继线索
			}
			if (prev && !prev->_rchild)
			{
				prev->_rTag = THREAD;
				prev->_rchild = root;        //后继线索
			}
			prev = root;
			if (LINK == root->_lTag)
				_PreOrderThreading(root->_lchild);
			if (LINK == root->_rTag)
				_PreOrderThreading(root->_rchild);
		}
	}
	
	
	
	void _InOrderThreading(Node* root)
	{
		if (root)
		{
			_InOrderThreading(root->_lchild);
			if (root->_lchild == NULL)
			{
				root->_lTag = THREAD;
				root->_lchild = prev;
			}
			if (prev && prev->_rchild == NULL)
			{
				prev->_rTag = THREAD;
				prev->_rchild = root;
			}
			prev = root;
			_InOrderThreading(root->_rchild);
		}
	}
	void _PostOrderThreading(Node* root)
	{
		if (root == NULL)
			return;
		if (root)
		{
			if (LINK == root->_lTag)
				_PostOrderThreading(root->_lchild);

			if (LINK == root->_rTag)
				_PostOrderThreading(root->_rchild);

			if (!root->_lchild)
			{
				root->_lTag = THREAD;
				root->_lchild = prev;        //前继线索
			}
			if (prev && !prev->_rchild)
			{
				prev->_rTag = THREAD;
				prev->_rchild = root;        //后继线索
			}
			prev = root;
		}
	}
private:
	Node* _root;
	Node* prev;
};