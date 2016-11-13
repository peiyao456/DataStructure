#pragma once
#include<iostream>
using namespace std;

template<typename K,int M >
struct BTreeNode
{
	K _keys[M];//�洢ÿ�����Ĺؼ���
	BTreeNode<K,M>* _subs[M + 1];//�洢�ӽڵ��ָ������

	BTreeNode<K,M>* _parent;
	size_t _size;//�洢�ؼ��ֵĸ���

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
				if(cur->_keys[i] < key)//����������ǰ���������ؼ���
				{
					++i;
				}
				else if(cur->_keys[i] > key)
				{
					break;//������ǰ���
				}
				else
				{
					return pair<Node*,int>(cur,i);
				}
			}
			parent = cur;
			cur = cur->_subs[i];
		}
		//curΪNULL��û���ҵ�������parent,����֮��Ĳ���
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
				//ָ���ӽ���ָ��Ҳ����ƶ�
				node->_subs[i + 2] = node->_subs[i + 1];
			}
			else
			{
				break;
			}
			--i;
		}
		//������
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
		//�жϵ�ǰҪ����Ľ���Ƿ��Ѿ����ڣ�������ڣ����ɲ���
		pair<Node*,int> ret = Find(key);
		if(ret.second != -1)//�ҵ����
		{
			return false;
		}

		Node* cur = ret.first;
		Node* sub = NULL;
		K newKey = key;
		while(1)
		{
			//������
			InsertKey(cur,newKey,sub);
			if(cur->_size < M)//û����
				return true;

			//����������з���
			//����key�Լ����ӽ��
			int mid = cur->_size / 2;
			Node* tmp = new Node;  //�����µĽ�㣬�洢���Ѻ���ұ�����
			int j = 0;
			int i = 0;
			for(i = mid+1; i < cur->_size; ++i,++j)
			{
				tmp->_keys[j] = cur->_keys[i];//�����ؼ���
				tmp->_subs[j] = cur->_subs[i];//����Ҷ�ӽ��
				//���Ӹ��ڵ�
				if(tmp->_subs[j])
					tmp->_subs[j]->_parent = tmp;
				//�����ߵ�Ԫ�ص�λ����ΪĬ��ֵ
				cur->_keys[i] = K();
				cur->_subs[i] = NULL;
				++tmp->_size;
			}
			tmp->_subs[j] = cur->_subs[i];//���������һ��Ҷ�ӽ��
			if(tmp->_subs[i])
				tmp->_subs[i]->_parent = NULL;
			cur->_subs[i] = NULL;

			newKey = cur->_keys[mid];
			cur->_keys[mid] = K();
			sub = tmp;
			cur->_size = mid;


			if(cur->_parent == NULL)//cur�Ǹ��ڵ�
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