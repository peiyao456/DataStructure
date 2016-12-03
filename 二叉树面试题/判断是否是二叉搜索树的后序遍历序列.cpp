//�жϸ��������Ƿ���BST�ĺ�������
template<typename T>
class PostOrder
{
public:
	PostOrder(int a[],int n)
		:_size(n)
	{
		_a = new T[_size];
		for(int i = 0; i < n; ++i)
		{
			_a[i] = a[i];
		}
	}

	bool IsCurrentPostOrder()
	{
		return _IsCurrentPostOrder(_a,_size);
	}
protected:
	bool _IsCurrentPostOrder(int a[],int len)
	{
		if( a == NULL ||len <= 0)
			return false;

		//��������зֶ�
		int i = 0;
		for(i = 0; i < len - 1; ++i)
		{
			if(a[i] > a[len - 1])
				break;//�ҵ��ָ��
		}

		for(int j = i; j < len - 1 ; ++j)
		{
			if(a[j] < a[len - 1])//����С�ڸ��ڵ��ֵ��˵�����ǺϷ��������У�����
				return false;
		}

		bool left = true;
		if(i > 0)
			left = _IsCurrentPostOrder(a,i);

		bool right = true;
		if(i < len - 1)
			right = _IsCurrentPostOrder(a+i,len-i-1);

		return left && right;
	}
private:
	T* _a;
	int _size;
};

void TestPostOrder()
{
	//int a[] = {3,7,6,11,12,8};
	int a[] = {7,4,6,5};
	PostOrder<int> p(a,4);
	cout<<p.IsCurrentPostOrder()<<endl;
}