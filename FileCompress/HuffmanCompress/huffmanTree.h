template <class T>
struct HuffmanNode
{
	HuffmanNode<T>*_left;
	HuffmanNode<T>*_right;
	T _weight;

	HuffmanNode(const T&weight)
		:_left(NULL)
		, _right(NULL)
		, _weight(weight)
	{}

};

template <class T>
class HuffmanTree
{
	typedef HuffmanNode<T> Node;
public:
	HuffmanTree(const T*a, size_t size, const T& invalid)
		//invalid代表非法值，若为非法值，则不构建哈夫曼树
	{
		_root = CreateTree(a, size, invalid);
	}

	Node* GetRootNode()
	{
		return _root;
	}
protected:
	Node* CreateTree(const T*a, size_t size, const T& invalid)
	{
		struct Compare
		{
			bool operator()(const Node*l, const Node*r)
			{
				return (l->_weight < r->_weight);
			}
		};
		Heap <Node*, Compare> minHeap;
		for (size_t i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}
		//小堆的top结点的权值必是最小的，每次选出小堆的top构造哈夫曼树的结点
		while (minHeap.size()>1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();
			Node* parent = new Node(left->_weight + right->_weight);
			//哈夫曼树特点，父结点是两个子结点和
			parent->_left = left;
			parent->_right = right;
			minHeap.Push(parent);

		}
		return minHeap.Top();
	}
protected:
	HuffmanNode<T>* _root;
};