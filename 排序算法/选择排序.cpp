void SelectSortOP(vector<int>& a)
{
	int left = 0;
	int right = a.size() - 1;
	int min = left;//�洢��Сֵ���±�
	int max = left;//�洢���ֵ���±�
	while(left <= right)
	{
		min = left;
		max = left;
		for(int i = left; i <= right; ++i)
		{
			if(a[i] < a[min])
			{
				min = i;
			}
			if(a[i] > a[max])
			{
				max = i;
			}
		}
		swap(a[left],a[min]);
		if(left == max)
			max = min;
		swap(a[right],a[max]);

		++left;
		--right;
	}
}

void SelectSort(vector<int>& v)
{
	for(int i = 0; i < v.size() - 2; ++i)
	{
		int k = i;
		for(int j = i + 1; j < v.size() - 1; ++j)
		{
			//�ҵ���С�������±�
			if(v[j] < v[k])
				k = j;
		}
		if(k != i)
		{
			swap(v[k],v[i]);
		}
	}
}