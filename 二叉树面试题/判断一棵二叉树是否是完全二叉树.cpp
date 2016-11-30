#pragma once
#include<iostream>
using namespace std;
#include<queue>
#include<list>
#include<vector>
template<typename T>
struct TreeNode
{
	T _data;
	TreeNode* _left;
	TreeNode* _right;
	TreeNode(const T& x = T())
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
	BinaryTree()
		:_root(NULL)
	{}
	BinaryTree(T* a,size_t size,const T& invalid)
	{
		size_t index = 0;
		_root = _Create(a,size,index,invalid);
	}
	bool Find(const T& x)
	{
		if(_root == NULL)
			return false;
		Node* cur = _root;
		while(cur)
		{
			if(cur->_data > x)
				cur = cur->_left;
			else if(cur->_data < x)
				cur = cur->_right;
			else
				return true;
		}
	}
protected:
	Node* _Create(T* a, size_t size,size_t& index,const T& invalid)
	{
		//assert(a);
		Node* root = NULL;
		while (index < size && a[index] != invalid)
		{
		    root = new Node(a[index]);
			root->_left = _Create(a,size,++index,invalid);
			root->_right = _Create(a,size, ++index,invalid);
		}
		return root;
	}
public:
	Node* _root;
};

template<typename T>
class IsCompleteBinaryTree
{
	typedef TreeNode<T> Node;
public:
	IsCompleteBinaryTree(T* array,size_t size,const T& invalid)
		:_bt(array,size,invalid)
	{}
	
	bool _IsComplete_1()
    {
        if(_bt._root == NULL)
            return false;
        queue<Node*> q;
        q.push(_bt._root);
        bool result = true;
        bool IsNul = false;//出现一个叶子结点，后边的结点必须都是叶子结点
        while(!q.empty())
        {
            Node* pNode = q.front();
            q.pop();
            if(IsNul)
            {
                //只有pNode是叶子结点，这棵树才是完全二叉树；否则不是
                if(pNode->_left != NULL || pNode->_right != NULL)
                {
                    result = false;
                    break;
                }
            }
            else
            {
                if(pNode->_left != NULL && pNode->_right != NULL)
                {
                    q.push(pNode->_left);
                    q.push(pNode->_right);
                }
                else if(pNode->_left != NULL && pNode->_right == NULL)
                {
                    q.push(pNode->_left);
                    IsNul = true;
                }
                else if(pNode->_left == NULL && pNode->_right != NULL)
                {
                    result = false;//说明这棵树不是完全二叉树
                    break;
                }
                else
                {
                    IsNul = true;
                }
            }
        }
        return result;
    }
    bool _IsComplete_2()
    {
        if(_bt._root == NULL)
            return false;
        queue<Node*> q;
        q.push(_bt._root);
        while(!q.empty())
        {
            Node* top = q.front();
            if(top != NULL)
            {
                q.pop();
                q.push(top->_left);
                q.push(top->_right);
            }
            else
                break;
        }
        //计算队列中非空节点的个数
        int i = 0;
        while(i++ < q.size())
        {
            if(q.front() != NULL)
                return false;
            else
                q.pop();
        }
        return true;
    }

private:
	BinaryTree<T> _bt;
};


void TestIsCompleteBinaryTree()
{
	//int array[] = {3,4,6,'#','#',7,'#','#',5,8,'#','#'};
	int array[] = {5,6,9,'#','#','#',7,12,13};
	IsCompleteBinaryTree<int> bt(array,9,'#');
	cout<<bt._IsComplete_1()<<endl;
	cout<<bt._IsComplete_2()<<endl;
}