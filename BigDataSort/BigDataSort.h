#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<string>
#include<assert.h>
#include<vector>
#include<time.h>
#include<algorithm>
#include<queue>

class BigDataSort
{
public:
	BigDataSort(string fileName,size_t size)
		:_fileName(fileName)
		,_size(size)
	{
		//写fileName文件
		FILE* pWrite = fopen(fileName.c_str(),"w");
		assert(pWrite);
		srand( (unsigned)time( NULL )); 
		//随机值函数生成数据写入文件
		for(int i = 0; i < _size; ++i)
		{
			int tmp = rand();
			fprintf(pWrite,"%d",tmp);
			fprintf(pWrite,"%c",'\n');
		}
		fclose(pWrite);
	}
	void Sort()
	{
		_Divide();
		_Merge();
	}
protected:
	
	void _Divide()//读取要排序的文件，分成10个小文件
	{
		vector<int> v;//存放每个小文件的数据
		FILE* pRead = fopen(_fileName.c_str(),"r");
		assert(pRead);
		int count = 1;
		char fileName[] = "0.txt";
		while(count <= 10)
		{
			v.clear();
			//从要排序的文件中读取10分之一的数据，写到v中，在内存中进行排序
			for(int i = 0; i < _size/10 && !feof(pRead); ++i)
			{
				int tmp;
				fscanf(pRead,"%d",&tmp);
				if(tmp == '\n')
					fscanf(pRead,"%d",&tmp);
				v.push_back(tmp);
			}
			sort(v.begin(),v.end());
			//将排序好的整数写进一个小的文件中
			
			FILE* pWrite = fopen(fileName,"w");
			assert(pWrite);
			//将文件名写进文件名的容器
			_smallFileName.push(fileName);
			fileName[0]++;


			for(int i = 0; i < v.size(); ++i)
			{
				fprintf(pWrite,"%d",v[i]);
				fprintf(pWrite,"%c",'\n');
			}
			fclose(pWrite);
			++count;
		}
		fclose(pRead);
	}


	void _Merge()
	{
		char filename[] = "a.txt";
		while(_smallFileName.size() > 1)
		{
			//从文件名的容器中读取两个文件进行合并
			string file1 = _smallFileName.front();
			_smallFileName.pop();
			string file2 = _smallFileName.front();
			_smallFileName.pop();
			
			//将合并的文件名写进文件名容器
			
			FILE* pMergeFile = fopen(filename,"w");
			assert(pMergeFile);
			_smallFileName.push(filename);

			filename[0]++;

			//打开两个文件，并进行读操作
			FILE* pRead1 = fopen(file1.c_str(),"r");
			assert(pRead1);
			FILE* pRead2 = fopen(file2.c_str(),"r");
			assert(pRead2);

			//进行合并
			int tmp1 = 0;
			int tmp2 = 0;
			fscanf(pRead1,"%d",&tmp1);
			fscanf(pRead2,"%d",&tmp2);

			while(!feof(pRead1) && !feof(pRead2))
			{
				while(!feof(pRead1) && !feof(pRead2) && tmp1 <= tmp2)//将tmp1写进合并文件，并继续读取文件1
				{
					fprintf(pMergeFile,"%d",tmp1);
					fprintf(pMergeFile,"%c",'\n');
					fscanf(pRead1,"%d",&tmp1);
				}

				while(!feof(pRead1) && !feof(pRead2) && tmp2 <= tmp1)//将tmp2写进合并文件，并继续读取文件2
				{
					fprintf(pMergeFile,"%d",tmp2);
					fprintf(pMergeFile,"%c",'\n');
					fscanf(pRead2,"%d",&tmp2);
				}
			}
			//有一个文件已经读取完毕
			while(!feof(pRead1))
			{
				fprintf(pMergeFile,"%d",tmp1);
				fprintf(pMergeFile,"%c",'\n');
				fscanf(pRead1,"%d",&tmp1);
			}

			while(!feof(pRead2))
			{
				//将上次读到的数据写进文件
				fprintf(pMergeFile,"%d",tmp2);
				fprintf(pMergeFile,"%c",'\n');
				fscanf(pRead2,"%d",&tmp2);
			}

			//关闭文件
			fclose(pRead1);
			fclose(pRead2);
			fclose(pMergeFile);
			//删除文件
			remove(file1.c_str());
			remove(file2.c_str());
		}
	}
private:
	string _fileName;
	size_t _size;//要排序的数据总数
	queue<string> _smallFileName;
};

void Test()
{
	BigDataSort s("sort.txt",1000000);
	s.Sort();
}