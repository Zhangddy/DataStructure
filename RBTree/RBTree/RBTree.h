#pragma once
enum Colour
{
	BLACK,
	RED,
};

template <class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	Colour _col;

	RBTreeNode(const T& data)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(BLACK)
	{ }
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<pair<K, V>> Node;
public:
	RBTree()
		: _root(nullptr)
	{ }

	pair<Node*, bool> insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return make_pair(_root, true);
		}
		
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			// һ. ��������һ�����ҵ�Ӧ�ò����λ��
			if (cur->_data.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_data.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(cur, false);
			}
		}
		cur = new Node(kv);
		cur->_col = RED;
		Node* ret = cur; // ���ڱ��淵��ֵ

		if (parent->_data.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// ��. �ҵ�֮����е���
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			// parent��randfather��ʱ
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				// ���1, ֻ��ı���ɫȻ�����ϼ�������
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				// ���2 3, curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�� �������ϼ�������
				else
				{
					// �ж������2����3
					// ���2
					//     g
					//   p
					// c
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					// ���3
					//     g
					//   p
					//    c
					else
					{
						RotateLR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else // parent��grandfather��ʱ
			{
				Node* uncle = grandfather->_left;
				// ���1, ֻ��ı���ɫȻ�����ϼ�������
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				// ���2 3, curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�� �������ϼ�������
				else
				{
					// �ж������2����3
					// ���2
					// g
					//   p
					//     c
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					// ���3
					//   g
					//     p
					//    c
					else
					{
						RotateRL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;

		return make_pair(ret, true);
	}

	void RotateR(Node* parent)
	{
		Node* pSubL = parent->_left;
		Node* pSubLR = pSubL->_right;

		pSubL->_right = parent;
		Node* pParent = parent->_parent;
		parent->_parent = pSubL;

		if (pSubLR != nullptr)
		{
			pSubLR->_parent = parent;
		}
		parent->_left = pSubLR;

		if (parent == _root)
		{
			_root = pSubL;
			pSubL->_parent = nullptr;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = pSubL;
			}
			else
			{
				pParent->_right = pSubL;
			}
			pSubL->_parent = pParent;
		}
	}

	void RotateL(Node* parent)
	{
		Node* pSubR = parent->_right;
		Node* pSubRL = pSubR->_left;

		pSubR->_left = parent;
		Node* pParent = parent->_parent;
		parent->_parent = pSubR;

		parent->_right = pSubRL;
		if (pSubRL != nullptr)
			pSubRL->_parent = parent;

		if (parent == _root)
		{
			_root = pSubR;
			pSubR->_parent = nullptr;
		}
		else
		{
			if (pParent->_right == parent)
			{
				pParent->_right = pSubR;
			}
			else
			{
				pParent->_left = pSubR;
			}
			pSubR->_parent = pParent;
		}
	}

	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}

	void RotateRL(Node* parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}

private:
	Node* _root;
};
