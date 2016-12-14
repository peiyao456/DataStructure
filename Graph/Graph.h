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
		//申请结点数组
		_vertex = new V[_size];
		//申请矩阵
		_martix = new W*[_size];
		for(int i = 0; i < _size; ++i)
		{
			_martix[i] = new W[_size];
			_vertex[i] = arr[i];//对结点信息进行赋值
		}
		//对矩阵进行初始化，可以给出一个非法值，也可以用默认值
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
		else//无向图
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
		throw std::invalid_argument("给定的结点错误");
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

	//处理非连通图的情况
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
			if(!visited[front])//未被访问
			{
				cout<<_vertex[front]<<" ";
				visited[front] = true;
			}
			//将该结点后边的没有被访问的结点入队
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
		if(_isDirection)//有向图不能求最小生成树
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
		//将每条边的信息都入堆
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
			if(h.Empty())//堆里已经没有元素，但是边数还没有达到N-1,此时表示最小生成树无法生成
			{
				return false;
			}

			//从堆里选出一条最小边
			Node* top = h.Top();
			h.Pop();
			int srcIndex = top->_src;
			int dstIndex = top->_dst;

			//查找srcIndex和dstIndex是否自一个集合中
			int root1 = ufs.Find(top->_src);
			int root2 = ufs.Find(top->_dst);
			if(root1 != root2)//才能加入边，并且进行合并两个集合
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
		throw std::invalid_argument("给定的结点错误");
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