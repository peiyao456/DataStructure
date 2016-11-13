#pragma once
#include<iostream>
using namespace std;

template<typename K,int M >
struct BTreeNode
{
	K _keys[M];//存储每个结点的关键字
	BTreeNode<K,M>* _subs[M + 1];//存储子节点的指针数组

	BTreeNode<K,M>* _parent;
	size_t _size;//存储关键字的个数

	BTreeNode()
		:_parent(NULL)
		,_size(0)
	{
		for(int i = 0; i < M; ++i)
		{
			_keys[i] = K();
			_subs[i] = NULL;
		}
		_subs[M] = NULL;
	}
};
template<typename K,int M >
class BTree
{
	typedef BTreeNode<K,M> Node;
public:
	BTree()
		:_root(NULL)
	{}

	pair<Node*,int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while(cur)
		{
			int i = 0;
			while(i < cur->_size)
			{
				if(cur->_keys[i] < key)//继续遍历当前结点的其他关键字
				{
					++i;
				}
				else if(cur->_keys[i] > key)
				{
					break;//跳出当前结点
				}
				else
				{
					return pair<Node*,int>(cur,i);
				}
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		//cur为NULL，没有找到，返回parent,便于之后的插入
		return pair<Node*,int>(parent,-1);
	}

	void InsertKey(Node* node,const K& key,Node* sub)
	{
		int i = node->_size - 1;
		while( i >= 0 )
		{
			if(node->_keys[i] > key)
			{
				node->_keys[i + 1] = node->_keys[i];
				//指向孩子结点的指针也向后移动
				node->_subs[i + 2] = node->_subs[i + 1];
			}
			else
			{
				break;
			}
			--i;
		}
		//插入结点
		node->_keys[i + 1] = key;
		node->_subs[i + 2] = sub;
		if(sub)
			sub->_parent = node;
		++node->_size;
	}

	bool Insert(const K& key)
	{
		if(_root == NULL)
		{
			_root = new Node;
			_root->_keys[0] = key;
			_root->_parent = NULL;
			_root->_size = 1;

			return true;
		}
		//判断当前要插入的结点是否已经存在，如果存在，不可插入
		pair<Node*,int> ret = Find(key);
		if(ret.second != -1)//找到结点
		{
			return false;
		}

		Node* cur = ret.first;
		Node* sub = NULL;
		K newKey = key;
		while(1)
		{
			//插入结点
			InsertKey(cur,newKey,sub);
			if(cur->_size < M)//没有满
				return true;

			//已满，则进行分裂
			//拷贝key以及孩子结点
			int mid = cur->_size / 2;
			Node* tmp = new Node;  //开辟新的结点，存储分裂后的右边子树
			int j = 0;
			int i = 0;
			for(i = mid+1; i < cur->_size; ++i,++j)
			{
				tmp->_keys[j] = cur->_keys[i];//拷贝关键字
				tmp->_subs[j] = cur->_subs[i];//拷贝叶子结点
				//连接父节点
				if(tmp->_subs[j])
					tmp->_subs[j]->_parent = tmp;
				//将移走的元素的位置置为默认值
				cur->_keys[i] = K();
				cur->_subs[i] = NULL;
				++tmp->_size;
			}
			tmp->_subs[j] = cur->_subs[i];//拷贝多余的一个叶子结点
			if(tmp->_subs[i])
				tmp->_subs[i]->_parent = NULL;
			cur->_subs[i] = NULL;

			newKey = cur->_keys[mid];
			cur->_keys[mid] = K();
			sub = tmp;
			cur->_size = mid;


			if(cur->_parent == NULL)//cur是根节点
			{
				_root = new Node;
				_root->_keys[0] = newKey;
				_root->_size = 1;
				_root->_subs[0] = cur;
				_root->_subs[1] = sub;
				cur->_parent = _root;
				sub->_parent = _root;
				return true;
			}

			else
			{
				cur = cur->_parent;
			}
			
		}
		
	}

	void InOrder()
	{
		_InOrder(_root);
		cout<<endl;
	}
protected:
	void _InOrder(Node* root)
	{
		if(root == NULL)
			return ;
		int i = 0;
		while(i < root->_size)
		{
			_InOrder(root->_subs[i]);
			cout<<root->_keys[i]<<" ";
			++i;
		}
		_InOrder(root->_subs[i]);
	}
private:
	Node* _root;
};

void TestBTree()
{
	int array[] = {53, 75, 139, 49, 145, 36, 101};
	BTree<int,3> bt;
	for(int i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
	{
		bt.Insert(array[i]);
	}
	bt.InOrder();
}