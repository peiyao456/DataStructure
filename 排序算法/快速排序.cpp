//单趟排序的三种办法
//左右指针法
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
		while(left < right && a[left] <= key)//在左边找大于key的值
		{
			++left;
		}
		while(left < right && a[right] >= key)//在右边找小于key的值
		{
			--right;
		}
		swap(a[left],a[right]);
	}
	//如果left一直没有找到大于key的值，会停在end的前一个位置，此时并不需要交换
	if(a[left] > a[end])
		swap(a[left],a[end]);
	return left;
}
//挖坑法
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
		a[right] = a[left];//将找到的值填到预留的坑
		while(left < right && a[right] >= key)
		{
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}
//前后指针法
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
		if(a[cur] < key && ++prev != cur)//prev指向大于key的值
		{
			swap(a[prev],a[cur]);
		}
		++cur;
	}
	swap(a[++prev],a[end]);
	return prev;
}


//单趟排序的优化方法
//三数取中法
int GetMidNum(int* a,int begin,int end)
{
	int mid = begin + (end - begin)/2;
	//找出3个数中处于中间位置的数

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

//快排一般版本
void QuickSort(int* a,int begin,int end)
{
	if(begin < end)
	{
		int key = PartSort3(a,begin,end);
		QuickSort(a,begin,key-1);
		QuickSort(a,key + 1,end);
	}
}

//快排优化版本
//如果区间小时，用插入排序
void QuickSortOP(int* a,int begin,int end)
{
	//由于递归太深会导致栈溢出，效率低，所以，当区间比较小时采用插入排序。
	if(end - begin > 13)
	{
		int key = PartSort3(a,begin,end);
		QuickSort(a,begin,key-1);
		QuickSort(a,key + 1,end);
	}
	else
		InsertSort(a+begin,end-begin + 1);
}

//快排非递归
void QuickSortNonR(int* a,int begin,int end)
{
	stack<int> s;

	if(begin < end)
	{//先将区间尾放进栈里
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
