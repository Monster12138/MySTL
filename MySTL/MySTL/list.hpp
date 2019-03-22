#pragma once
template<class T>
struct ListNode
{
	T _value;
	ListNode *_pre;
	ListNode *_next;

	ListNode(T v, ListNode *pre = nullptr, ListNode *next = nullptr)
		:_value(v), _pre(pre), _next(next) 
	{}
};

template<class T, class Ref, class Ptr>
class ListIterator
{
	typedef ListNode<T> Node;
	typedef	ListIterator<T, Ref, Ptr> Self;
public:
	Node *_ptr;

	ListIterator(Node *p = nullptr) :_ptr(p) {}
	ListIterator(const Self& it) :_ptr(it._ptr) {}

	T& operator*() { return _ptr->_value; }
	T& operator->() { return _ptr->_value; }

	Self& operator++() { _ptr = _ptr->_next; return *this; }
	Self& operator++(int) { Self tmp(*this); _ptr = _ptr->_next; return tmp; }
	Self& operator--() { _ptr = _ptr->_pre; return *this; }
	Self& operator--(int) { Self tmp(*this); _ptr = _ptr->_pre; return tmp; }

	bool operator!=(const Self& l) { return _ptr != l._ptr; }
	bool operator==(const Self& l) { return !(*this != l); }
};

template<class T, class Ref, class Ptr, class Iterator>
class ListReverseIterator
{
	typedef ListReverseIterator<T, Ref, Ptr, Iterator> Self;
	
public:
	Iterator _it;

	ListReverseIterator(const Iterator &it = Iterator())
		:_it(it)
	{}

	ListReverseIterator(const Self& l)
		:_it(l.it)
	{}

	Ref operator*()
	{
		Iterator temp(_it);
		return *(--temp);
	}

	Ptr operator->()
	{
		return &operator*();
	}

	Self& operator++() { --_it; return this; }
	Self& operator++(int) { Self temp(_it); --_it; return temp; }
	Self& operator--() { ++_it; return this; }
	Self& operator--(int) { Self temp(_it); ++_it; return temp; }
	
	bool operator!=(const Self& s) { return _it != s._it; }
	bool operator==(const Self& s) { return _it == s._it; }
};