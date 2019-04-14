#include "vector.hpp"
#include <iostream>
#include "list.hpp"
#include "RBTree.hpp"
#include "Map.hpp"
using namespace std;

int main()
{
	RBTNode<int> *p = nullptr;
	MapIterator<int> mi(p);
	MapIterator<int> mi2(mi);
	return 0;
}