#pragma once

#include<iostream>
using namespace std;
#include<stack>

enum COLOR
{
	RED,
	BLACK
};

template<typename K,typename V>
struct RBTreeNode
{
	
	K _key;
	V _value;

	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;

	COLOR _col;

	RBTreeNode(const K& key,const V& value = 0)
		:_key(key)
		,_value(value)
		,_parent(NULL)
		,_left(NULL)
		,_right(NULL)
		,_col(RED)
	{}
};
template<typename K,typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}

	bool Insert(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			_root->_col = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else//�ҵ�����ͬ��Ԫ��
				return false;
		}

		cur = new Node(key);
		//parent�ز�ΪNULL
		if (parent->_key < key)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;
		//����
		while (cur != _root && parent->_col == RED)
		{
			Node* grandFather = parent->_parent;//grandFather�ز�Ϊ��
			Node* uncle = NULL;
			if (parent == grandFather->_left)
			{
				uncle = grandFather->_right;
				//1.uncle�������Ǻ�ɫ
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandFather->_col = RED;
					//���ϵ���
					cur = grandFather;
					parent = cur->_parent;
				}
				//2.uncle�������Ǻ�ɫ
				//3.uncle������
				else
				{
					if (cur == parent->_right)
					{
						_RotateL(parent);
						swap(parent,cur);
					}
					
					_RotateR(grandFather);

					//cur->_col = RED;
					parent->_col = BLACK;
					grandFather->_col = RED;

					cur = parent;
					parent = cur->_parent;
				}
			}
		
			else             //if (grandFather && parent == grandFather->_right)
			{
				uncle = grandFather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandFather->_col = RED;
					//���ϵ���
					cur = grandFather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						_RotateR(parent);
						swap(cur,parent);
					}
					_RotateL(grandFather);
					
					//cur->_col = RED;
					grandFather->_col = RED;
					parent->_col = BLACK;

					cur = parent;
					parent = cur->_parent;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
	void InOrderNonR()
	{
		if (_root == NULL)
		{
			cout << endl;
			return;
		}
		Node* cur = _root;
		stack<Node*> s;
		while (cur || !s.empty())
		{
			while (cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_key << " ";
			cur = top->_right;
		}
		cout << endl;
	}
	bool Blance()
	{
		if(_root == NULL)
		{
			return true;
		}
		int count = 0;//����ĳһ��·���Ϻ�ɫ���ĸ���
		int k = 0;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_col == BLACK)
			{
				++count;
			}			
			cur = cur->_left;
		}
			return _Blance(_root,count,k);	
	}
protected:
	bool _Blance(Node* root,const int& count,int k)
	{
		if(root == NULL)
		{
			return k == count;
		}
		if(root->_col == BLACK)
		{
			++k;
		}
		//���ڵĺ�ɫ���
		if(root->_col == RED && root->_parent->_col == RED)
		{
			cout<<root->_key<<endl;
			return false;
		}
		return _Blance(root->_left,count,k) &&
			    _Blance(root->_right,count,k);
		//ÿ��·���Ϻ�ɫ�������һ��
	}


	
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		//����parent��subRL
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		//����parent��subR
		subR->_left = parent;
		parent->_parent = subR;

		//����ppNode��subR
		if (ppNode == NULL)
		{
			_root = subR;
			_root->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;
		//����parent��subLR
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		//����parent��subL
		subL->_right = parent ;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			_root->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}
private:
	Node* _root;
};
