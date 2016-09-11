//����Ķ��岿�֣�ֻ�������壬û�а���ͷ�ļ���Ҳû�и���������ʵ�֣�
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
//�ݹ�ʵ��
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
//�ǵݹ�ʵ��
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
//���Դ���
void test()
{
	LinkList <int> l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	Print(l1._head);
}