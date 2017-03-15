#include<iostream>
using namespace std;
#include<string>
//LZW压缩和解压缩
typedef struct Dict
{
	string _s;
	int _code;
}Dict;
class Compress
{
public:
	Compress(int maxSize,string text)
	{
		_maxSize = maxSize;
		_code = new int[maxSize];
		_size = 0;
		_text = text;
		_dict = new Dict[_maxSize];
		_dictSize = 0;
		//过滤0号位置
		Insert("#");
		//向字典中插入26个字母
		string s = "A";
		for (int i = 0; i < 26; ++i)
		{
			Insert(s);
			s[0]++;
		}
	}
	~Compress()
	{
		delete[] _code;
		delete[] _dict;
		_code = NULL;
		_dict = NULL;
		_maxSize = 0;
		_size = 0;
	}
	string Encode()
	{
		string s;//存储压缩后的字符串
		string cur;
		char next;
		int i = 0;
		while (i < _text.size())
		{
			cur.insert(cur.size(),1, _text[i]);
			i++;
			next = _text[i];
			while (FindCode(cur) != -1)//当前串在字典中
			{	
				cur.insert(cur.size(), 1, next);
				++i;
				if (i != _text.size())
					next = _text[i];
				else
					break;
			}
			if (i != _text.size())
			{
				char c = cur.at(cur.size() - 1);
				cur.erase(cur.end()-1);
				_code[_size] = FindCode(cur);
				++_size;
				cur += c;
				c =  _code[_size-1];
				s.push_back(c);
				Insert(cur);
			}		
			if(i == _text.size() && FindCode(cur) != -1)
			{
				_code[_size] = FindCode(cur);
				s.push_back(_code[_size]);
				break;
			}		
			--i;
			cur.clear();
		}
		return s;
	}
	string Decode(const string& s)
	{
		string text;
		string cur;
		if (s.size() <= 0)
			return s;
		int code; 
		for (int i = 0; i < s.size(); ++i)
		{
			code = (int)(s[i]);
			cur = FindSeq(code);
			text += cur;
		}
		return text;
	}
	void PrintDict()
	{
		cout<<"seq  code"<<endl;
		for (int i = 0; i < _dictSize; ++i)
		{
			cout << _dict[i]._s << "     " << _dict[i]._code<<endl;
		}
	}
protected:
	int FindCode(const string& s)
	{
		for (int i = 0; i < _dictSize; ++i)
		{
			if (s == _dict[i]._s)
				return i;
		}
		return -1;
	}
	string FindSeq(int code)
	{
		return _dict[code]._s;
	}
	void Insert(string seq)
	{
		_dict[_dictSize]._s = seq;
		_dict[_dictSize]._code = _dictSize;
		_dictSize++;
	}
private:
	Dict* _dict;
	int _dictSize;

	int* _code;
	int _size;
	int _maxSize;
	string _text;
};
int main()
{
	string text;
	cin >> text;
	Compress c(100,text);
	//c.PrintDict();
	string s = c.Encode();
	//c.PrintDict();
	//cout << s;
	cout << "解压结果是：";
	cout<<c.Decode(s)<<endl;
	system("pause");
	return 0;
}