#pragma once

#include <algorithm>
#include <iostream>
enum Color{RED, BLACK};

template <class T>
struct RBTNode
{
	T _data;
	Color _color;
	RBTNode *_left;
	RBTNode *_right;
	RBTNode *_parent;

	RBTNode(const T& data = T(), Color color = RED):
		_data(data),
		_color(color),
		_left(nullptr),
		_right(nullptr),
		_parent(nullptr)
	{}
};

template<typename T, typename Ref , typename Ptr>
class RBTreeIterator
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
	typedef RBTreeIterator<T, Ref, Ptr> Self;
private:
	PNode _p;

public:
	RBTreeIterator(PNode p):_p(p) {}
	RBTreeIterator(const Self& s):_p(s._p) {}

	Ref operator*()const { return _p->_data; }
	Ptr operator->()const { return &(operator*()); }

	Self& operator=(const Self& i)
	{
		_p = i._p;
	}

	Self operator++()
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

	bool operator!=(const Self& s)const { return _p != s._p; }

	bool operator==(const Self& s)const { return !(*this != s); }
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
			while (parent && parent->_right == _p)
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
class RBTreeIteratorReverse
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
	typedef RBTreeIteratorReverse<T, Ref, Ptr, Iterator> Self;
private:
	Iterator _it;

public:
	RBTreeIteratorReverse(const Iterator& it) :_it(it) {}
	RBTreeIteratorReverse(const Self& s) :_it(s._it) {}

	Ref operator*()const
	{
		Iterator tmp(_it);
		return (--tmp).operator*();
	}
	Ptr operator->()const { return &(operator*()); }

	Self operator++()
	{
		RBTreeIteratorReverse tmp(_it);
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
		RBTreeIteratorReverse  tmp(_it);
		++(tmp._it);
		return tmp;
	}

	Self& operator--(int)
	{
		++_it;
		return *this;
	}

	bool operator!=(const Self& s)const { return _it != s._it; }

	bool operator==(const Self& s)const { return !(*this != s); }
};


template<class K, class T, class KeyOfValue>
class RBTree
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;
public:
	typedef RBTreeIterator<T, T&, T*> Iterator;
	typedef RBTreeIteratorReverse<T, T&, T*, Iterator> ReverseIterator;

private:
	PNode _phead;
	unsigned int _size;
public:
	RBTree()
	{
		_phead = new Node;
		_phead->_left = _phead;
		_phead->_right = _phead;
		_phead->_parent = nullptr;
		_size = 0;
	}

	~RBTree()
	{
		_Destory(GetRoot());
	}

	std::pair<Iterator, bool> Insert(const T& data)
	{
		PNode thisNode = nullptr;
		PNode& pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_parent = _phead;

			++_size;
			thisNode = pRoot;
		}
		else
		{
			PNode cur = pRoot;
			PNode pParent = nullptr;

			//���Ҳ���λ��
			while (cur)
			{
				pParent = cur;
				if (KeyOfValue()(data) < KeyOfValue()(cur->_data))
					cur = cur->_left;
				else if (KeyOfValue()(data) > KeyOfValue()(cur->_data))
					cur = cur->_right;
				else
					return std::make_pair(Iterator(thisNode), false);
			}

			//����
			thisNode = cur = new Node(data);
			if (KeyOfValue()(data) < KeyOfValue()(pParent->_data))
				pParent->_left = cur;
			else
				pParent->_right = cur;

			cur->_parent = pParent;
			//������ɫ
			while (pParent != _phead && RED == pParent->_color)
			{
				PNode grandfa = pParent->_parent;
				if (pParent == grandfa->_left)
				{
					PNode uncle = grandfa->_right;
					//���һ����������ڣ���Ϊ��
					if (uncle && uncle->_color == RED)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandfa->_color = RED;
						cur = grandfa;
						pParent = cur->_parent;
					}
					else
					{
						//�������
						if (cur == pParent->_right)
						{
							_RouteL(pParent);
							std::swap(cur, pParent);
						}
						
						//�����
						pParent->_color = BLACK;
						grandfa->_color = RED;
						_RouteR(grandfa);
					}
				}
				else
				{
					PNode uncle = grandfa->_left;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						grandfa->_color = RED;
						uncle->_color = BLACK;

						cur = grandfa;
						pParent = cur->_parent;
					}
					else
					{
						if (cur == pParent->_left)
						{
							_RouteR(pParent);
							std::swap(cur, pParent);
						}

						pParent->_color = BLACK;
						grandfa->_color = RED;
						_RouteL(grandfa);
					}
				}
			}
		}

		pRoot->_color = BLACK;
		_phead->_left = _LeftMost();
		_phead->_right = _RightMost();
		++_size;
		return std::make_pair(Iterator(thisNode), true);
	}

	void Inorder()
	{
		_Inorder(GetRoot());
		std::cout << std::endl;
	}

	bool IsRBTree()
	{
		PNode pRoot = GetRoot();

		if (nullptr == pRoot)
			return true;

		if (RED == pRoot->_color)
		{
			std::cout << "Υ������2�����ڵ���ɫΪ��ɫ\n";
			return false;
		}

		int black_count = 0;
		PNode cur = pRoot;
		while (cur)
		{
			if (BLACK == cur->_color)
				++black_count;

			cur = cur->_left;
		}

		return _IsRBTree(pRoot, black_count, 0);
	}

	Iterator Find(const K& key)
	{
		PNode cur = GetRoot();
		while (cur)
		{
			if (key == KeyOfValue()(cur->_data))
				return Iterator(cur);
			else if (key < KeyOfValue()(cur->_data))
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		return Iterator(_phead);
	}

	Iterator Begin()
	{
		return Iterator(_phead->_left);
	}

	Iterator End()
	{
		return Iterator(_phead);
	}

	ReverseIterator rBegin()
	{
		return ReverseIterator(_phead->_right);
	}

	ReverseIterator rEnd()
	{
		return ReverseIterator(_phead);
	}
	void Clear()
	{
		_Destory(GetRoot());
		_phead->_left = _phead;
		_phead->_right = _phead;
		_size = 0;
	}

	unsigned int Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}
private:
	PNode& GetRoot()
	{
		return _phead->_parent;
	}

	PNode _LeftMost()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return nullptr;

		PNode cur = pRoot;
		while (cur->_left)
			cur = cur->_left;

		return cur;
	}

	PNode _RightMost()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return nullptr;

		PNode cur = pRoot;
		while (cur->_right)
			cur = cur->_right;

		return cur;
	}

	//����
	void _RouteL(PNode pParent)
	{
		PNode pSubR = pParent->_right;
		
		pParent->_right = pSubR->_left;
		if (pSubR->_left)
			pSubR->_left->_parent = pParent;

		pSubR->_parent = pParent->_parent;

		pSubR->_left = pParent;

		PNode& pRoot = GetRoot();
		if (pParent == pRoot)
		{
			pRoot = pSubR;
		}
		else
		{
			if (pParent == pParent->_parent->_left)
			{
				pParent->_parent->_left = pSubR;
			}
			else
			{
				pParent->_parent->_right = pSubR;
			}
		}

		pParent->_parent = pSubR;
	}

	void _RouteR(PNode pParent)
	{
		PNode pSubL = pParent->_left;

		pParent->_left = pSubL->_right;
		if (pSubL->_right)
			pSubL->_right->_parent = pParent;

		pSubL->_right = pParent;
		pSubL->_parent = pParent->_parent;


		PNode& pRoot = GetRoot();
		if (pParent == pRoot)
		{
			pRoot = pSubL;
		}
		else
		{
			if (pParent == pParent->_parent->_left)
			{
				pParent->_parent->_left = pSubL;
			}
			else
			{
				pParent->_parent->_right = pSubL;
			}
		}
		pParent->_parent = pSubL;
	}

	void _Inorder(PNode pRoot)
	{
		if (pRoot)
		{
			_Inorder(pRoot->_left);
			std::cout << pRoot->_data << " ";
			_Inorder(pRoot->_right);
		}
	}

	void _Destory(PNode& pRoot)
	{
		if (pRoot)
		{
			_Destory(pRoot->_left);
			_Destory(pRoot->_right);
			delete pRoot;
			pRoot = nullptr;
		}
	}

	bool _IsRBTree(PNode pRoot, int black_count, int pathBlack)
	{
		if (nullptr == pRoot)
			return true;

		if (BLACK == pRoot->_color)
			++pathBlack;

		PNode pParent = pRoot->_parent;
		if (pParent && RED == pRoot->_color && RED == pParent->_color)
		{
			std::cout << "Υ��������3��������һ��ĺ�ɫ�ڵ�\n";
			return false;
		}

		if (nullptr == pRoot->_left && nullptr == pRoot->_right)
		{
			if (black_count != pathBlack)
			{
				std::cout << "Υ������4��·���к�ɫ�ڵ������ͬ\n";

				return false;
			}
		}

		return _IsRBTree(pRoot->_left, black_count, pathBlack) 
			&& _IsRBTree(pRoot->_right, black_count, pathBlack);
	}
};





