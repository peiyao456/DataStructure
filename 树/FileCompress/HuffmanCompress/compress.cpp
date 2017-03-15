#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <cassert>
#include <string>

#include <cassert> 
#include <time.h>
#include"heap.h"
#include"huffmanTree.h"




typedef unsigned long long  LongType;
struct CharInfo
{
	unsigned char _ch;  //�ַ�
	LongType _count;   //���ִ���
	string _code;      //Huffman code


	CharInfo()
		:_ch(0)
		, _count(0)
	{}

	CharInfo(LongType count)
		:_ch(0)
		, _count(count)
	{}

	bool operator!=(const CharInfo&info) const
	{
		return _count != info._count;
	}

	CharInfo operator+(const CharInfo&info) const
	{
		return CharInfo(_count + info._count);
	}

	bool operator<(const CharInfo&info) const
	{
		return _count < info._count;
	}


};
template <class T>
class FileCompress
{
	typedef HuffmanNode<T> Node;
public:
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
			_infos[i]._count = 0;
		}

	}
public:
	void Compress(const char* filename)
	{
		assert(filename);

		//ͳ���ļ����ַ����ֵĴ���
		FILE* fout = fopen(filename, "rb");
		assert(fout);
		char ch = fgetc(fout);
		while (!feof(fout))
		{
			_infos[(unsigned char)ch]._count++;
			ch = fgetc(fout);
		}

		//������������
		CharInfo invalid(0);
		HuffmanTree<CharInfo>tree(_infos, 256, invalid);

		//���ɹ���������
		string code;
		GenerateHuffmanCode(tree.GetRootNode(), code);

		//��ȡԴ�ļ��ַ�ѹ����������������д����Ӧ��λ
		string Compressfilename = filename;
		Compressfilename += ".compress";
		FILE* fin = fopen(Compressfilename.c_str(), "wb");      //�ö����ƶ�д�ļ�
		fseek(fout, 0, SEEK_SET);                             //��λ���ļ���ʼλ��
		ch = fgetc(fout);
		char value = 0;
		int pos = 0;
		while (!feof(fout))
		{
			string& code = _infos[(unsigned char)ch]._code;
			//ע��codeҪΪ����
			for (size_t i = 0; i < code.size(); ++i)
				//����λ�洢���������룬�����ڴ�
			{
				value <<= 1;
				if (code[i] == '1')
				{
					value |= 1;
				}
				if (++pos == 8)
					/*
					��8λ��1�ֽڣ���������������д����Ӧ���ļ���
					Ȼ�������ȡ����ַ��ĺ�������
					*/
				{
					fputc(value, fin);
					value = 0;
					pos = 0;
				}
			}
			ch = fgetc(fout);     /*������ȡ��һ���ַ��Ĺ���������*/
		}
		if (pos != 0)
		{
			value <<= (8 - pos);
			fputc(value, fin);
		}

		/*/д�����ļ��������ѹ����ʱ���ؽ���������/*/
		string configfilename = filename;
		configfilename += ".config";
		FILE* finconfig = fopen(configfilename.c_str(), "wb");
		assert(finconfig);
		char buffer[128];                          /*/����д�뻺����/*/
		string str;
		for (size_t i = 0; i < 256; ++i)
		{
			if (_infos[i]._count>0)
			{
				str += _infos[i]._ch;
				str += ",";
				str += _itoa(_infos[i]._count, buffer, 10);
				/*/itoa������_countת�����ַ�����buffer�У�10Ϊ����/*/

				str += '\n';
			}
			fputs(str.c_str(), finconfig);
			str.clear();
		}
		fclose(fout);
		fclose(fin);
		fclose(finconfig);
	}




	//��ѹ��
	void UnCompress(const char* filename)
	{
		string configfilename = filename;
		configfilename += ".config";
		FILE* foutconfig = fopen(configfilename.c_str(), "rb");
		assert(foutconfig);
		string str;
		LongType charCount = 0;
		while (Readline(foutconfig, str))
		{
			if (str.empty())
			{
				str += '\n';
			}
			else
			{
				_infos[(unsigned char)str[0]]._count = atoi(str.substr(2).c_str());
				str.clear();
			}
		}


		//�ؽ���������
		CharInfo invalid(0);
		HuffmanTree<CharInfo>tree(_infos, 256, invalid);
		charCount = tree.GetRootNode()->_weight._count;

		string Compressfilename = filename;
		Compressfilename += ".compress";
		FILE* fout = fopen(Compressfilename.c_str(), "rb");
		assert(fout);

		string UnCompressfilename = filename;
		UnCompressfilename += ".uncompress";
		FILE* fin = fopen(UnCompressfilename.c_str(), "wb");
		assert(fin);
		char ch = fgetc(fout);
		HuffmanNode<CharInfo>* root = tree.GetRootNode();
		HuffmanNode<CharInfo>* cur = root;
		int pos = 7;
		while (1)
		{
			if (ch & (1 << pos))
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
			if (pos-- == 0)
			{
				pos = 7;
				ch = fgetc(fout);          //������ȡ�ַ�
			}
			if (cur->_left == NULL&&cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fin);

				if (--charCount == 0)
				{
					break;
				}
				cur = root;
			}
		}
		fclose(fin);

	}

protected:
	void GenerateHuffmanCode(HuffmanNode<CharInfo>* root, string code)
	{
		if (root == NULL)
		{
			return;
		}
		if (root->_left)
		{
			GenerateHuffmanCode(root ->_left, code + '0');
		}

		if (root->_right)
		{
			GenerateHuffmanCode(root->_right, code + '1');
		}
		if ((root->_left == NULL) && (root->_right == NULL))
		{
			_infos[root->_weight._ch]._code = code;
		}
	}
	bool Readline(FILE* fout, string& str)
	{
		char ch = fgetc(fout);
		if (feof(fout))
		{
			return false;
		}
		while (!feof(fout) && ch != '\n')
		{
			str += ch;
			ch = fgetc(fout);
		}
		return true;
	}
protected:
	CharInfo _infos[256];
};

void TestCompress()
{
	FileCompress<int> fc;
	double start_compress = clock();
//	fc.Compress("Input.BIG");
	fc.Compress("shixun.png");
//	fc.Compress("s.txt");
	//fc.Compress("video.csf");
	//fc.Compress("yicijiuhao.mp3");
	double finish_compress = clock();
	//fc.UnCompress("Input.BIG");
	fc.UnCompress("shixun.png");
	//fc.UnCompress("s.txt");
	//fc.UnCompress("video.csf");
	//fc.UnCompress("yicijiuhao.mp3");
	double finish_uncompress = clock();
	cout << "ѹ��ʱ���ǣ�" << finish_compress - start_compress << "ms" << endl;
	cout << "��ѹ��ʱ���ǣ�" << finish_uncompress - finish_compress << "ms" << endl;
}

int main()
{
	TestCompress();
	system("pause");
	return 0;
}
