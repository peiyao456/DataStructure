#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<queue>
#include"heap.h"
#include"UnionFindSet.h"

template<typename V,typename W>
class GraphMartix
{
public:
	GraphMartix(V* arr,size_t size,bool isDirection = false)
		:_size(size)
		,_isDirection(isDirection)
	{
		//����������
		_vertex = new V[_size];
		//�������
		_martix = new W*[_size];
		for(int i = 0; i < _size; ++i)
		{
			_martix[i] = new W[_size];
			_vertex[i] = arr[i];//�Խ����Ϣ���и�ֵ
		}
		//�Ծ�����г�ʼ�������Ը���һ���Ƿ�ֵ��Ҳ������Ĭ��ֵ
		for(int i = 0; i < _size; ++i)
		{
			for(int j = 0; j < _size; ++j)
			{
				_martix[i][j] = 0;
			}
		}
	}
	void AddEdge(const V& src,const V& dst,const W& w)
	{
		int srcIndex = _GetIndex(src);
		int dstIndex = _GetIndex(dst);

		//
		if(_isDirection)
		{
			_martix[srcIndex][dstIndex] = w;
		}
		else//����ͼ
		{
			_martix[srcIndex][dstIndex] = w;
			_martix[dstIndex][srcIndex] = w;
		}
	}
	void Display()
	{
		for(int i = 0; i < _size; ++i)
		{
			for(int j = 0; j < _size; ++j)
			{
				cout<<_martix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
protected:
	int _GetIndex(const  V& v)
	{
		for(int i = 0; i < _size; ++i)
		{
			if(_vertex[i] == v)
				return i;
		}
		throw std::invalid_argument("�����Ľ�����");
	}
private:
	V* _vertex;
	W** _martix;
	size_t _size;
	bool  _isDirection;
};

void TestGraphMartix()
{
	char array[] = {'A','B','C','D','E'};

	GraphMartix<char,int> gm(array,5);
	gm.AddEdge('A','B',8);
	gm.AddEdge('D','E',12);
	gm.AddEdge('D','C',6);

	gm.Display();
}

template<typename V,typename W>
struct GraphNode
{
	GraphNode(const size_t& src,const size_t& dst,const W& w)
		:_src(src)
		,_dst(dst)
		,_w(w)
		,_next(NULL)
	{}
	size_t _src;
	size_t _dst;
	W _w;
	GraphNode<V,W>* _next;
};

template<typename V,typename W>
class GraphLink
{
	typedef GraphNode<V,W> Node;
public:
	GraphLink(const V* arr,size_t size,bool isDirection = false)
		:_isDirection(isDirection)
	{
		_vertex.resize(size);
		_edge.resize(size);
		for(int i = 0; i < size; ++i)
		{
			_vertex[i] = arr[i];
		}
	}

	void AddEdge(const V& src,const  V& dst,const  W& w)
	{
		int srcIndex = _GetIndex(src);
		int dstIndex = _GetIndex(dst);
		if(_isDirection)
		{
			_AddEdge(srcIndex,dstIndex,w);
		}
		else
		{
			_AddEdge(srcIndex,dstIndex,w);
			_AddEdge(dstIndex,srcIndex,w);
		}
	}

	void Print()
	{
		for(int i = 0; i < _vertex.size(); ++i)
		{
			cout<<_vertex[i]<<"["<<i<<"]"<<"->";
			Node* cur = _edge[i];
			while(cur)
			{
				cout<<_vertex[cur->_dst]<<"["<<cur->_dst<<"]"<<"->";
				cur = cur->_next;
			}
			cout<<"NULL"<<endl;
		}
	}
	void DFS(const V& v)
	{
		bool visited[5] = {0};
		_DFS(v,visited);

	//�������ͨͼ�����
		for(int i = 0; i < _vertex.size(); ++i)
		{
			if(visited[i] == false)
				_DFS(_vertex[i],visited);
		}
		cout<<endl;
	}

	void BFS(const V& v)
	{
		bool visited[5] = {false};
		int index = _GetIndex(v);
		queue<int> q;
		q.push(index);
		while(!q.empty())
		{
			int front = q.front();
			q.pop();
			if(!visited[front])//δ������
			{
				cout<<_vertex[front]<<" ";
				visited[front] = true;
			}
			//���ý���ߵ�û�б����ʵĽ�����
			Node* cur = _edge[front];
			while(cur)
			{
				if(!visited[cur->_dst])
				{
					q.push(cur->_dst);
				}
				cur = cur->_next;
			}
		}
		cout<<endl;
	}

	bool Kruskal(GraphLink<V,W>& tables)
	{
		if(_isDirection)//����ͼ��������С������
		{
			return false;;
		}

		tables._vertex = _vertex;
		tables._edge.resize(_vertex.size());
		tables._isDirection = _isDirection;
		int count = 0;

		struct Compare
		{
			bool operator()(const Node* l,const Node* r)
			{
				return l->_w < r->_w;
			}
		};

		Heap<Node*,Compare> h;
		//��ÿ���ߵ���Ϣ�����
		for(int i = 0; i < _vertex.size(); ++i)
		{
			Node* cur = _edge[i];
			while(cur)
			{
				h.Push(cur);
				cur = cur->_next;
			}
		}

		UnionFindSet ufs(_vertex.size() + 1);
		while(count < _vertex.size() - 1)
		{
			if(h.Empty())//�����Ѿ�û��Ԫ�أ����Ǳ�����û�дﵽN-1,��ʱ��ʾ��С�������޷�����
			{
				return false;
			}

			//�Ӷ���ѡ��һ����С��
			Node* top = h.Top();
			h.Pop();
			int srcIndex = top->_src;
			int dstIndex = top->_dst;

			//����srcIndex��dstIndex�Ƿ���һ��������
			int root1 = ufs.Find(top->_src);
			int root2 = ufs.Find(top->_dst);
			if(root1 != root2)//���ܼ���ߣ����ҽ��кϲ���������
			{
				tables._AddEdge(top->_src,top->_dst,top->_w);
				ufs.Union(top->_src,top->_dst);
				++count;
			}
		}
		return true;
	}
protected:
	void _DFS(const V& v,bool (&visited)[5])
	{
		int index = _GetIndex(v);
		visited[index] = true;
		cout<<_vertex[index]<<" ";
		Node* cur = _edge[index];
		while(cur)
		{
			if(!visited[cur->_dst])
				_DFS(_vertex[cur->_dst],visited);

			cur = cur->_next;
		}
	}

	int _GetIndex(const  V& v)
	{
		for(int i = 0; i < _vertex.size(); ++i)
		{
			if(_vertex[i] == v)
				return i;
		}
		throw std::invalid_argument("�����Ľ�����");
	}
	void _AddEdge(size_t src,size_t dst,const W& w)
	{
		Node* newNode = new Node(src,dst,w);

		newNode->_next = _edge[src];
		_edge[src] = newNode;
	}
private:
	vector<V> _vertex;
	vector<Node*> _edge;
	bool _isDirection;
};

void TestGraphLink()
{
	char array[] = {'A','B','C','D','E'};

	GraphLink<char,int> gm(array,5);
	gm.AddEdge('A','B',8);
	gm.AddEdge('A','C',10);
	gm.AddEdge('D','E',12);
	gm.AddEdge('D','C',6);
	gm.AddEdge('D','B',20);

	gm.Print();
	gm.DFS('A');
	gm.BFS('A');
	GraphLink<char,int> LeastTree(array,5);
	gm.Kruskal(LeastTree);
	LeastTree.Print();
}