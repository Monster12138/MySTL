#pragma once
#include "RBTree.hpp"

template<class T>
class Set 
{
	struct KeyOfValue
	{
		const T& operator()(const T& data)
		{
			return data;
		}
	};
	typedef RBTree<T, T, KeyOfValue> RBTree;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> ConstIterator;
	typedef RBTreeIteratorReverse<T, T&, T*, Iterator> ReverseIterator;
	typedef RBTreeIteratorReverse<T, const T&, const T*, ConstIterator> ConstReverseIterator;
private:
	RBTree _t;
public:
	Set() {}

	Iterator Begin() { return _t.Begin(); }

	Iterator End() { return _t.End(); }

	ReverseIterator rBegin() { return _t.rBegin(); }

	ReverseIterator rEnd() { return _t.rEnd(); }

	unsigned int Size()const { return _t.Size(); }

	bool Empty()const { return _t.Empty(); }

	std::pair<Iterator, bool> Insert(const T& data) { return _t.Insert(data); }

	Iterator Find(const T& key) { return _t.Find(key); }
};

void SetTest()
{
	Set<int> s;
	s.Insert(3);
	s.Insert(2);
	s.Insert(4);
	s.Insert(5);
	s.Insert(1);
	for (auto it = s.Begin(); it != s.End(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}