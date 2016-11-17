void AdjustDowm(vector<int>& v,int parent,int len)
{
	int child = parent * 2 + 1;
	while(child < len)
	{
		if(child + 1 < len && v[child] < v[child + 1])
			++child;
		if(v[parent] < v[child])
		{
			swap(v[child],v[parent]);
			parent = child;
			child = parent *  2 + 1;
		}
		else
			break;
	}
}
void HeapSort(vector<int>& v)
{
	if(v.size() == 0 || v.size() == 1)
		return;
	for(int i = v.size() - 2; i >= 0; --i)
	{
		AdjustDowm(v,i,v.size());
	}
	//½»»»£¬µ÷Õû
	//int size = v.size();
	for(int i = v.size() - 1; i >= 0; --i)
	{
		swap(v[0],v[i]);
		AdjustDowm(v,0,i);
	}
}
