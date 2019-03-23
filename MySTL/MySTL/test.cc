#include "vector.hpp"
#include <iostream>
#include "list.hpp"
using namespace std;

int main()
{
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
	//vector²âÊÔ
#if 0
	vector<int> vec;
	vector<int> vec2(5, 1);
	vector<int> vec3(vec2);
	vec.push_back(1);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(2);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(3);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(4);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.push_back(5);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.resize(20);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.resize(10);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;

	vec.erase(vec.end() - 1);
	cout << "size: " << vec.size() << " capacity: " << vec.capacity() << endl;
	vec.printAll();
#endif
	return 0;
}