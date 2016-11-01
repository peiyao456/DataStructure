#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<string>

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

	Status _status;//保存某个位置的状态
	KVNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_status(EMPTY)
	{}
};
template<typename K,typename V>
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


	void Swap(HashTable<K,V> ht)
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
			if(_tables[index]._key == key)//要插入的值在原表中已经存在
			{
				return false;
			}

			++index;

			if(index == _tables.size())
			{
				index = 0;
			}
		}

		//找到合适的位置
		_tables[index]._key = key;
		_tables[index]._value = value;
		_tables[index]._status = EXIST;//将状态改为存在
		++_size;
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
			if(index == begin)//已经遍历一圈
			{
				return false;
			}
		}
	}
protected:
	void _CheckCapacity()
	{
		if(_size*10 / _tables.size() >= 8)//保证查找效率
		{
			int newSize = _GetNewSize(_tables.size());
			HashTable<K,V> hash;
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
		return key % _tables.size();
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

void TestHashTable()
{
	HashTable<int,int>  ht1;
	int array1[] = {89,18,8,58,2,3,4,9,0};
	for(int i = 0; i < sizeof(array1)/sizeof(array1[0]); ++i)
	{
		ht1.Insert(array1[i],0);
	}
	ht1.Remove(8,0);
	ht1.Remove(1,0);
	

}