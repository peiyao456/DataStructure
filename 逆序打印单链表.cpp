//链表的定义部分（只给出定义，没有包含头文件，也没有给出函数的实现）
template <typename T>
struct Node
{
	T _data;
	struct Node* next;
	struct Node* prev;
};

template <typename T>
class LinkList
{
public:
	LinkList();
	~LinkList();
	void PushBack(const T& d);
public:
	struct Node<T>* _head;
	struct Node<T>* _tail;
};
//递归实现
template <typename T>
void Print(Node<T>* head)
{
	Node<int> *cur = head;
	if (head == NULL)
	{
		return;
	}
	else
	{
		Print(cur->next);
		cout << cur->_data << " ";
	}
}
//非递归实现
template <typename T>
void Print(Node<T>* head)
{
	Node<int> *cur = head;
	stack<int> s;
	while (cur)
	{
		s.push(cur->_data);
		cur = cur->next;
	}
	while (!s.empty())
	{
		cout << s.top()<<" ";
		s.pop();
	}
}
//测试代码
void test()
{
	LinkList <int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	Print(l1._head);
}