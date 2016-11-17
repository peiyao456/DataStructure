void InsertSort(vector<int>& v)
{
	if(v.size() == 0 || v.size() == 1)
		return;
	for(size_t i = 1; i < v.size(); ++i)
	{
		int tmp = v[i];
		int  j = i - 1;
		while(j >= 0 && tmp <= v[j])
		{
			v[j + 1] = v[j];
			--j;
		}
		v[j + 1] = tmp;
	}
}
