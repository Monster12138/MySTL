#include "vector.hpp"
#include <iostream>
#include "list.hpp"
using namespace std;

int main()
{
	ListNode<int> ln(2);
	ListIterator<int, int&, int*> it;
	ListReverseIterator<int, int&, int*, ListIterator<int, int&, int*>> rit;


	//vector≤‚ ‘
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