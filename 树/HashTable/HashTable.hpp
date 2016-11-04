#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>

//���ŵ�ַ��
namespace Open
{
	enum Status
	{
		EMPTY,
		EXIST,
		DELETE
	};


	template<typename K,typename V>
	struct KVNode
	{
		K _key;
		V _value;

		Status _status;//����ĳ��λ�õ�״̬
		KVNode(const K& key = K(),const V& value = V())
			:_key(key)
			,_value(value)
			,_status(EMPTY)
		{}
	};
	template<typename K>
	struct __GetK
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	struct __GetStrK
	{
		static size_t BKDRHash(const char* str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while(*str)
			{
				hash = hash * seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator()(const string& str)
		{
			return BKDRHash(str.c_str());
		}
	};

	template<typename K,typename V,typename GetK = __GetK<K>>
	class HashTable
	{
		typedef KVNode<K,V> Node;

	public:
		HashTable()
			:_size(0)
		{
			_tables.resize(2);
		}

		~HashTable()
		{}


		void Swap(HashTable<K,V,GetK> ht)
		{
			swap(_size,ht._size);
			swap(_tables,ht._tables);
		}

		bool Insert(const K& key,const V& value)
		{
			_CheckCapacity();
			int index = _GetIndex(key,value);
			
			while(_tables[index]._status == EXIST)
			{
				if(_tables[index]._key == key)//Ҫ�����ֵ��ԭ�����Ѿ�����
				{
					return false;
				}

				++index;

				if(index == _tables.size())
				{
					index = 0;
				}
			}

			//�ҵ����ʵ�λ��
			_tables[index]._key = key;
			_tables[index]._value = value;
			_tables[index]._status = EXIST;//��״̬��Ϊ����
			++_size;
		}

		Node* Find(const K& key,const V& value)
		{
			int index = _GetIndex(key,value);
			int begin = index;
			while(_tables[index]._key != key)
			{
				++index;
				if(index == _tables.size())
				{
					index = 0;
				}
				if(index == begin)
				{
					return NULL;
				}
			}
			//�п�����Ҫɾ�����Ѿ����ڵ�Ԫ��
			if(_tables[index]._status == EXIST)
			{
				return &_tables[index];
			}
			else
				return NULL;
		}

		bool Remove(const K& key,const V& value)
		{
			if(_size == 0)
				return false;
			int index = _GetIndex(key,value);
			int begin = index;
			while(_tables[index]._status != EMPTY)
			{
				if(_tables[index]._key == key && _tables[index]._status == EXIST)
				{
					_tables[index]._status = DELETE;
					--_size;
					return true;
				}

				++index;
				if(index == _tables.size())
				{
					index = 0;
				}
				if(index == begin)//�Ѿ�����һȦ
				{
					return false;
				}
			}
		}
	protected:
		void _CheckCapacity()
		{
			if(_size*10 / _tables.size() >= 8)//��֤����Ч��
			{
				int newSize = _GetNewSize(_tables.size());
				HashTable<K,V,GetK> hash;
				hash._tables.resize(newSize);
				for(size_t i = 0; i < _size; ++i)
				{
					if(_tables[i]._status == EXIST)
					{
						hash.Insert(_tables[i]._key,_tables[i]._value);
					}
				}
				this->Swap(hash);
			}
			else
				return;
		}

		int _GetIndex(const K& key,const V& value)
		{
			GetK getK;
			return getK(key) % _tables.size();
		}
		int _GetNewSize(int num)
		{
			const int _PrimeSize= 28;
			static const unsigned long _PrimeList[_PrimeSize] = {
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,1610612741ul, 3221225473ul, 4294967291ul
			};
			for(int i = 0; i < _PrimeSize; ++i)
			{
				if(_PrimeList[i] > num)
					return _PrimeList[i];
			}
		}
	protected:
		vector<Node> _tables;
		size_t _size;
	};
}


void TestHashTableOpen()
{
	Open::HashTable<int,int>  ht1;//ģ�����3�ǲ���ȱʡ�Ĳ���
	int array1[] = {89,18,8,58,2,3,4,9,0};
	for(int i = 0; i < sizeof(array1)/sizeof(array1[0]); ++i)
	{
		ht1.Insert(array1[i],0);
	}
	ht1.Remove(8,0);
	ht1.Remove(1,0);
	
	Open::HashTable<string,int,Open::__GetStrK> ht2;
	char* array2[] = {"hello","world","sort","find","sort"};
	for(int i = 0; i < sizeof(array2)/sizeof(array2[0]); ++i)
	{
		Open::KVNode<string,int>* node = ht2.Find(array2[i],0);
		if(node)//����Ѿ�����
		{
			node->_value++;
		}
		else
		{
			ht2.Insert(array2[i],0);
		}
	}
}


//������
namespace Link
{
	template<typename K,typename V>
	struct KVNode
	{
		K _key;
		V _value;
		KVNode<K,V>* _next;

		KVNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_next(NULL)
		{}
	};

	template<typename K>
	struct __GetK
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};

	template<>
	struct __GetK<string>
	{
		static size_t BKDRHash(const char* str)
		{
			unsigned int seed = 131;// 31 131 1313 13131 131313
			unsigned int hash = 0;
			while(*str)
			{
				hash = hash * seed + (*str++);
			}
			return(hash & 0x7FFFFFFF);
		}
		size_t operator()(const string& str)
		{
			return BKDRHash(str.c_str());
		}
	};

	template<typename K,typename V,typename GetK = __GetK<K>>
	class HashTable
	{
		typedef KVNode<K,V> Node;
	public:
		HashTable()
			:_size(0)
		{
			_tables.resize(2);//��ʼ������2���ռ�
		}

		bool Insert(const K& key,const V& value)
		{
			//�������
			_CheckCapacity();
			int index = _GetIndex(key);
			//�Ȳ��ң���Ҫ�����Ԫ���Ƿ��Ѿ�����
			if(Find(key))
			{
				return false;
			}
			//����Ԫ�ط��������
			//1.����Ľ���ǵ�һ�����
			//2.����Ľ�㲻�ǵ�һ�����
			Node* newNode = new Node(key,value);
			newNode->_next = _tables[index];
			_tables[index] = newNode;
			++_size;
		}

		Node* Find(const K& key)
		{
			int index = _GetIndex(key);
			Node* cur = _tables[index];
			while(cur)
			{
				if(cur->_key == key)
					return cur;
				cur = cur->_next;
			}
			return NULL;
		}

		bool Remove(const K& key)
		{
			int index = _GetIndex(key);
			//ɾ����3�����
			//1.ɾ����һ���ڵ�
			//2.ɾ���м���
			//3.ɾ�����һ�����
			Node* cur = _tables[index];
			//��¼Ҫɾ��������һ�����
			Node* prev = NULL;
			while(cur)
			{
				if(cur->_key == key)//�ҵ�Ҫɾ���Ľ��
				{
					if(prev == NULL)//Ҫɾ���ľ��ǵ�һ�����
					{
						_tables[index] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}
					delete cur;
					--_size;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

	protected:
		int _GetIndex(const K& key)
		{
			GetK getK;
			return getK(key) % _tables.size();
		}

		void _CheckCapacity()
		{
			if(_size == _tables.size())
			{
				int newSize = _GetNewSize(_size);//��������
				HashTable<K,V,GetK> tmp;
				tmp._tables.resize(newSize);
				vector<K> v;
				Node* del = NULL;

				//������Ԫ�طŽ�vector��
				for(size_t i = 0; i < _size; ++i)
				{
					//�ҵ��д洢Ԫ�ص���
					if(_tables[i] != NULL)
					{
						Node* cur = _tables[i];
						while(cur)
						{
						    //cur = _tables[i];
							v.push_back(cur->_key);
							cur = cur->_next;
						}

						//����ռ�
						cur = _tables[i];
						while(cur)
						{
							del = cur;
							cur = cur->_next;
							delete del;
						}
					}
					else
						continue;
				}
				//��vector�е�����Ԫ�����²���
				for(size_t i = 0 ; i < v.size(); ++i)
				{
					tmp.Insert(v[i],0);
					//v.pop_back();
				}
				//�Ѿ��ƶ����
				this->_Swap(tmp);
			}
		}
		
		int _GetNewSize(int num)
		{
			const int _PrimeSize= 28;
			static const unsigned long _PrimeList[_PrimeSize] = {
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,1610612741ul, 3221225473ul, 4294967291ul
			};
			for(int i = 0; i < _PrimeSize; ++i)
			{
				if(_PrimeList[i] > num)
					return _PrimeList[i];
			}
		}

		void _Swap(HashTable<K,V,GetK> ht)
		{
			swap(ht._tables,_tables);
			swap(ht._size,_size);
		}

	protected:
		vector<Node* > _tables;
		size_t _size;
	};
	
}
void TestHashTableLink()
{
	Link::HashTable<int,int>  ht1;
	int array1[] = {89,21,8,58,53,12,3,4,9,0};
	for(int i = 0; i < sizeof(array1)/sizeof(array1[0]); ++i)
	{
		ht1.Insert(array1[i],0);
	}
	ht1.Remove(4);
	ht1.Remove(12);
	
	Link::HashTable<string,int> ht2;
	char* array2[] = {"hello","yang","hello","sort","wang","zip","huffman"};
	for(int i = 0; i < sizeof(array2)/sizeof(array2[0]); ++i)
	{
		Link::KVNode<string,int>* ret = ht2.Find(array2[i]);
		if(!ret)
			ht2.Insert(array2[i],0);
	}
	ht2.Remove("hello");
	ht2.Remove("sort");
}