#pragma once
#include "RBTree.hpp"

template<class K, class V>
class Map
{
	typedef std::pair<K, V> T;
	struct KeyOfValue
	{
		const K& operator()(const T& data)
		{
			return data.first;
		}
	};
	typedef RBTree<K, T, KeyOfValue> RBTree;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIterator<T, const T&, const T*> ConstIterator;
	typedef RBTreeIteratorReverse<T, T&, T*, Iterator> ReverseIterator;
	typedef RBTreeIteratorReverse<T, const T&, const T*, ConstIterator> ConstReverseIterator;
private:
	RBTree _t;
public:
	Map() {}

	Iterator Begin() { return _t.Begin(); }

	Iterator End() { return _t.End(); }

	ReverseIterator rBegin() { return _t.rBegin(); }

	ReverseIterator rEnd() { return _t.rEnd(); }

	unsigned int Size()const { return _t.Size(); }

	bool Empty()const { return _t.Empty(); }

	T& operator[](const K& key) { return *(_t.Insert(T(key, V()).first)).second; }

	const T& operator[](const K& key)const { return *(_t.Insert(T(key, V()).first)).second; }

	std::pair<Iterator, bool> Insert(const T& data) { return _t.Insert(data); }

	Iterator Find(const K& key) { return _t.Find(key); }
};

void MapTest()
{
	Map<int, int> m;
	m.Insert({ 2,2 });
	m.Insert({ 4,4 });
	m.Insert({ 1,1 });
	m.Insert({ 3,3 });
	for (auto it = m.Begin(); it != m.End(); ++it)
	{
		std::cout << "[" << (*it).first << "," << (*it).second << "]" << " ";
	}
	std::cout << std::endl;
}