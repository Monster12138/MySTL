#pragma once
#include "RBTree.hpp"

template<typename T>
class MapIterator
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
	typedef MapIterator<T> Self;
private:
	PNode _p;

public:
	MapIterator(PNode p):_p(p) {}
	MapIterator(Self& s):_p(s._p) {}

	Node& operator*() { return *_p; }
	PNode operator->() { return _p; }

	Self& operator=(const Self& s)
	{
		_p = s._p;
	}

	Self& operator++()
	{
		//todo
	}

	Self& operator++(int)
	{
		//todo
	}

	Self& operator--()
	{
		//todo
	}

	Self& operator--(int)
	{
		//todo
	}

	Self& operator!=(const Self& s) { return _p != s._p; }

	Self& operator==(const Self& s) { return !(*this != s); }
};

template<typename T>
class MapIteratorReverse
{
	typedef MapIterator<T> Iterator;
	typedef MapIteratorReverse<T> Self;
private:
	Iterator _it;

public:
	MapIteratorReverse(const Iteratot& it) :_it(it) {}
	MapIteratorReverse(Self& s) :_it(s._it) {}

	Node& operator*() 
	{
		Iterator tmp(_it);
		return (--it).operator*();
	}
	Node& operator->() { return &operator*(); }

	Self& operator=(const Self& s)
	{
		_p = s._p;
	}

	Self& operator++()
	{
		//todo
	}

	Self& operator++(int)
	{
		//todo
	}

	Self& operator--()
	{
		//todo
	}

	Self& operator--(int)
	{
		//todo
	}

	Self& operator!=(const Self& s) { return _p != s._p; }

	Self& operator==(const Self& s) { return !(*this != s); }
};

class Map
{

};