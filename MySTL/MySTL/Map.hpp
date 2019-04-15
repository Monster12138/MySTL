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
		Self tmp(*this);
		Increasement();
		return tmp;
	}

	Self& operator++(int)
	{
		Increasement();
		return *this;
	}

	Self& operator--()
	{
		Self tmp(*this);
		Decreasement();
		return tmp;
	}

	Self& operator--(int)
	{
		Decreasement();
		return *this;
	}

	Self& operator!=(const Self& s)const { return _p != s._p; }

	Self& operator==(const Self& s)const { return !(*this != s); }
private:
	void Increasement()
	{
		//1.��_p�����������ʱ��ȥ������������С��
		if (_p && _p->_right)
		{
			_p = _p->_right;
			while (_p->_left)
				_p = _p->_left;
		}
		else //2.��_p�����������ʱ�������ҵ�һ�����Һ��Ӳ��ǵ�ǰ���Ľ��
		{
			PNode parent = _p->_parent;
			while (parent && parent->_right = _p)
			{
				_p = _p->_parent;
				parent = _p->_parent;
			}

			/*
			����������ʼָ����ڵ㣬�ڽ��������ѭ���󣬵�������ָ����head���
			����������parent��ָ����ڵ㣬���ʱ����Ҫ����_p = parent��
			*/
			if (_p->_right != parent)
				_p = parent;
		}
	}

	void Decreasement()
	{
		if (_p->_parent->_parent == _p && _p->_color == RED)	//1.�ýڵ���head�ڵ�
		{
			_p = _p->_right;
		}
		else if (_p && _p->_left) //2.�ýڵ�������������ȥ��������������
		{
			_p = _p->_left;
			while (_p->_right)
				_p = _p->_right;
		}
		else //3.�ýڵ������������������ҵ�һ�������Ӳ��ǵ�ǰ�ڵ�Ľڵ�
		{
			PNode parent = _p->_parent;
			while (parent->_left == _p)
			{
				_p = parent;
				parent = _p->_parent;
			}

			_p = parent;
		}
	}
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
		MapIteratorReverse tmp(_it);
		--(tmp._it);
		return tmp;
	}

	Self& operator++(int)
	{
		--_it;
		return *this;
	}

	Self& operator--()
	{
		MapIteratorReverse tmp(_it);
		++(tmp._it);
		return tmp;
	}

	Self& operator--(int)
	{
		++_it;
		return *this;
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