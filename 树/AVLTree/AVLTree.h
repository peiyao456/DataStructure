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
			//找插入位置
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
			//无法插入
			else
				return false;
		}
		 cur = new Node(key);
		 cur->_parent = parent;
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		while (parent)//调整到根节点之后就不再调整
		{
			//if (parent->_parent && parent->_parent->_left == parent)
			if(cur == parent->_left)
				--parent->_bf;
			else if (cur == parent->_right)             //if (parent->_parent->_right == parent)
				++parent->_bf;

			if (parent->_bf == 0)//说明parent的高度并没有改变，此时调整结束
				return true;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else
			{
				if (parent->_bf == 2)//树已经不平衡，需要调整
				{
					if (cur->_bf == 1)
						_RotateL(parent);
					else             //if (cur->_bf == -1)
						_RotateRL(parent);
				}
			//	if (parent->_bf == -2)
				else
				{
					if (cur->_bf == -1)
						_RotateR(parent);
					else                 //if (cur->_bf == 1)
						_RotateLR(parent);
				}
			}
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
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool IsBalanceOP()
	{
		int height = 0;
		return _IsBalanceOP(_root,height);
	}
	size_t Height()
	{
		return _Height(_root);
	}
protected:
	//优化版本
	bool _IsBalanceOP(Node* root,int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}
		int leftHeight = 0;
		if (!_IsBalanceOP(root->_left, leftHeight))
			return false;
		int rightHeight = 0;
		if (!_IsBalanceOP(root->_right, leftHeight))
			return false;
		height = 1 + rightHeight > leftHeight ? rightHeight : leftHeight;
		return true;
	}
	size_t _Height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
	//大多数结点会计算两次，时间复杂度0(N*N)
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);

		if (rightHeight - leftHeight != root->_bf)
		{
			cout << "平衡因子异常" << root->_key << " ";
		}

		return abs(rightHeight - leftHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}
	void _RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* ppNode = parent->_parent;//记住parent的父节点
		Node*  subLR = subL->_right;

		//parent与subLR连接
		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;

		//parent与subL连接
		subL->_right = parent;
		parent->_parent = subL;

		//ppNode与subL进行连接
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
		Node* ppNode = parent->_parent;//记住parent的父节点
		Node* subRL = subR->_left;

		//subRL与parent相连
		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;

		//subR与parent相连接
		subR->_left = parent;
		parent->_parent = subR;

		//ppNode与subR连接
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
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);
		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 1;
		}
		else // bf == -1
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = -1;
		}
	}
	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);
		if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 1;
		}
		else
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = -1;
		}

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
	AVLTree<int, int> tree1;
	int array1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < sizeof(array1) / sizeof(array1[0]); ++i)
	{
		tree1.InsertNonR(array1[i]);
	}
	tree1.InOrderNonR();
	cout <<"IsBalance?"<< tree1.IsBalance() << endl;
	cout << "IsBalance?" << tree1.IsBalanceOP() << endl;
	int array2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int, int> tree2;
	for (size_t i = 0;i<sizeof(array2) / sizeof(array2[0]);++i)
	{
		tree2.InsertNonR(array2[i]);
	}
	tree2.InOrderNonR();
	cout << "IsBalance?" << tree2.IsBalance() << endl;
	cout << "IsBalance?" << tree2.IsBalanceOP() << endl;
}