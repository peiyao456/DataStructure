#pragma once
#include<iostream>
using namespace std;
#include<stack>

template<typename K,typename V>
struct AVLTreeNode
{
	K _key;
	V _value;

	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;
	AVLTreeNode(const K& key,const V& value = 0)
		:_key(key)
		,_value(value)
		,_left(NULL)
		,_right(NULL)
		,_parent(NULL)
		,_bf(0)
	{}
};
template<typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{
		_Destroy(_root);
	}
	bool InsertNonR(const K& key)
	{
		if (_root == NULL)
		{
			_root = new Node(key);
			_root->_parent = NULL;
			return true;
		}
		Node* cur = _root;
		Node* parent = _root;
		while (cur)
		{
			//�Ҳ���λ��
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
			//�޷�����
			else
			{
				return false;
			}
		}
		Node* newNode = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = newNode;
		}
		else
		{
			parent->_left = newNode;
		}
		newNode->_parent = parent;

		while (parent)//���������ڵ�֮��Ͳ��ٵ���
		{
			if (parent->_bf == 0)//˵��parent�ĸ߶Ȳ�û�иı䣬��ʱ��������
				break;
			if (parent->_parent->_left == parent)
				parent->_bf--;
			else                 //if (parent->_parent->_right == parent)
				parent->_bf++;
			
			if (parent->_bf == 2)//���Ѿ���ƽ�⣬��Ҫ����
			{
				if (parent->_right->_bf == 1)
					_RotateL(parent);
				else
					_RotateRL(parent);
			}
			if (parent->_bf == -2)
			{
				if (parent->_right->_bf == -1)
					_RotateR(parent);
				else
					_RotateLR(parent);
			}
			parent = parent->_parent;
		}
		return true;
	}
	void InOrderNonR()
	{
		if (_root == NULL)
			return;
		stack<Node*> s;
		Node* cur = _root;
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
protected:
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* ppNode = parent->_parent;//��סparent�ĸ��ڵ�
		Node*  subLR = subL->_right;

		//parent��subLR����
		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		//parent��subL����
		subL->_right = parent;
		parent->_parent = subL;

		//ppNode��subL��������
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
			subL->_parent = ppNode;

		}
		subL->_bf = parent->_bf = 0;
	}
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* ppNode = parent->_parent;//��סparent�ĸ��ڵ�
		Node* subRL = subR->_left;

		//subRL��parent����
		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		//subR��parent������
		subR->_left = parent;
		parent->_parent = subR;

		//ppNode��subR����
		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
		parent->_bf = subR->_bf = 0;
	}
	void _RotateLR(Node* parent)
	{
		_RotateL(parent->_left);
		_RotateR(parent);
	}
	void _RotateRL(Node* parent)
	{
		_RotateR(parent->_right);
		_RotateL(parent);
	}
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
private:
	Node* _root;
};
void TestAVL()
{
	AVLTree<int, int> at;
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
	{
		at.InsertNonR(array[i]);
	}
	at.InOrderNonR();
}
