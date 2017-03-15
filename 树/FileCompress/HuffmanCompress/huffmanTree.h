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
		//invalid����Ƿ�ֵ����Ϊ�Ƿ�ֵ���򲻹�����������
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
		//С�ѵ�top����Ȩֵ������С�ģ�ÿ��ѡ��С�ѵ�top������������Ľ��
		while (minHeap.size()>1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();
			Node* parent = new Node(left->_weight + right->_weight);
			//���������ص㣬������������ӽ���
			parent->_left = left;
			parent->_right = right;
			minHeap.Push(parent);

		}
		return minHeap.Top();
	}
protected:
	HuffmanNode<T>* _root;
};