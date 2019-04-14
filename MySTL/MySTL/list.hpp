#pragma once
#include <iostream>

template<class T>
struct ListNode
{
	T _value;
	ListNode<T> *_pre;
	ListNode<T> *_next;

	ListNode(const T& v = T())
		:_value(v), _pre(nullptr), _next(nullptr) 
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

	Node& operator*() { return *_ptr; }
	Node& operator->() { return *_ptr; }

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

template <class T>
class List
{
	typedef ListNode<T> Node;
	typedef Node* pNode;

	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<T, const T&, const T*> ConstIterator;
	typedef ListReverseIterator<T, T&, T*, Iterator> ReverseIterator;
	typedef ListReverseIterator<T, const T&, const T*, ConstIterator> ConstReverseIterator;

private:
	pNode _head;

	void CreatHead()
	{
		_head = new Node;
		_head->_pre = _head;
		_head->_next = _head;
	}
public:
	List()
	{
		CreatHead();
	}

	List(int n, const T& v)
	{
		CreatHead();
		while (n--)
		{
			push_back(v);
		}
	}

	template<class Iterator>
	List(Iterator first, Iterator last)
	{
		CreatHead();
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}

	List(const List<T>& l)
	{
		CreatHead();

		List tmp(l.cbegin(), l.cend());
		this->Swap(tmp);
	}

	List<T>& operator=(const List<T>& l)
	{
		if (this != &l)
		{
			List tmp(l.begin(), l.end());
			this->Swap(tmp);
		}
		return *this;
	}

	~List()
	{
		clear();
		delete _head;
		_head = nullptr;
	}

	Iterator begin()
	{
		return Iterator(_head->_next);
	}

	Iterator end()
	{
		return Iterator(_head);
	}

	ReverseIterator rbegin()
	{
		return ReverseIterator(end());
	}

	ReverseIterator rend()
	{
		return ReverseIterator(begin());
	}

	ConstIterator cbegin()const
	{
		return ConstIterator(_head->_next);
	}

	ConstIterator cend()const
	{
		return ConstIterator(_head);
	}

	ConstReverseIterator crbegin()const
	{
		return ConstReverseIterator(cend());
	}

	ConstReverseIterator crend()const
	{
		return ConstReverseIterator(cbegin());
	}

	size_t size()const
	{
		size_t sz = 0;
		
		for (auto it = cbegin(); it != cend(); ++it)
		{
			++sz;
		}

		return sz;
	}

	bool empty()const
	{
		return _head->_next == _head;
	}

	void resize(size_t new_size, const T& v = T())
	{
		size_t old_size = size();
		if (old_size < new_size)
		{
			for (size_t i = old_size; i < new_size; ++i)
			{
				push_back(v);
			}
		}
		else
		{
			for (size_t i = new_size; i < old_size; ++i)
			{
				pop_back();
			}
		}
	}

	T& front()
	{
		return *_head->_next->_value;
	}

	const T& front()const
	{
		return *_head->_next->_value;
	}

	T& back()
	{
		return *_head->_pre->_value;
	}

	const T& back()const
	{
		return *_head->_pre->_value;
	}

	void push_back(const T& v)
	{
		pNode pnew_node = new Node(v);

		pnew_node->_pre = _head->_pre;
		pnew_node->_next = _head;

		_head->_pre->_next = pnew_node;	
		_head->_pre = pnew_node;
	}

	void pop_back()
	{
		pNode del = _head->_pre;

		if (del != _head)
		{
			del->_pre->_next = _head;
			_head->_pre = del->_pre;

			delete del;
		}
	}

	void push_front(const T& v)
	{
		pNode pnew_node = new Node(v);

		pnew_node->_pre = _head;
		pnew_node->_next = _head->_next;

		_head->_next->_pre = pnew_node;
		_head->_next = pnew_node;
	}

	void pop_front()
	{
		pNode del = _head->_next;
		if (del != _head)
		{
			del->_next->_pre = _head;
			_head->_next = del->_next;

			delete del;
		}
	}

	Iterator insert(Iterator pos, const T& v)
	{
		pNode pnew_node = new Node(v);

		pNode cur = pos._ptr;
		pnew_node->_next = cur;
		pnew_node->_pre = cur->_pre;

		cur->_pre->_next = pnew_node;
		cur->_pre = pnew_node;

		return Iterator(pnew_node);
	}

	Iterator erase(Iterator pos)
	{
		pNode del = pos._ptr;
		
		del->_pre->_next = del->_next;
		del->_next->_pre = del->_pre;

		pNode next = del->_next;
		delete del;

		return Iterator(next);
	}

	void clear()
	{
		pNode cur = _head->_next;

		while (cur != _head)
		{
			_head->_next = cur->_next;
			delete cur;
			cur = _head->_next;
		}

		_head->_next = _head;
		_head->_pre = _head;
	}

	void Swap(List<T> &l)
	{
		swap(_head, l._head);
	}

	void PrintList()
	{
		for (auto it = begin(); it != end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};

void TestList()
{
#if 0
	ListNode<int> ln(2);
	ListIterator<int, int&, int*> it;
	ListReverseIterator<int, int&, int*, ListIterator<int, int&, int*>> rit;

	List<int> l1;
	List<int> l2(5, 1);
	List<int> l3(l2);

	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
	l1.pop_back();
	l1.insert(l1.begin(), 6);
	l1.erase(l1.begin());
	l1.PrintList();
	l1.clear();
	cout << "size: " << l1.size() << endl;
	cout << "empty: " << l1.empty() << endl;
#endif
}