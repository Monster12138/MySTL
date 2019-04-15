#pragma once

#include <algorithm>
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

template<class T, class KeyOfValue>
class RBTree
{
	typedef RBTNode<T> Node;
	typedef Node* PNode;

private:
	PNode _phead;
public:
	RBTree()
	{
		_phead = new Node;
		_phead->_left = _phead;
		_phead->_right = _phead;
		_phead->_parent = nullptr;
	}

	~RBTree()
	{
		Destory(GetRoot());
	}

	bool Insert(const T& data)
	{
		PNode& pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_parent = _phead;
		}
		else
		{
			PNode cur = pRoot;
			PNode pParent = nullptr;

			//���Ҳ���λ��
			while (cur)
			{
				pParent = cur;
				if (KeyOfValue(data) < KeyOfValue(cur->_data))
					cur = cur->_left;
				else if (KeyOfValue(data) > KeyOfValue(cur->_data))
					cur = cur->_right;
				else
					return false;
			}

			//����
			cur = new Node(data);
			if (KeyOfValue(data) < KeyOfValue(pParent->_data))
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
							RouteL(pParent);
							std::swap(cur, pParent);
						}
						
						//�����
						pParent->_color = BLACK;
						grandfa->_color = RED;
						RouteR(grandfa);
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
							RouteR(pParent);
							std::swap(cur, pParent);
						}

						pParent->_color = BLACK;
						grandfa->_color = RED;
						RouteL(grandfa);
					}
				}
			}
		}

		pRoot->_color = BLACK;
		_phead->_left = LeftMost();
		_phead->_right = RightMost();
		return true;
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
private:
	PNode& GetRoot()
	{
		return _phead->_parent;
	}

	PNode LeftMost()
	{
		PNode pRoot = GetRoot();
		if (nullptr == pRoot)
			return nullptr;

		PNode cur = pRoot;
		while (cur->_left)
			cur = cur->_left;

		return cur;
	}

	PNode RightMost()
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
	void RouteL(PNode pParent)
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

	void RouteR(PNode pParent)
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

	void Destory(PNode& pRoot)
	{
		if (pRoot)
		{
			Destory(pRoot->_left);
			Destory(pRoot->_right);
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

void TestRBTree()
{
	
}



