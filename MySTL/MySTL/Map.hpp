#pragma once
#include "RBTree.hpp"

template<typename T, typename Ref , typename Ptr>
class MapIterator
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
	typedef MapIterator<T, Ref, Ptr> Self;
private:
	PNode _p;

public:
	MapIterator(PNode p):_p(p) {}
	MapIterator(Self& s):_p(s._p) {}

	Ref operator*()const { return *_p->_data; }
	Ptr operator->()const { return &(operator*()); }

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

	Self& operator!=(const Self& s)const { return _p != s._p; }

	Self& operator==(const Self& s)const { return !(*this != s); }
};

template<typename T, typename Ref, typename Ptr, class Iterator>
class MapIteratorReverse
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
	typedef MapIteratorReverse<T, Ref, Ptr, Iterator> Self;
private:
	Iterator _it;

public:
	MapIteratorReverse(const Iterator& it) :_it(it) {}
	MapIteratorReverse(Self& s) :_it(s._it) {}

	Ref operator*()const
	{
		Iterator tmp(_it);
		return (--tmp).operator*();
	}
	Ptr operator->()const { return &(operator*()); }

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

	Self& operator!=(const Self& s)const { return _it != s._it; }

	Self& operator==(const Self& s)const { return !(*this != s); }
};

template<typename T>
class Map
{
public:
	typedef MapIterator<T, T&, T*> Iterator;
	typedef MapIterator<T, const T&, const T*> ConstIterator;
	typedef MapIteratorReverse<T, T&, T*, Iterator> ReverseIterator;
	typedef MapIteratorReverse<T, const T&, const T*, ConstIterator> ConstReverseIterator;


};