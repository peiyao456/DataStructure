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
		//дfileName�ļ�
		FILE* pWrite = fopen(fileName.c_str(),"w");
		assert(pWrite);
		srand( (unsigned)time( NULL )); 
		//���ֵ������������д���ļ�
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
	
	void _Divide()//��ȡҪ������ļ����ֳ�10��С�ļ�
	{
		vector<int> v;//���ÿ��С�ļ�������
		FILE* pRead = fopen(_fileName.c_str(),"r");
		assert(pRead);
		int count = 1;
		char fileName[] = "0.txt";
		while(count <= 10)
		{
			v.clear();
			//��Ҫ������ļ��ж�ȡ10��֮һ�����ݣ�д��v�У����ڴ��н�������
			for(int i = 0; i < _size/10 && !feof(pRead); ++i)
			{
				int tmp;
				fscanf(pRead,"%d",&tmp);
				if(tmp == '\n')
					fscanf(pRead,"%d",&tmp);
				v.push_back(tmp);
			}
			sort(v.begin(),v.end());
			//������õ�����д��һ��С���ļ���
			
			FILE* pWrite = fopen(fileName,"w");
			assert(pWrite);
			//���ļ���д���ļ���������
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
			//���ļ����������ж�ȡ�����ļ����кϲ�
			string file1 = _smallFileName.front();
			_smallFileName.pop();
			string file2 = _smallFileName.front();
			_smallFileName.pop();
			
			//���ϲ����ļ���д���ļ�������
			
			FILE* pMergeFile = fopen(filename,"w");
			assert(pMergeFile);
			_smallFileName.push(filename);

			filename[0]++;

			//�������ļ��������ж�����
			FILE* pRead1 = fopen(file1.c_str(),"r");
			assert(pRead1);
			FILE* pRead2 = fopen(file2.c_str(),"r");
			assert(pRead2);

			//���кϲ�
			int tmp1 = 0;
			int tmp2 = 0;
			fscanf(pRead1,"%d",&tmp1);
			fscanf(pRead2,"%d",&tmp2);

			while(!feof(pRead1) && !feof(pRead2))
			{
				while(!feof(pRead1) && !feof(pRead2) && tmp1 <= tmp2)//��tmp1д���ϲ��ļ�����������ȡ�ļ�1
				{
					fprintf(pMergeFile,"%d",tmp1);
					fprintf(pMergeFile,"%c",'\n');
					fscanf(pRead1,"%d",&tmp1);
				}

				while(!feof(pRead1) && !feof(pRead2) && tmp2 <= tmp1)//��tmp2д���ϲ��ļ�����������ȡ�ļ�2
				{
					fprintf(pMergeFile,"%d",tmp2);
					fprintf(pMergeFile,"%c",'\n');
					fscanf(pRead2,"%d",&tmp2);
				}
			}
			//��һ���ļ��Ѿ���ȡ���
			while(!feof(pRead1))
			{
				fprintf(pMergeFile,"%d",tmp1);
				fprintf(pMergeFile,"%c",'\n');
				fscanf(pRead1,"%d",&tmp1);
			}

			while(!feof(pRead2))
			{
				//���ϴζ���������д���ļ�
				fprintf(pMergeFile,"%d",tmp2);
				fprintf(pMergeFile,"%c",'\n');
				fscanf(pRead2,"%d",&tmp2);
			}

			//�ر��ļ�
			fclose(pRead1);
			fclose(pRead2);
			fclose(pMergeFile);
			//ɾ���ļ�
			remove(file1.c_str());
			remove(file2.c_str());
		}
	}
private:
	string _fileName;
	size_t _size;//Ҫ�������������
	queue<string> _smallFileName;
};

void Test()
{
	BigDataSort s("sort.txt",1000000);
	s.Sort();
}