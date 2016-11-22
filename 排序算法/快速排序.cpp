//������������ְ취
//����ָ�뷨
int PartSort1(int* a,int begin,int end)
{
	int midNumIndex = GetMidNum(a,begin,end);
	if(end != midNumIndex)
		swap(a[end],a[midNumIndex]);
	int key = a[end];
	int left = begin;
	int right = end;
	
	while(left < right)
	{
		while(left < right && a[left] <= key)//������Ҵ���key��ֵ
		{
			++left;
		}
		while(left < right && a[right] >= key)//���ұ���С��key��ֵ
		{
			--right;
		}
		swap(a[left],a[right]);
	}
	//���leftһֱû���ҵ�����key��ֵ����ͣ��end��ǰһ��λ�ã���ʱ������Ҫ����
	if(a[left] > a[end])
		swap(a[left],a[end]);
	return left;
}
//�ڿӷ�
int PartSort2(int* a,int begin,int end)
{
	int midNumIndex = GetMidNum(a,begin,end);
	if(end != midNumIndex)
		swap(a[end],a[midNumIndex]);
	int key = a[end];
	int left = begin;
	int right = end;
	while(left < right)
	{
		while(left < right && a[left] <= key)
		{
			++left;
		}
		a[right] = a[left];//���ҵ���ֵ�Ԥ���Ŀ�
		while(left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}
//ǰ��ָ�뷨
int PartSort3(int* a,int begin,int end)
{
	int midNumIndex = GetMidNum(a,begin,end);
	if(end != midNumIndex)
		swap(a[end],a[midNumIndex]);
	int key = a[end];
	int prev = begin - 1;
	int cur = begin;
	while(cur < end)
	{
		if(a[cur] < key && ++prev != cur)//prevָ�����key��ֵ
		{
			swap(a[prev],a[cur]);
		}
		++cur;
	}
	swap(a[++prev],a[end]);
	return prev;
}


//����������Ż�����
//����ȡ�з�
int GetMidNum(int* a,int begin,int end)
{
	int mid = begin + (end - begin)/2;
	//�ҳ�3�����д����м�λ�õ���

	// a[begin] > a[mid]
	if(a[begin] > a[mid])
	{
		if(a[mid] > a[end])//a[begin] > a[mid] > a[end]
			return mid;
		//a[begin] > a[mid] < a[end]
		else if(a[begin] > a[end])//a[begin] > a[end] > a[mid]
			return end;
		else  //  a[end] > a[begin]> a[mid]
			return begin;
	}
	//a[mid]> a[begin]
	else
	{
		if(a[begin] > a[end])//a[mid]> a[begin]> a[end]
			return begin;
		//a[mid]> a[begin]< a[end]
		else if(a[mid] > a[end])//a[mid] > a[end]> a[begin]
			return end;
		else     //a[end] > a[mid] > a[begin]
			return mid;

	}
}

//����һ��汾
void QuickSort(int* a,int begin,int end)
{
	if(begin < end)
	{
		int key = PartSort3(a,begin,end);
		QuickSort(a,begin,key-1);
		QuickSort(a,key + 1,end);
	}
}

//�����Ż��汾
//�������Сʱ���ò�������
void QuickSortOP(int* a,int begin,int end)
{
	//���ڵݹ�̫��ᵼ��ջ�����Ч�ʵͣ����ԣ�������Ƚ�Сʱ���ò�������
	if(end - begin > 13)
	{
		int key = PartSort3(a,begin,end);
		QuickSort(a,begin,key-1);
		QuickSort(a,key + 1,end);
	}
	else
		InsertSort(a+begin,end-begin + 1);
}

//���ŷǵݹ�
void QuickSortNonR(int* a,int begin,int end)
{
	stack<int> s;

	if(begin < end)
	{//�Ƚ�����β�Ž�ջ��
		s.push(end);
		s.push(begin);
		while(!s.empty())
		{
			int low = s.top();
			s.pop();
			int high = s.top();
			s.pop();
			int mid = PartSort1(a, low, high);
           if(low < mid-1)
			{
				 s.push(mid-1);
                s.push(low);
          
            }
           if(mid+1 < high)
			{
				 s.push(high);
                s.push(mid+1);
           }
		}
	}
}
