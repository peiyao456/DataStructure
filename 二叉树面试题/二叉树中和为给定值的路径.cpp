//找和为某一值的路径
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
class FindPath
{
	typedef TreeNode<T> Node;
public:
	FindPath()
		:_root(NULL)
		,_sum(0)
	{}
	FindPath(T* a,size_t size,const T& invalid,int sum)
	{
		size_t index = 0;
		_sum = sum;
		_root = _Create(a,size,index,invalid);
	}
	void Path()
	{
		if(_root == NULL)
			return;
		vector<int> path;
		int currentSum = 0;
		_Path(_root,currentSum,path);
	}
	//练习二叉树的后序非递归
	void PostOrder()
	{
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			//
			Node* top = s.top();
			if(top->_right == NULL || prev == top->_right)
			{
				cout<<top->_data<<" ";
				prev = top;
				s.pop();
			}
			else
				cur = top->_right;
		}

		cout<<endl;
	}
protected:
	void _Path(Node* root,int currentSum,vector<int>& path)
	{
		currentSum += root->_data;
		path.push_back(root->_data);

		//如果是叶子结点，并且currentSum等于sum
		if(currentSum == _sum && root->_left == NULL && root->_right == NULL)
		{
			//打印路径
			vector<int>::iterator it = path.begin();
			while(it != path.end())
			{
				cout<<*it<<" ";
				++it;
			}
			cout<<endl;
		}

		if(root->_left != NULL)
		{
			_Path(root->_left,currentSum,path);
		}
		if(root->_right != NULL)
		{
			_Path(root->_right,currentSum,path);
		}
		//叶子结点返回到父节点
		path.pop_back();
	}
	Node* _Create(T* a, size_t size,size_t& index,const T& invalid)
	{
		assert(a);
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
	int _sum;//
};

void TestFindPath()
{
	int array[] = {8,7,5,'#','#','#',12,11,'#','#',18};
	FindPath<int> fp(array,11,'#',38);
	fp.Path();
	fp.PostOrder();
}